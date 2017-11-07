<?php


/**
 * @file
 * DLTS Image theme functions
 */

/**
 * Returns HTML for a high-resolution JPEG 2000 image.
 *
 * This function returns the necessary HTML elements, and sets certain
 * JavaScript settings for the file being displayed. The given elements are
 * then replaced by OpenLayers with a zoomable version of the image.
 *
 * @ingroup themable
 */

module_load_include('inc', 'dlts_image', 'dlts_image.file');

function theme_dlts_image_hires($variables) {
  $parameters = drupal_get_query_parameters();
  $file = $variables['file'];
  $module_path = drupal_get_path('module', 'dlts_image');
  $fid = 'id-'. $file['fid'];
  $fileUri = file_create_url($file['uri']);
  drupal_add_css($module_path . '/css/dlts_image.css');
  
  /*
   * Add Openlayers to the page
   */
  drupal_add_js( variable_get( 'dlts_image_openlayers_source', 'sites/all/libraries/openlayers/lib/OpenLayers.js'), array('group' => JS_LIBRARY));

  $openlayers_options = array(
    'zoom' => (isset($file['zoom'])) ? $file['zoom'] : 1,
    'service' => variable_get('dlts_image_djatoka_service', ''),
    'imgMetadata' => array(
      'width' => $file['djakota_width'],
      'height' => $file['djakota_height'],
      'levels' => $file['djakota_levels'],
      'dwtLevels' => $file['djakota_dwtLevels'],
      'compositingLayerCount' => $file['djakota_compositingLayerCount'],
    ),
  );
  
  $js_inline = '(function(O){O.DLTS.Page("'. $fid .'","'.  $fileUri .'",'. json_encode($openlayers_options) .')})(OpenLayers);';

  $js_options = array(
    'group' => JS_DEFAULT,
    'type' => 'inline',
    'every_page' => FALSE,
    'weight' => 5,
    'scope' => 'footer',
    'cache' => TRUE,
    'defer' => TRUE,
  );
  
  drupal_add_js($js_inline, $js_options);  
  
  return '<div id="id-' . $file['fid'] . '" class="dlts_image_map" data-uri="'. $fileUri . '"></div>';
}

function theme_dlts_image_thumbnail($variables) {
  $item = $variables['item'];

  if (is_null($item) || empty($item['uri'])) {
    watchdog('dlts_image', 'Error while returning thumbnail image.', array(), WATCHDOG_WARNING);
    return '';
  }
  $thumb_path = dlts_image_file_path( $item, 'dlts-book-image', FALSE );
  return '<img src="' . file_create_url( $thumb_path ) . '" title="' . check_plain($item['filename']) . '"  alt="' . t('Image preview') . '" />';
}

function theme_dlts_image_widget($variables) {
  $element = $variables['element'];
  $output = '';
  $output .= '<div class="image-widget form-managed-file clearfix">';
  if (isset($element['preview'])) {
    $output .= '<div class="image-preview">';
    $output .= drupal_render($element['preview']);
    $output .= '</div>';
  }
  $output .= '<div class="image-widget-data">';
  if ($element['fid']['#value'] != 0) {
    $element['filename']['#markup'] .= ' <span class="file-size">(' . format_size($element['#file']->filesize) . ')</span> ';
  }
  $output .= drupal_render_children($element);
  $output .= '</div>';
  $output .= '</div>';
  return $output;
}