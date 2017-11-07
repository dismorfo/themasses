<?php

/**
 * Configure Site-specific metadata form
 */

function dlts_solr_search_settings($form, &$form_state) {

  $form['dlts_solr_search'] = array(
    '#type' => 'fieldset',
    '#title' => t('Configure search options for DLTS sites'),
    '#collapsed' => FALSE,
    '#collapsible' => FALSE,
  );

  $form['dlts_solr_search']['dlts_solr_search_multisite'] = array(
    '#type' => 'radios',
    '#title' => t('Enable Multi-Site Search'),
    '#default_value' => variable_get('dlts_solr_search_multisite', 0),
    '#options' => array( 
      0 => t('Disable'),
      1 => t('Enable'), 
    ),
    '#maxlength' => 100,
    '#description' => t('Allow site to search all DLTS Collections'),
  );  
  
  return system_settings_form($form);
}