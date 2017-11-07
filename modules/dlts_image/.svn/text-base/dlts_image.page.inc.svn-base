<?php

/**
 * @file
 *   Menu callbacks for the DLTS Image module.
 */

/**
 * Get metadata about an image from a Djatoka server.
 *
 *
 * @param $file
 *   A file fid.
 *
 * @return
 *   An array suitable for converting into JSON
 *
 * @see drupal_json_output
 */

function dlts_image_getMetadata($resource) {
  return dlts_image_djatoka_request( ( ( $item = file_load( $resource ) ) ?  $item : dlts_image_resolve($resource) ) , 'info:lanl-repo/svc/getMetadata');
}

function dlts_image_djatoka_ping() {
  return dlts_image_djatoka_request( array( 'uri' => drupal_get_path('module', 'dlts_image') . '/img/djatoka-ping.jp2' ), 'info:lanl-repo/svc/ping');
}

/*
 * Validate URL. For now a hack
 */

function dlts_image_resolve($fid) {
  // find if we have a valid URL.
  if ( $fid === '0' ) {
   return array(
     'uri' => 'http://memory.loc.gov/gmd/gmd433/g4330/g4330/np000066.jp2',
   );
  }
  return FALSE;
}

/*
 * Remove
 */

function dlts_image_metadata($resource) {
  return dlts_image_getMetadata($resource);
}