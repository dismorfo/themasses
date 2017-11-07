

// function dlts_solr_cron_queue_info() {
  // drupal_set_message(t('dlts_solr_cron_queue_info'));

  // $queues['dlts_book_ocr_text'] = array(
  //  'worker callback' => 'dlts_solr_orc_processor',
  //  'time' => 60,
  // );
  // return $queues;
// }

/*
 * http://api.drupal.org/api/drupal/modules--aggregator--aggregator.module/function/aggregator_cron/7
 */

// function dlts_solr_cron() {
  // drupal_set_message(t('dlts_solr_cron'));
// }

/*
 * http://api.drupal.org/api/drupal/modules--system--system.queue.inc/group/queue/7
 * http://api.drupal.org/api/drupal/modules--system--system.api.php/function/hook_cron_queue_info/7
 */

// function dlts_solr_orc_processor() {

  // drupal_set_message(t('dlts_solr_cron_queue_info'));

  /*
   * dpm('dlts_solr_orc_processor');
   */

  // $queue = DrupalQueue::get('dlts_book_ocr_text');
  //   $queue->createQueue();  // There is no harm in trying to recreate existing.
  // $items = array();
  //   while ($item = $queue->claimItem() ) {
  //     $items[] = $item;
  //   }
  //   foreach ($items as $item) {
  //     $queue->releaseItem($item);
  //   }

// }


/*
 * I might be albe to use this to add a JS to stop submit if q < 4
 */

/**
 * Added form submit function to retain filters.
 *
 * @see apachesolr_search_form_search_form_alter()

function apachesolr_search_form_search_submit($form, &$form_state) {
  $fv = $form_state['values'];
  $get = json_decode($fv['apachesolr_search']['get'], TRUE);
  if (!empty($fv['apachesolr_search']['retain-filters'])) {
    $get['retain-filters'] = '1';
    // Add the query values into the redirect.
    $form_state['redirect'] = array($form_state['redirect'], array('query' => $get));
  }
}
*/

/*
 * Adding a module path to Drupal 7 theme registry
 * Implements hook_theme_registry_alter()
 * See: http://www.metachunk.com/blog/adding-module-path-drupal-7-theme-registry
 *
 * TODO: We need this? Maybe is just here for all the wrong reasons. By the way, I
 * was the one who add it (aof)
 */
function dlts_solr_theme_registry_alter(&$theme_registry) {
  $mod_path = drupal_get_path('module', 'dlts_solr');
  $theme_registry_copy = $theme_registry;
  _theme_process_registry($theme_registry_copy, 'phptemplate', 'theme_engine', 'pow', $mod_path);
  $theme_registry += array_diff_key($theme_registry_copy, $theme_registry);
  $hooks = array('node');
  foreach ($hooks as $h) {
    _dlts_solr_insert_after_first_element($theme_registry[$h]['theme paths'], $mod_path);
  }
}

/**
 * Helper function for re-ordering arrays (needed by theme_registry_alter)
 * See: dlts_solr_theme_registry_alter()
 */
function _dlts_solr_insert_after_first_element(&$a, $element) {
  if(is_array($a)) {
    $first_element = array_shift($a);
    array_unshift($a, $first_element, $element);
  }
}

/**
 * Allows a module to change the contents of the $document object before it is
 * sent to the Solr Server.
 */
function dlts_solr_apachesolr_update_index($document, $node) {
  global $base_url;

  $document->addField('base_url', $base_url );
  $document->addField('nyu_collectionId', variable_get('dlts_solr_field_nyu_collectionId', apachesolr_site_hash()) );
  switch ($node->type) {
    case 'dlts_book_page':
      $book_nid = field_get_items( 'node', $node, 'field_book' );
      $field_ocr_text = field_get_items( 'node', $node, 'field_ocr_text' );

      if ( isset($field_ocr_text[0]['value']) ) {
        $ocr = strip_tags($field_ocr_text[0]['value']);
        $document->addField('ts_ocr', $ocr );

        /*
         * Add OCR text to content
         */
        $content = $document->content . ' ' . $ocr;
        unset($document->content);
        $document->addField('content', $content );
      }

      /*
       * Add the book identifer to the document.
       * We only care for the first item in the array.
       */

      if ( $book = node_load($book_nid[0]['nid']) ) {
        $identifer = field_get_items( 'node', $book, 'field_identifer' );
        if (isset($identifer[0]['safe_value'])) {
          $document->addField('ss_identifer', $identifer[0]['safe_value']);
        }
      }

      break;

    case 'dlts_book':
      $identifer = field_get_items( 'node', $node, 'field_identifer' );

      /*
       * We only care for the "safe_value" of the first item in the array.
       */

      if (isset($identifer[0]['safe_value'])) {
        $document->addField('ss_identifer', $identifer[0]['safe_value']);
      }

      /*
       * Don't do this! Just testing ...

      $ocr = '';
      $query = "SELECT
                  o.field_ocr_text_value as ocr
                FROM {field_data_field_book} b
                  LEFT JOIN {node} n ON n.vid = b.entity_id
                  LEFT JOIN {field_data_field_ocr_text} o ON o.entity_id = n.nid
                WHERE field_book_nid = :bnid
                AND n.status > 0";

      $result = db_query( $query, array(':bnid' => $node->nid, ) );
      while( $record = $result->fetchAssoc() ) {
        $ocr .= $record['ocr'];
      }
      $content = $document->content . ' ' . $ocr;
      unset($document->content);
      $document->addField('content', $content );

      // Don't do this end

      */
      break;

    default:
      // do something else
  }

}