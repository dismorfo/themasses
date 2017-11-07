<?php

function dlts_solr_series_book_by_book_nid ( $entity ) {

  $query = new EntityFieldQuery;
  
  $keys = array () ; 
  
  $result = $query->entityCondition('entity_type', 'node')
                  ->entityCondition('bundle', 'dlts_series_book')
                  ->fieldCondition('field_book', 'nid', array( $entity->nid ) )
                  ->execute();
  
  if ( !empty ( $result['node'] ) ) $keys = array_keys( $result['node'] ) ;
  
  return $keys  ;
  
}

function dlts_solr_index_book ( &$document, &$entity, $entity_type, $env_id ) {

  /** add book utilities functions */
  module_load_include('inc', 'dlts_utilities', 'inc/dlts_utilities.book');

  /** add collection utilities functions */
  module_load_include('inc', 'dlts_utilities', 'inc/dlts_utilities.collection');

  /** add series utilities functions */
  module_load_include('inc', 'dlts_utilities', 'inc/dlts_utilities.series');
  
  $identifier = dlts_utilities_book_get_identifier ( $entity ) ;  

  /** DLTS book should have a unique identifier */  
  if ( ! $identifier ) return ;
  
  /** searchable content; dump all you want to be searchable in this array */
  $searchableFields = array( $document->content );

  $book_field_title = dlts_utilities_book_get_title($entity);

  $partners = dlts_utilities_book_get_partner($entity);

  $isbns = dlts_utilities_book_get_isbn( $entity );

  $subtitle = dlts_utilities_book_get_subtitle($entity);

  $authors = dlts_utilities_book_get_authors($entity);

  $description = dlts_utilities_book_get_description($entity);

  $creators = dlts_utilities_book_get_creator($entity);

  $contributors = dlts_utilities_book_get_contributor($entity);

  $publishers = dlts_utilities_book_get_publisher($entity);

  $editors = dlts_utilities_book_get_editor($entity);   

  $publication_location = dlts_utilities_book_get_publication_location($entity);

  $publication_date = dlts_utilities_book_get_field_publication_date_text($entity);
  
  $publication_date_object = dlts_utilities_book_get_field_publication_date($entity);  

  $subjects_list = dlts_utilities_book_get_subjects($entity);
  
  $book_series = dlts_utilities_book_get_series_book ( $entity ) ;

  $representative_image = dlts_utilities_book_get_representative_image_uri ( $entity ) ;
  
  $books_series = dlts_solr_series_book_by_book_nid ( $entity ) ;  

  /** let $identifier alone while we do a fix across collections */
  $collection_identifiers = dlts_utilities_book_get_collection_identifiers ( $entity ) ;

  foreach ( $collection_identifiers as $collection_identifier ) {
    $document->addField('sm_collection_identifier', $collection_identifier) ;
    /** let $identifier alone while we do a fix across collections */
    $collections_code = dlts_utilities_collection_get_collection_code ( $collection_identifier ) ;
    if ( $collections_code ) {
      $document->addField('sm_collection_code', $collections_code) ;
    }
  }

  $subjects = array();

  foreach ( $subjects_list as $subject ) {
	$subjects[] = $subject->name;
	// allow to loop subject when using mustache
    $document->addField('zm_subject' , json_encode ( array ( 'name' => $subject->name , 'tid' =>  $subject->tid, 'vid' => $subject->vid ) ) ) ;	  	
  }

  $document->addField('ss_identifer', $identifier);
  
  $document->addField('ss_uri', url('books/' . $identifier . '/1', array('absolute' => TRUE)));
  
  $document->addField('ss_embedded', url('books/' . $identifier . '/1', array('absolute' => TRUE, 'query' => array('oembed' => 1))));

  if ( $multivol = dlts_utilities_book_get_multivol_book( $entity ) ) {
    if ( $volume = dlts_utilities_multibook_get_volume( $multivol ) ) {
      $book_field_title = t('@title Vol. @volume', array( '@title' => $book_field_title, '@volume' => $volume ) );
      $document->addField('is_ispartof_multivol', 1) ;
      $document->addField('ss_multivol_number', $volume) ;
      $document->addField('ss_multivol_label', $book_field_title) ;
    }
  }
  else {
    $document->addField('is_ispartof_multivol', 0) ;
  }
  
  if ( $books_series ) {

    $document->addField( 'is_ispartof_series', 1 ) ;
    
    foreach ( $books_series as $book_series ) {

      $entity_book_series = node_load ( $book_series ) ;
        
      $series = dlts_utilities_series_book_get_series ( $entity_book_series ) ;
      
      $series_volume = dlts_utilities_series_get_volume ( $entity_book_series ) ;
    
      $series_identifier = trim ( dlts_utilities_series_get_identifier ( $series ) ) ;
        
      $document->addField( 'sm_series_label', $series->title . ' v. ' . $series_volume ) ;      

      $document->addField( 'sm_series_identifier', $series_identifier ) ;
      
      $document->addField('iass_series_' . $series_identifier, $series_volume );
      
      $document->addField('zm_series_data' , json_encode ( array ( 'label' => $series->title , 'identifier' =>  $series_identifier, 'volume' => $series_volume ) ) ) ;	  	        

    }
  }
	  
  /** to be dump to content */
  $searchableFields[] = $book_field_title;
  $searchableFields[] = $subtitle;
  $searchableFields[] = $description;   
  $searchableFields[] = $publication_date;
  $searchableFields[] = $publication_location;

  $multi_value_fields = array(
    'partner' => $partners,
    'isbn' => $isbns,    
    'author' => $authors,    
    'creator' => $creators,
    'editor' => $editors,
    'contributor' => $contributors,  
    'publisher' => $publishers,    
    'subject' => $subjects,
  );

  /** multivol value fields */
  foreach ( $multi_value_fields as $label => $fields ) {
    foreach ( $fields as $index => $value ) {
      $searchableFields[] = $value;
      /** sort does not work with multiple values; just get the first one */
      if ( $index == 0 ) {
        $field_value = dlts_solr_remove_accents( strtolower( $value ) ) ;
        $document->addField('ss_s' . $label, $field_value );
        $document->addField('iass_s' . $label, $field_value );
      }
      $document->addField('sm_' . $label, $value);
    }
  }

  /** Shared fields */
  $document->addField('ss_collection_identifier', $collection_identifier);

  /** @TODO: remove this field */
  $document->addField('ss_representative_image', $representative_image);
  
  /** @TODO: remove this field */
  $document->addField('ss_thumbnail', $representative_image);

  if  ( $representative_image = dlts_utilities_book_get_representative_image_file ( $entity ) ) {
    $styles = array_keys ( image_styles() ) ;
	foreach ( $styles as $style ) {
      $document->addField('zs_image_' . $style , image_style_url( $style, $representative_image['uri'] ) ) ;	  
	}
  }

  /** Single value fields */
  $document->addField('ss_title', $book_field_title);

  $document->addField('ss_pubdate', $publication_date);

  $document->addField('ss_publocation', $publication_location);

  // Strip HTML Tags
  $title_sort = strip_tags( $book_field_title );

  // Trim the string of leading/trailing space
  $title_sort = trim($title_sort);

  $title_sort = dlts_solr_remove_accents($title_sort);

  // Clean up things like &amp;
  $title_sort = html_entity_decode($title_sort);

  // Strip out any url-encoded stuff
  $title_sort = urldecode($title_sort);

  // Replace Multiple spaces with single space
  $title_sort = preg_replace('/ +/', ' ', $title_sort);

  // To lower-case
  $title_sort = strtolower( $title_sort );

  /** Sort fields */
  $document->addField('ss_longlabel', $title_sort );
  $document->addField('iass_longlabel', $title_sort );
  $document->addField('ss_spubdate', strtolower($publication_date));
  $document->addField('ss_spublocation', dlts_solr_remove_accents( strtolower($publication_location)));
  $document->addField('ss_scollection', $collection_identifier);

  /** check if this node have data in field_publication_date in Date (ISO format) */
  if ( $publication_date_object['value'] ) {
    /** convert ISO format into UNIX  timestamp */
    $timestamp = strtotime ( $publication_date_object['value'] ) ;  
    /** use date() to get just the year */    
    $publication_year = date ( 'Y' , $timestamp ) ;
    if ( $publication_year ) {
      /** add filed to Solr */    
      $document->addField('sort_pubyear', $publication_year );
      $document->addField('iass_pubyear', $publication_year );      
      $document->addField('iass_timestamp', $timestamp );  
    }
  }
  
  /** add translations helper */
  module_load_include('inc', 'dlts_solr', 'inc/dlts_solr.translations');  

  /** add translations */
  dlts_solr_index_book_translations ( &$document, &$entity, $entity_type, $env_id, $searchableFields ) ;
  
  if ( module_exists('ocr') ) {
    $result = db_query('SELECT value FROM {ocr} WHERE nid = :nid LIMIT 1', array(':nid' => $entity->nid));
    $ocr = $result->fetchField();
    if ( !empty( $ocr ) ) {
      $document->addField('ts_ocr', $ocr);
      $searchableFields[] = $ocr;
    }
  }

  unset( $document->content );
  
  $document->addField('content', implode( $searchableFields, ' ') );

}
