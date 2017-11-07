<?php
/**
 * @file
 * dlts_books.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function dlts_books_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_descriptive_metadata|node|dlts_book|form';
  $field_group->group_name = 'group_descriptive_metadata';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'dlts_book';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Descriptive Metadata',
    'weight' => '4',
    'children' => array(
      0 => 'field_author',
      1 => 'field_contributor',
      2 => 'field_creator',
      3 => 'field_description',
      4 => 'field_dimensions',
      5 => 'field_editor',
      6 => 'field_language',
      7 => 'field_language_code',
      8 => 'field_number',
      9 => 'field_other_version',
      10 => 'field_page_count',
      11 => 'field_publication_date',
      12 => 'field_publisher',
      13 => 'field_sequence_count',
      14 => 'field_subject',
      15 => 'field_subtitle',
      16 => 'field_volume',
      17 => 'field_title',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_descriptive_metadata|node|dlts_book|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_descriptive_metadata|node|dlts_book|metadata';
  $field_group->group_name = 'group_descriptive_metadata';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'dlts_book';
  $field_group->mode = 'metadata';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Descriptive Metadata',
    'weight' => '1',
    'children' => array(
      0 => 'field_author',
      1 => 'field_contributor',
      2 => 'field_creator',
      3 => 'field_description',
      4 => 'field_dimensions',
      5 => 'field_editor',
      6 => 'field_handle',
      7 => 'field_language',
      8 => 'field_number',
      9 => 'field_other_version',
      10 => 'field_page_count',
      11 => 'field_pdf_file',
      12 => 'field_publication_date',
      13 => 'field_publisher',
      14 => 'field_sequence_count',
      15 => 'field_subject',
      16 => 'field_subtitle',
      17 => 'field_title',
      18 => 'field_volume',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Descriptive Metadata',
      'instance_settings' => array(
        'classes' => '',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_descriptive_metadata|node|dlts_book|metadata'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_essence|node|dlts_book_page|form';
  $field_group->group_name = 'group_essence';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'dlts_book_page';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Essence',
    'weight' => '8',
    'children' => array(
      0 => 'field_cropped_master',
      1 => 'field_ocr_text',
      2 => 'field_service_copy',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_essence|node|dlts_book_page|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_essence|node|dlts_book|form';
  $field_group->group_name = 'group_essence';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'dlts_book';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Essence',
    'weight' => '3',
    'children' => array(
      0 => 'field_ocr_text',
      1 => 'field_pdf_file',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_essence|node|dlts_book|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_essence|node|dlts_book|metadata';
  $field_group->group_name = 'group_essence';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'dlts_book';
  $field_group->mode = 'metadata';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Essence',
    'weight' => '4',
    'children' => array(
      0 => 'field_ocr_text',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_essence|node|dlts_book|metadata'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_structural_metadata|node|dlts_book|form';
  $field_group->group_name = 'group_structural_metadata';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'dlts_book';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Structural Metadata',
    'weight' => '6',
    'children' => array(
      0 => 'field_read_order',
      1 => 'field_scan_order',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_structural_metadata|node|dlts_book|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_structural_metadata|node|dlts_book|metadata';
  $field_group->group_name = 'group_structural_metadata';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'dlts_book';
  $field_group->mode = 'metadata';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Structural Metadata',
    'weight' => '2',
    'children' => array(
      0 => 'field_read_order',
      1 => 'field_scan_order',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_structural_metadata|node|dlts_book|metadata'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_technical_metadata|node|dlts_book|form';
  $field_group->group_name = 'group_technical_metadata';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'dlts_book';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Technical Metadata',
    'weight' => '7',
    'children' => array(
      0 => 'field_scan_date',
      1 => 'field_scanning_notes',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_technical_metadata|node|dlts_book|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_technical_metadata|node|dlts_book|metadata';
  $field_group->group_name = 'group_technical_metadata';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'dlts_book';
  $field_group->mode = 'metadata';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Technical Metadata',
    'weight' => '3',
    'children' => array(
      0 => 'field_scan_date',
      1 => 'field_scanning_notes',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_technical_metadata|node|dlts_book|metadata'] = $field_group;

  return $export;
}
