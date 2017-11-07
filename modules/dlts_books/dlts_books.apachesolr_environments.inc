<?php
/**
 * @file
 * dlts_books.apachesolr_environments.inc
 */

/**
 * Implements hook_apachesolr_environments().
 */
function dlts_books_apachesolr_environments() {
  $export = array();

  $environment = new stdClass();
  $environment->api_version = 1;
  $environment->env_id = 'solr';
  $environment->name = 'Discovery';
  $environment->url = 'http://discovery.dlib.nyu.edu:8080/solr3_discovery/core0';
  $environment->service_class = '';
  $environment->conf = array(
    'apachesolr_read_only' => '0',
    'apachesolr_search_changed_boost' => '0:0',
    'apachesolr_search_comment_boost' => '0:0',
    'apachesolr_search_date_boost' => '0:0',
    'apachesolr_search_promote_boost' => '0',
    'apachesolr_search_sticky_boost' => '0',
    'apachesolr_search_type_boosts' => array(
      'article' => '0',
      'page' => '0',
      'dlts_book' => '0',
      'dlts_book_page' => '0',
      'dlts_book_section' => '0',
      'dlts_book_stitched_page' => '0',
    ),
    'field_bias' => array(
      'base_url' => '0',
      'bm_field_visible' => '0',
      'bs_field_visible' => '0',
      'bs_promote' => '0',
      'bs_status' => '0',
      'bs_sticky' => '0',
      'bs_translate' => '0',
      'bundle' => '0',
      'bundle_name' => '0',
      'collection_abstract' => '0',
      'collection_call_number' => '0',
      'collection_code' => '0',
      'collection_creator' => '0',
      'collection_id' => '0',
      'collection_title' => '0',
      'collection_type' => '0',
      'content' => '8.0',
      'dc_identifier' => '0',
      'dm_field_date' => '0',
      'dm_field_publication_date' => '0',
      'dm_field_publication_date_end' => '0',
      'ds_changed' => '0',
      'ds_created' => '0',
      'ds_last_comment_or_change' => '0',
      'entity_id' => '0',
      'entity_type' => '0',
      'hash' => '0',
      'id' => '0',
      'im_field_binding_orientation' => '0',
      'im_field_book' => '0',
      'im_field_hand_side' => '0',
      'im_field_page_type' => '0',
      'im_field_photo_collection' => '0',
      'im_field_photo_set' => '0',
      'im_field_playlist_ref' => '0',
      'im_field_read_order' => '0',
      'im_field_scan_order' => '0',
      'im_field_subject' => '0',
      'im_field_subject_ref' => '0',
      'im_vid_1' => '0',
      'is_comment_count' => '0',
      'is_field_binding_orientation' => '0',
      'is_field_hand_side' => '0',
      'is_field_page_type' => '0',
      'is_field_read_order' => '0',
      'is_field_scan_order' => '0',
      'is_tnid' => '0',
      'is_uid' => '0',
      'itm_field_container_box' => '0',
      'itm_field_container_folder' => '0',
      'itm_field_item_count' => '0',
      'itm_field_page_count' => '0',
      'itm_field_sequence_count' => '0',
      'itm_field_sequence_number' => '0',
      'its_field_container_box' => '0',
      'its_field_container_folder' => '0',
      'its_field_item_count' => '0',
      'its_field_page_count' => '0',
      'its_field_sequence_count' => '0',
      'its_field_sequence_number' => '0',
      'label' => '5.0',
      'path' => '0',
      'path_alias' => '0',
      'repository_code' => '0',
      'repository_name' => '0',
      'site' => '0',
      'sm_vid_The_Masses_Subject_Terms' => '0',
      'sort_identifer' => '0',
      'sort_label' => '0',
      'sort_language' => '0',
      'sort_name' => '0',
      'sort_name_formatted' => '0',
      'sort_representative_image' => '0',
      'spell' => '0',
      'ss_identifer' => '0',
      'ss_language' => '0',
      'ss_name' => '0',
      'ss_name_formatted' => '0',
      'ss_representative_image' => '0',
      'tags_a' => '0',
      'tags_h1' => '5.0',
      'tags_h2_h3' => '3.0',
      'tags_h4_h5_h6' => '2.0',
      'tags_inline' => '1.0',
      'taxonomy_names' => '2.0',
      'tid' => '0',
      'timestamp' => '0',
      'tm_vid_1_names' => '0',
      'tos_content_extra' => '0.1',
      'tos_name' => '3.0',
      'tos_name_formatted' => '0',
      'ts_collection_creator' => '0',
      'ts_collection_id' => '0',
      'ts_collection_type' => '0',
      'ts_comments' => '0.5',
      'ts_extracted' => '21.0',
      'ts_ocr' => '0',
      'ts_partner_name' => '0',
      'url' => '0',
    ),
  );
  $environment->index_bundles = array(
    'node' => array(
      0 => 'dlts_book',
      1 => 'dlts_book_page',
    ),
  );
  $export['solr'] = $environment;

  return $export;
}
