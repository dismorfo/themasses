<?php

/**
 * @file
 * DLTS Shapes theme functions
 */

/**
 * Returns JS for a openlayers OCR coordinates.
 *
 * Sets certain JavaScript settings for the OCR coordinates.
 *
 * @ingroup themable
 */

function theme_dlts_shapes_ocr_coordinates_openlayers_js($variables) {
  if (isset($variables['terms']) && !empty( $variables['terms'])) {
    
    $settings = array(
      'dlts' => array(
        'shapes' => array(
          'ocr' => $variables['terms'],
        ),
      ),
    );
    
    $options = array(
      'type' => 'setting',
      'scope' => JS_THEME,
    );
    drupal_add_js($settings, $options);
  }
  return '';
}