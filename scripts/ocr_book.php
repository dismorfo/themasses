<?php

/** A command-line Drupal script for concatenate book pages OCR text in a dlts_book_page node. Usage: drush scr ocr_book.php */

if (!defined('__DIR__') ) define('__DIR__', dirname(__FILE__));

/** Load utilities */
module_load_include('inc', 'dlts_utilities', 'inc/dlts_utilities.book_page');

/** Query db for all the books */
$results = db_query('SELECT nid FROM {node} WHERE type = :type', array(':type' => 'dlts_book'));

$books_count = $results->rowCount();

$i = 0;

$ocr_dir_path = __DIR__ . '/ocr';

$ocr_dir = drupal_mkdir($ocr_dir_path);

foreach ($results as $value) {
  
  $i++;
  
  /** For each book concatenate OCR text into $ocr_text */
  $ocr = '';
  $ocr_text = '';

  /** Load book by nid */
  $book_node = node_load($value->nid);

  /** Get book identifier */
  $identifier = dlts_utilities_field_get_first_item('node', $book_node, 'field_identifier');
  
  $book_dir_path = $ocr_dir_path . '/' . $identifier['safe_value'];
  
  $book_dir = drupal_mkdir($book_dir_path);
  
  $ocr_book_file = $book_dir_path . '/' . $identifier['safe_value'] . '.txt';
  $ocr_book_file_html = $book_dir_path . '/' . $identifier['safe_value'] . '.html';
  
  drush_print(dt('Book @book_count out of @books_count (@book_identifier)', array('@books_count' => $books_count,'@book_count' => $i, '@book_identifier' => $identifier['safe_value'])));
  
  /** Add book title to the OCR text */
  $ocr .= '<h1>' . $book_node->title . '</h1>';

  /** Get all book pages by the book identifier */
  $query_book_pages = new EntityFieldQuery();

  $query_book_pages
    ->entityCondition('entity_type', 'node', '=')
    ->entityCondition('bundle', 'dlts_book_page')
    ->propertyCondition('status', 1)
    ->fieldCondition('field_is_part_of', 'value', $identifier['safe_value'], '=')
    ->addMetaData('account', user_load(1));
  
  $result = $query_book_pages->execute();
  
  /** Test for results */
  if (isset($result['node'])) {

    /** Get the keys from the results array, each id represent a book page nid */
    $nids = array_keys($result['node']);
    
    /** Load book page */    
    $book_pages = entity_load('node', $nids);
    
    foreach ($book_pages as $book_page) {
      
      $sequence_number = dlts_utilities_book_page_get_sequence_number($book_page);
      
      $ocr_book_page_file =  $book_dir_path . '/' . $identifier['safe_value'] . '-' . $sequence_number. '.txt';
      
      /** Concatenate book pages into $ocr_text */
      $ocr_text = dlts_utilities_field_get_first_item('node', $book_page, 'field_ocr_text');
      
      /** OCR text */
      if (!empty($ocr_text['safe_value'])) {
      
        if (!file_exists($ocr_book_page_file)) {
          file_put_contents($ocr_book_page_file, trim($ocr_text['safe_value']));
        }
        
        else {
          unlink($ocr_book_page_file);
          file_put_contents($ocr_book_page_file, trim($ocr_text['safe_value']));
        }
        
        $ocr .= '<p>' . trim($ocr_text['safe_value']) . '</p>';
      }
    }
  }
  
  file_put_contents($ocr_book_file_html, $ocr);
  file_put_contents($ocr_book_file, $ocr);
  
}