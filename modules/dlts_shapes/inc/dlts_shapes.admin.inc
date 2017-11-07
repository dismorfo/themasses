<?php

/**
 * OCR word shape service Admin Form
 */
function dlts_shapes_settings($form, &$form_state) {

  $form['dlts_shapes_field'] = array(
    '#type' => 'fieldset',
    '#title' => t('OCR word shape service'),
    '#collapsed' => FALSE,
    '#collapsible' => FALSE,
  );
  
  $form['dlts_shapes_field']['dlts_shapes_services_url'] = array(
    '#type' => 'textfield',
    '#title' => t('URL'),
    '#default_value' => variable_get('dlts_shapes_services_url', 'http://localhost:8983/ocr'),
    '#size' => 60,
    '#maxlength' => 100,
    '#description' => t('e.g., http://localhost:8983/ocr'),
  );
  
  $url = variable_get('dlts_shapes_services_url', 'http://localhost:8983/ocr');
  
  /*
   * Ping OCR Word Shape Service server
   */
  
  try {
    $service = dlts_shapes_get_service('dlts_shapes', 'solr');
    $service->setUrl($url);
    $ping = $service->ping();
    $value = $ping ? t('Your site has contacted the OCR Word Shape Service server.') : t('Your site was unable to contact the OCR Word Shape Service server.');    
    drupal_set_message($value);   
  }
  catch (Exception $e) {
    watchdog('OCR Word Shape Service', nl2br(check_plain($e->getMessage())) . ' in ocrapp_settings', NULL, WATCHDOG_ERROR);
  }  
  return system_settings_form($form);
}