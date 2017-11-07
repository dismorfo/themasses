<?php

/**
 * @file
 * Implements DLTS Image widgets and formatters.
 *
 */

module_load_include('inc', 'dlts_image', 'dlts_image.djatoka');

function dlts_image_field_info() {
  return array(
    'dlts_image' => array(
      'label' => t('DLTS Image'),
      'description' => t('This field stores the ID of an image file as an integer value.'),
      'settings' => array(
        'uri_scheme' => variable_get('file_default_scheme', 'public'),
        'default_image' => 0,
      ),
      'instance_settings' => array(
        'file_extensions' => 'jp2 tif tiff jpg jpeg',
        'file_directory' => '',
        'max_filesize' => '',
      ),
      'default_widget' => 'dlts_image',
      'default_formatter' => 'dlts_image_hires',
    ),
  );
}

function dlts_image_field_settings_form($field, $instance) {
  $form = image_field_settings_form($field, $instance);
  return $form;
}

/**
* Implements hook_field_instance_settings_form().
*/
function dlts_image_field_instance_settings_form($field, $instance) {

  // Use the file field instance settings form as a basis.
  $form = file_field_instance_settings_form($field, $instance);

  // Remove the description option.
  unset($form['description_field']);
  
  // Remove the file_extensions option, we only accept jp2, jpg, jpeg, tif, tiff.
  unset($form['file_extensions']);
  
  return $form;
}

function dlts_image_field_widget_form(&$form, &$form_state, $field, $instance, $langcode, $items, $delta, $element) {

  // Add display_field setting to field because file_field_widget_form() assumes it is set.
  $field['settings']['display_field'] = 0;
  $elements = file_field_widget_form($form, $form_state, $field, $instance, $langcode, $items, $delta, $element);
  $settings = $instance['settings'];
  $supported_extensions = array('tiff', 'tif', 'jp2', 'jpg', 'jpeg');  
  
  foreach (element_children($elements) as $delta) {
    $elements[$delta]['#upload_validators']['file_validate_extensions'][0] = implode(' ', $supported_extensions);
    // Add all extra functionality provided by the image widget.
    $elements[$delta]['#process'][] = 'dlts_image_field_widget_process';
  }
  
  if ($field['cardinality'] == 1) {
    // If there's only one field, return it as delta 0.
    if (empty($elements[0]['#default_value']['fid'])) {
      $elements[0]['#description'] = theme('file_upload_help', array('description' => $instance['description'], 'upload_validators' => $elements[0]['#upload_validators']));
    }
  }
  else {
    $elements['#file_upload_description'] = theme('file_upload_help', array('upload_validators' => $elements[0]['#upload_validators']));
  }

  return $elements;
}

function dlts_image_field_load($entity_type, $entities, $field, $instances, $langcode, &$items, $age) {
  file_field_load($entity_type, $entities, $field, $instances, $langcode, $items, $age);
}

