/* ======================================================================
    OpenLayers/Control/DLTSZoomIn.js
   ====================================================================== */

/* Copyright (c) 2006-2011 by OpenLayers Contributors (see authors.txt for 
 * full list of contributors). Published under the Clear BSD license.  
 * See http://svn.openlayers.org/trunk/openlayers/license.txt for the
 * full text of the license. */

/**
 * @requires OpenLayers/Control.js
 */

/**
 * Class: OpenLayers.Control.DLTSZoomIn
 * The ZoomIn control is a button to increase the zoom level of a map.
 *
 * Inherits from:
 *  - <OpenLayers.Control>
 */

OpenLayers.Control.DLTSZoomIn = OpenLayers.Class(OpenLayers.Control, {

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
        this.map.zoomIn();
        var zoomIdDiv = this.map.getControlsByClass('OpenLayers.Control.DLTSZoomIn')[0].panel_div;
        var zoomOutDiv = this.map.getControlsByClass('OpenLayers.Control.DLTSZoomOut')[0].panel_div;
        if ( this.map.zoom === ( this.map.resolutions.length - 1 ) ) {
          OpenLayers.Element.addClass(zoomIdDiv, 'zoom_in_max');
        }
        else {
          if (OpenLayers.Element.hasClass(zoomOutDiv, 'zoom_out_max')) {
            OpenLayers.Element.removeClass(zoomOutDiv, 'zoom_out_max');
          }
        }
    },

    CLASS_NAME: "OpenLayers.Control.DLTSZoomIn"
});