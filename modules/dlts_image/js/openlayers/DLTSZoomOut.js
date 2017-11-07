/* ======================================================================
    OpenLayers/Control/DLTSZoomOut.js
   ====================================================================== */

/* Copyright (c) 2006-2011 by OpenLayers Contributors (see authors.txt for 
 * full list of contributors). Published under the Clear BSD license.  
 * See http://svn.openlayers.org/trunk/openlayers/license.txt for the
 * full text of the license. */

/**
 * @requires OpenLayers/Control.js
 */

/**
 * Class: OpenLayers.Control.DLTSZoomOut
 * The ZoomOut control is a button to decrease the zoom level of a map.
 *
 * Inherits from:
 *  - <OpenLayers.Control>
 */
OpenLayers.Control.DLTSZoomOut = OpenLayers.Class(OpenLayers.Control, {

    /**
     * Property: type
     * {String} The type of <OpenLayers.Control> -- When added to a 
     *     <Control.Panel>, 'type' is used by the panel to determine how to 
     *     handle our events.
     */
    type: OpenLayers.Control.TYPE_BUTTON,
    
    /**
     * Method: trigger
     */
    trigger: function() {
        this.map.zoomOut();
        var zoomInDiv = this.map.getControlsByClass('OpenLayers.Control.DLTSZoomIn')[0].panel_div;
        var zoomOutDiv = this.map.getControlsByClass('OpenLayers.Control.DLTSZoomOut')[0].panel_div;
        
        if ( this.map.zoom === 0 ) {
          OpenLayers.Element.addClass(zoomOutDiv, 'zoom_out_max');
        }
        else {
          if (OpenLayers.Element.hasClass(zoomInDiv, 'zoom_in_max')) {
            OpenLayers.Element.removeClass(zoomInDiv, 'zoom_in_max');
          }
        }        
    },

    CLASS_NAME: "OpenLayers.Control.DLTSZoomOut"
});