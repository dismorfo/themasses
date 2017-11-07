<?php

/**
 * OCR Clean
 * A command-line Drupal script for pulling HTML tags and entities out of the OCR text 
 * in a dlts_book_page node.
 *
 * Usage:
 * drush scr ocr_clean.php
 */
function ocr_load_include($type, $name = NULL) {
  $file = dirname(__FILE__) . "/inc/$name.$type";
  if (is_file($file)) {
    require_once $file;
  }
  else {
    die('Unable to bootstrap');
  }
}

function remove_array_empty_values($array, $remove_null_number = false) {
  $new_array = $null_exceptions = array();
  foreach ($array as $key => $value) {
    $value = trim($value);
    if ($remove_null_number) {
      $null_exceptions[] = '0';
    }
    if (!in_array($value, $null_exceptions) && $value != '') {
      $new_array[] = $value;
    }
  }
  return $new_array;
}

drush_print('init');

ocr_load_include('php', 'common_english_words');
ocr_load_include('php', 'others');
ocr_load_include('php', 'common_names');

$engliswords = englishWords();
$commonNames = commonNames();
$others = others();

$words_list = array_merge($engliswords, $others);
$words_list = array_merge($engliswords, $commonNames);

$book_plus = 0;

$books_result = db_query('SELECT identifier FROM {dlts_ocr} WHERE extracted = 1 AND cleaned = 0 AND type = :t1', array('t1' => 'dlts_book'));
$books_count = $books_result->rowCount();

foreach ($books_result as $book) {
  $book_plus++;
  drush_print( $book_plus . ' (identifier: ' . $book->identifier . ') out of ' . $books_count );
  
  $book_pages_result = db_query('SELECT nid, oid, body FROM {dlts_ocr} WHERE extracted = 1 AND cleaned = 0 AND identifier = :identifier', array(':identifier' => $book->identifier));
  $books_pages_count = $book_pages_result->rowCount();
  $book_pages_plus = 0;
   
  foreach ($book_pages_result as $book_page) {
  
    $book_pages_plus++;

    drush_print( $book_pages_plus . ' (oid: ' . $book_page->oid . ') out of ' . $books_pages_count );

	  $raw = $book_page->body;
	
    // Not cool, but we' good
	  $raw = str_replace('T H E M A S S E S', 'THE MASSES', $raw);
	  $raw = str_replace("JaUUa1'YÂ»", 'JANUARY', $raw);
	  $raw = str_replace("MQNTI-lLY~", "MONTHLY", $raw);
	  $raw = str_replace("CQMPANY", "COMPANY", $raw);

  	// Start cleaning
	  $raw = htmlspecialchars_decode($raw, ENT_QUOTES);
	  $raw = str_replace('_', ' ', $raw);
    $raw = strip_tags(mb_decode_numericentity($raw, array(0x0, 0xffff, 0, 0xffff), 'UTF-8'));
    
    /** Explode string */
    $raw = explode(' ', $raw);
      
    /** Remove empty values */      
    $raw = remove_array_empty_values($raw);

    $goods = $bads = array();  

    foreach ($raw as $key => $word) {

	    // Test for this cases: 
  	  // 1909.submitted
	    // ours,mental,
	  
      /**
       * If is a number
       */        
      if (is_numeric($word)) {
        $left = $key - 1;
  
        //  Most likely a error  
        if ($word == $raw[$left]) {
          $bads[] = $word;
        }
        else {
          $goods[] = $word;
        }
      }	  
	    else {
	    
        /** Test for a word */        
        if (in_array(strtolower($word), $words_list)) {
          $goods[] = $word;
	      }

	      /** 19st ... 10th */
        elseif (preg_match('/^([0-9]{1,}[th|st]{2})$/i', $word, $matches)) {
          $goods[] = $matches[1];
        }
        
        /** US Currency */
        elseif (preg_match('/^\$((\d{1,3}(\,\d{3})*|(\d+))(\.\d{2})?)$|^(\$\.[0-9]{2})/i', $word, $matches)) {
          $goods[] = $matches[0];
        }

        /** A word can have a non-word character in end */        
        elseif (preg_match('/(.*)([.!?,;:\'-`])$/i', $word, $matches))  {
          if (in_array(strtolower($matches[1]), $words_list)) {
            if (preg_match('/[.,;:!?]{1}/i', $matches[2])) {
              $goods[] = $matches[1] . $matches[2];
            }
            else {
              $goods[] = $matches[1];
            }
          }
          else {
            $bads[] = $matches[1];
          }
        }
        
        /** A word can have a non-word character in front */
        elseif (preg_match('/^[^a-zA-Z]{1,}([a-zA-Z]{1,})$/i', $word, $matches)) {
	        if (in_array(strtolower($matches[1]), $words_list)) {
	          $goods[] = $matches[1];
          }
          else {
            $bads[] = $word;
          }
        }
        else {
          $bads[] = $word;
        }
      }
    }
  
    $safe_value = implode(' ', $goods);
  
    # Update the Table
  
    $num_updated = db_update('dlts_ocr')->fields(
      array(
        'cleaned' => 1,
        'safe_value' => $safe_value,
      )
    )
    ->condition('nid', $book_page->nid, '=')
    ->execute();
  }
}