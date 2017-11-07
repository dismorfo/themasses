<?php

/**
 * @file
 *   drush integration for apachesolr.
 */

/**
 * Implements hook_drush_command().
 *
 * In this hook, you specify which commands your
 * drush module makes available, what it does and
 * description.
 *
 * Notice how this structure closely resembles how
 * you define menu hooks.
 *
 * @see drush_parse_command()
 *   for a list of recognized keys.
 *
 * @return
 *   An associative array describing your command(s).
 */
function dlts_site_metadata_drush_command() {
  $items = array();
  $items['dlts-sm-add'] = array(
    'callback' => 'dlts_solr_drush_solr_mark_for_reindex',
    'description' => dt('Lolo'),
    'arguments' => array(
      'types' => dt('Optional. A space delimited list of content types to be deleted from the index.'),
    ),
  );

  return $items;
}

/**
 * Implements hook_drush_help().
 *
 * This function is called whenever a drush user calls
 * 'drush help <name-of-your-command>'
 *
 * @param
 *   A string with the help section (prepend with 'drush:')
 *
 * @return
 *   A string with the help text for your command.
 */
function dlts_site_metadata_drush_help($section) {
  switch ($section) {
    case 'drush:solr-delete-index':
      return dt("Lala");
  }
}

/**
 * Example drush command callback.
 *
 * This is where the action takes place.
 *
 * In this function, all of Drupals API is (usually) available, including
 * any functions you have added in your own modules/themes.
 *
 * To print something to the terminal window, use drush_print().
 *
 */
function dlts_site_metadata_drush_solr_delete_index() {
  module_load_include('inc', 'apachesolr', 'apachesolr.index');
  $args = func_get_args();
  $env_id = apachesolr_default_environment();
  apachesolr_index_delete_index($env_id);
  drush_print(t('Deleted the Solr index'));
}

function dlts_site_metadata_drush_solr_mark_for_reindex() {
  module_load_include('inc', 'apachesolr', 'apachesolr.index');
  $args = func_get_args();
  $env_id = apachesolr_default_environment();
  if (count($args) > 0) {
    foreach ($args as $type) {
      apachesolr_index_mark_for_reindex($env_id, $type);
    }
  }
  else {
    apachesolr_index_mark_for_reindex($env_id);
  }
  drush_print(t('Marked content for reindexing'));
}

function dlts_site_metadata_drush_solr_index() {
  module_load_include('inc', 'apachesolr', 'apachesolr.admin');
  module_load_include('inc', 'apachesolr', 'apachesolr.index');
  $env_id = apachesolr_default_environment();
  apachesolr_index_batch_index_remaining($env_id);
  drush_backend_batch_process();
}

function dlts_site_metadata_drush_solr_search() {
  $args = func_get_args();
  $keys = implode(' ', $args);
  foreach (apachesolr_search_search_execute($keys) as $result) {
    $output = 'node/' . $result['node']->entity_id . ' ' . dt('by @name (user/@uid)', array('@name' => strip_tags($result['user']), '@uid' => $result['node']->is_uid)) . "\n";
    $output .= dt('title: ') . $result['title'] . "\n";
    $output .= preg_replace('/[\s]+/', ' ', strip_tags($result['snippet'])) . "\n\n";
    drush_print($output);
  }
}
