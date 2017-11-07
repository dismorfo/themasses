<?php

/*
 * Make sure navbar-item links include: oembed=true
 */
function dlts_book_oembed_dlts_book_pager_link($arguments) {
  if ( isset( $_GET['oembed'] ) && $_GET['oembed'] == 'true' ) {
    $arguments['query'] = array(
      'oembed' => 'true',
    );
  }
  return '<li class="navbar-item">' . l( $arguments['text'], $arguments['url'], $arguments ) . '</li>';
}

/*
 * Remove unnecessary white-space to improve DOM performance. Not pretty but optimal.
 * See: http://api.drupal.org/api/drupal/includes--theme.inc/function/theme_html_tag/7
 */
function dlts_book_oembed_html_tag($variables) {
  $element = $variables['element'];
  $attributes = isset($element['#attributes']) ? drupal_attributes($element['#attributes']) : '';
  if (!isset($element['#value'])) {
    return '<' . $element['#tag'] . $attributes . ' />';
  }
  else {
    $output = '<' . $element['#tag'] . $attributes . '>';
    if (isset($element['#value_prefix'])) {
      $output .= $element['#value_prefix'];
    }
    $output .= $element['#value'];
    if (isset($element['#value_suffix'])) {
      $output .= $element['#value_suffix'];
    }
    $output .= '</' . $element['#tag'] . '>';
    return $output;
  }
}

/*
 * This theme used its own version of "all" the JavaScript files needed to play nice.
 * Not meant to be pretty.
 * 
 * Drupal "performance"aggregate JS files is a joke. We use Closure Tools
 * See: http://code.google.com/closure/
 * e.g.,* java -jar closure-compiler.jar --js ../build/OpenLayers.js --js_output_file oembed-min.js
 */
function dlts_book_oembed_js_alter(&$javascript) {
  $settings = drupal_array_merge_deep_array($javascript['settings']['data']);
  
  /*
   * Make sure DLTS is part of the settings
   */
  if ( isset($settings['dlts']) ) {
    $dlts_book_oembed = drupal_get_path('theme', 'dlts_book_oembed');
    $javascript = array();
    
    /*
     * Our JS version. Highly optimize for this theme.
     */
    $javascript[ $dlts_book_oembed . '/js/oembed-min.js'] = array(
        'group' => -100,
        'type' => 'file',
        'every_page' => '',
        'weight' => 0.008,
        'scope' => 'header',
        'cache' => 1,
        'defer' => '',
        'preprocess' => 1,
        'version' => '',
        'data' => $dlts_book_oembed . '/js/oembed-min.js',
    );
    
    /*
     * Init page
     * See: OpenLayers.Init.Page
     */
    
    $regions = array();
    $boxes = '[]';

    if ( isset($settings['dlts']['regions']) ) {
      foreach ( $settings['dlts']['regions']['terms'] as $term ) {        
        $regions[] = $term['coordinates'];
      }
      $boxes = drupal_json_encode($regions);
    }
        
    $options = '{zoom:1, boxes: ' . $boxes .'}';
    
    $javascript['init'] = array(
        'group' => -100,
        'type' => 'inline',
        'every_page' => '',
        'weight' => 5,
        'scope' => 'header',
        'cache' => 1,
        'defer' => TRUE,
        'preprocess' => 1,
        'version' => '',
        'data' => '(function(OpenLayers){OpenLayers.DLTS.Page("'. $settings['dlts']['image']['filepath'][0]['id'] .'","'. $settings['dlts']['image']['filepath'][0]['url'] .'","' . $settings['dlts']['image']['service'] . '", "' . $settings['dlts']['image']['metadata'] .'",'.$options.');})(OpenLayers);',
    );

    unset($dlts_book_oembed);
    unset($settings);
  }
  else {
    // For now: Leave $javascript as it is.
  }
}

/*
 * CSS
 * Not meant to be pretty. We know what we want we get it.
 * @TODO: Need more work
 */
function dlts_book_oembed_css_alter(&$css) {
  $dlts_media = drupal_get_path('theme', 'dlts_media');
  $dlts_book = drupal_get_path('theme', 'dlts_book');
  $dlts_book_oembed = drupal_get_path('theme', 'dlts_book_oembed');
  $dlts_image = drupal_get_path('module', 'dlts_image');
  $css = array(
  $dlts_media . '/css/global.css' => $css[ $dlts_media . '/css/global.css'],
    $dlts_book . '/css/book.css' => $css[ $dlts_book . '/css/book.css'],
    $dlts_book_oembed . '/css/dlts_book_oembed.css' => $css[ $dlts_book_oembed . '/css/dlts_book_oembed.css'],
    $dlts_image . '/css/dlts_image.css' => $css[ $dlts_image . '/css/dlts_image.css'],
  );
  unset($dlts_media);
  unset($dlts_book);
  unset($dlts_book_oembed);
  unset($dlts_image);
}