function dlts_image_field_widget_process($element, &$form_state, $form) {

  $item = $element['#value'];
  $item['fid'] = $element['fid']['#value'];
  $instance = field_widget_instance($element, $form_state);
  $settings = $instance['settings'];
  $widget_settings = $instance['widget']['settings'];
  
  $element['#theme'] = 'dlts_image_widget';
  
  // Add image CSS
  $element['#attached']['css'][] = drupal_get_path('module', 'image') . '/image.css';
  
  // Add the image preview.
  if ($element['#file']) {
  
    $variables = array(
      'style_name' => $widget_settings['preview_image_style'],
      'path' => $element['#file']->uri,
    );     
    
    // Determine image dimensions.
    if (isset($element['#value']['width']) && isset($element['#value']['height'])) {
      $variables['width'] = $element['#value']['width'];
      $variables['height'] = $element['#value']['height'];
    }
    else {
      $info = image_get_info($element['#file']->uri);    
      if (is_array($info)) {
        $variables['width'] = $info['width'];
        $variables['height'] = $info['height'];
      }
      else {
        $variables['width'] = $variables['height'] = 0;
      }
    }

    /**
     * Determine image dimensions and metadata
     * If djakota_*  is available, the others will also be available
     */
    if (isset($element['#value']['djakota_width'])) {
      $variables['djakota_width'] = $element['#value']['djakota_width'];
      $variables['djakota_height'] = $element['#value']['djakota_height'];
      $variables['djakota_levels'] = $element['#value']['djakota_levels'];
      $variables['djakota_dwtLevels'] = $element['#value']['djakota_dwtLevels'];
      $variables['djakota_compositingLayerCount'] = $element['#value']['djakota_compositingLayerCount'];
      $variables['width'] = $element['#value']['width'];
      $variables['height'] = $element['#value']['width'];
    }
    /**
     * Call Djakota Image Server
     */ 
    else {
      $djatoka = dlts_image_djatoka_request($element['#file']);
      
      if (!isset($djatoka['error'])) {
        $variables['djakota_width'] = $djatoka['width'];
        $variables['djakota_height'] = $djatoka['height'];
        $variables['djakota_levels'] = $djatoka['levels'];
        $variables['djakota_dwtLevels'] = $djatoka['dwtLevels'];
        $variables['djakota_compositingLayerCount'] = $djatoka['compositingLayerCount'];
      }
      else {
        form_set_error('dlts_image', t('Error requesting image metadata from Djakota service. @message (error code @code).', array('@message' => $djatoka['message'], '@error' => $djatoka['error'])));
        $variables['djakota_width'] = 
          $variables['djakota_height'] =  
          $variables['djakota_levels'] = 
          $variables['djakota_dwtLevels'] = 
          $variables['djakota_compositingLayerCount'] = 0;
      }
    }
    
    /**
     * Store the metadata in the form
     */
    
    $element['width'] = array(
      '#type' => 'hidden',
      '#value' => $variables['width'],
    );

    $element['height'] = array(
      '#type' => 'hidden',
      '#value' => $variables['height'],
    );
    
    $element['djakota_width'] = array(
      '#type' => 'hidden',
      '#value' => $variables['djakota_width'],
    );
    
    $element['djakota_height'] = array(
      '#type' => 'hidden',
      '#value' => $variables['djakota_height'],
    );
    
    $element['djakota_levels'] = array(
      '#type' => 'hidden',
      '#value' => $variables['djakota_levels'],
    );

    $element['djakota_dwtLevels'] = array(
      '#type' => 'hidden',
      '#value' => $variables['djakota_dwtLevels'],
    );
    
    $element['djakota_compositingLayerCount'] = array(
      '#type' => 'hidden',
      '#value' => $variables['djakota_compositingLayerCount'],
    );
    
    $element['preview'] = array(
      '#type' => 'markup',
      '#markup' => theme('image_style', $variables),
    );
        
  }
  return $element;
}

/**
 * Implements hook_field_widget_info().
 */
  function dlts_image_field_widget_info() {
  return array(
    'dlts_image' => array(
      'label' => t('DLTS Image'),
      'field types' => array('dlts_image'),
      'settings' => array(
        'progress_indicator' => 'throbber',
        'preview_image_style' => 'thumbnail',
      ),
      'behaviors' => array(
        'multiple values' => FIELD_BEHAVIOR_CUSTOM,
        'default value' => FIELD_BEHAVIOR_NONE,
      ),
    ),
  );
}

/**
 * Implements hook_field_widget_settings_form().
 */
function dlts_image_field_widget_settings_form($field, $instance) {
  return image_field_widget_settings_form($field, $instance);
}

/**
 * Implements hook_field_formatter_info().
 */
function dlts_image_field_formatter_info() {
  return array(
    'dlts_image_hires' => array(
      'label' => t('DLTS Hi-Res Image'),
      'field types' => array('dlts_image'),
      'description' => t('Displays image files in their original size.'),
    ),
    'dlts_image_thumbnail' => array(
      'label' => t('DLTS Thumbnail Image'),
      'field types' => array('dlts_image'),
      'description' => t('Displays image files in their thumbnail size.'),
    ),
    'dlts_image_thumbnail_nodelink' => array(
      'label' => t('DLTS Thumbnail Image linked to node'),
      'field types' => array('dlts_image'),
      'description' => t('Displays image files in their thumbnail size.'),
    ),
  );
}

/**
 * Implments hook_field_formatter_view().
 */
function dlts_image_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();
  switch ($display['type']) {
    case 'dlts_image_hires':
      foreach ($items as $delta => $item) {
        $element[$delta] = array(
          '#theme' => 'dlts_image_hires',
          '#file' => $item,
        );
      }
      break;
    
    default:
      // something went wrong
      break;
  }
  return $element;
}

function dlts_image_field_is_empty($item, $field) {
  return file_field_is_empty($item, $field);
}