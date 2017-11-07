<?php
/**
 * @file
 * dlts_books.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function dlts_books_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "apachesolr" && $api == "apachesolr_environments") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "apachesolr_search" && $api == "apachesolr_search_defaults") {
    return array("version" => "3");
  }
  list($module, $api) = func_get_args();
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function dlts_books_views_api() {
  return array("version" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function dlts_books_image_default_styles() {
  $styles = array();

  // Exported image style: dlts-admin-thumbnail.
  $styles['dlts-admin-thumbnail'] = array(
    'name' => 'dlts-admin-thumbnail',
    'effects' => array(
      6 => NULL,
      5 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => '100',
          'height' => '100',
          'upscale' => 1,
        ),
        'weight' => '-9',
      ),
    ),
  );

  // Exported image style: dlts-book-image.
  $styles['dlts-book-image'] = array(
    'name' => 'dlts-book-image',
    'effects' => array(
      1 => NULL,
      2 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => '200',
          'upscale' => 0,
        ),
        'weight' => '-9',
      ),
    ),
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function dlts_books_node_info() {
  $items = array(
    'dlts_book' => array(
      'name' => t('Book'),
      'base' => 'node_content',
      'description' => t('Anything derived from either a bound set of pages designed to be read (books, pamphlets, etc.), or an electronic format such as ePub or PDF that uses virtual sections or pages, or both. Examples include: AWDL; NYUP; Morgan Claypool'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'dlts_book_page' => array(
      'name' => t('Book Page'),
      'base' => 'node_content',
      'description' => t('Data derived from a single paper or electronic page'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'dlts_book_section' => array(
      'name' => t('Book Section'),
      'base' => 'node_content',
      'description' => t('A non-overlapping subset of pages of a book. '),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => t('This content type is not intended to carry information about rhetorical sections of a book - preface, etc. It is only intended to hold data derived from \'post-pagination\' sources such as ePub. A book can have pages and sections but only if it is derived from diverse materials that follow both models. A book derived from scanning or from dismemberment of paginated PDFs only will not have sections.

In early NYUP documentation, this was called \'_chapter\' - section is replacing \'_chapter\' because it is more generic. '),
    ),
    'dlts_book_stitched_page' => array(
      'name' => t('Book Stitched Page'),
      'base' => 'node_content',
      'description' => t('Two pages of a DLTS Book stitched together into a single image.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
