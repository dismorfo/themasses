<?php
// $Id$: dlts_image.admin.inc

/**
 * @file
 * Admin page.
 */

/*
 * Constants
 */

function dlts_image_admin($form, &$form_state) {

  $djatoka = dlts_image_djatoka_request(array( 'uri' => drupal_get_path('module', 'dlts_image') . '/img/caspar.jpg'));
  if (!isset($djatoka['error'])) {
    $preview = theme( 'dlts_image_hires', array( 'file' =>
      array(
        'fid' => 'djatoka-test',
        'uri' => $djatoka['identifier'],
        'djakota_width' => $djatoka['width'],
        'djakota_height' => $djatoka['height'],
        'djakota_dwtLevels' => $djatoka['dwtLevels'],
        'djakota_levels' => $djatoka['levels'],
        'djakota_compositingLayerCount' => $djatoka['compositingLayerCount'],
        'zoom' => 5,
        ),
      )
    );
  }
  else {
    $preview = '<div class="messages error"><h2 class="element-invisible">error</h2>'. t('Djatoka: Unable to request metadata from Djakota Jpeg 2000 Image Server. See: @message (code: @code)', array( '@message' => $djatoka['message'], '@code' => $djatoka['code'] )) . '</div>';
  }

  $form = array();
  
  $form['djatoka'] = array(
    '#type' => 'fieldset',
    '#title' => t('Djatoka Jpeg 2000 Image Server'),
    '#collapsed' => FALSE,
    '#collapsible' => TRUE,
  );

  $form['djatoka']['dlts_image_djatoka_service_host'] = array(
    '#type' => 'textfield',
    '#title' => t('Service path'),
    '#default_value' => variable_get( 'dlts_image_djatoka_service_host', ( isset( $_SERVER['HTTP_HOST'] ) ? $_SERVER['HTTP_HOST'] : '' ) ),
    '#size' => 60,
    '#maxlength' => 256,
    '#description' => t("Set host name. <acronym title=\"for example\">e.g.</acronym>, http://myhost.bobst.nyu.edu:8080/adore-djatoka"),
    '#required' => TRUE,
  );

  $form['djatoka']['dlts_image_image_service_preview'] = array(
    '#type' => 'item',
    '#title' => t('Preview'),
    '#markup' => $preview,
    '#weight' => 10,
  );
  
  $form['djatoka']['dlts_image_djatoka_service'] = array(
      '#type' => 'hidden',
      '#value' => variable_get( 'dlts_image_djatoka_service', ''),
  );
  
  $form['djatoka']['dlts_image_djatoka_metadataurl'] = array(
    '#type' => 'hidden',
    '#value' => variable_get( 'dlts_image_djatoka_metadataurl', ''),
  );  

  $form['openurl'] = array(
    '#type' => 'fieldset',
    '#title' => t('OpenURL'),
    '#collapsed' => TRUE,
    '#collapsible' => TRUE,
  );

  $form['openurl']['dlts_image_openlayers'] = array('#type' => 'hidden', '#value' => variable_get( 'dlts_image_openlayers', '' ) );

  $form['openurl']['dlts_image_openlayer_metadaurl_service'] = array(
    '#type' => 'textfield',
    '#title' => t('Service to request image metadata'),
    '#default_value' => variable_get('dlts_image_openlayer_metadaurl_service', 'info:lanl-repo/svc/getMetadata'),
    '#size' => 60,
    '#maxlength' => 256,
    '#description' => t("The service to request image metadata."),
    '#required' => TRUE,
  );

  $form['openurl']['dlts_image_openlayers_openurl'] = array(
    '#type' => 'textfield',
    '#title' => t('OpenURL Resolvers'),
    '#default_value' => variable_get( 'dlts_image_openlayers_openurl', 'Z39.88-2004'),
    '#size' => 60,
    '#maxlength' => 256,
    '#description' => t("Identifier Standard."),
    '#required' => TRUE,
  );

  $form['openurl']['dlts_image_openlayers_format'] = array(
    '#type' => 'textfield',
    '#title' => t('Format'),
    '#default_value' => variable_get( 'dlts_image_openlayers_format', 'image/jpeg' ),
    '#size' => 60,
    '#maxlength' => 256,
    '#description' => t("Format."),
    '#required' => TRUE,
  );
  
  $form['openlayers'] = array(
    '#type' => 'fieldset',
    '#title' => t('OpenLayers'),
    '#collapsed' => FALSE,
    '#collapsible' => TRUE,
  );

  $available_files_lib = file_scan_directory( libraries_get_path('openlayers') . '/lib', '/.*\.js$/', array( 'recurse' => FALSE ) );
  $available_files_build = file_scan_directory( libraries_get_path('openlayers') . '/build', '/.*\.js$/', array( 'recurse' => FALSE ) );
  $available_files = array_merge( (array) $available_files_lib, (array) $available_files_build );
  
  $js = array();

  foreach ( $available_files as $key => $value ) {
    $js[$key] = $value->uri;
  }
    
  $form['openlayers']['dlts_image_openlayers_source'] = array(
      '#type' => 'radios',
      '#title' => t('File'),
      '#default_value' => variable_get( 'dlts_image_openlayers_source', 'sites/all/libraries/openlayers/lib/OpenLayers.js'),
      '#options' => $js,
  );  

  // Make changes to the settings before passing them off to
  // system_settings_form_submit().

  $form['#submit'][] = 'dlts_image_image_service_admin_settings_submit';

  return system_settings_form( $form );
}

/**
 * Form submit handler for dlts_image admin settings form.
 */
function dlts_image_image_service_admin_settings_submit( $form, &$form_state) {

  /**
   * Ensure no trailing slash
   */
  $service = rtrim( $form_state['values']['dlts_image_djatoka_service_host'], '/' );
  $form_state['values']['dlts_image_djatoka_service'] = $service;
  $form_state['values']['dlts_image_djatoka_metadataurl'] = $service . '?';  

}