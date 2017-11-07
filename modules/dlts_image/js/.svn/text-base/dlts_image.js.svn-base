(function ($) {
  Drupal.dlts = Drupal.dlts || {},

  Drupal.behaviors.dlts = {
    attach: function (context, settings) {
      Drupal.dlts.image.init(context, settings);
    }
  };

  Drupal.dlts.image = {
    'init' : function (context, settings) {
      try {
        if (typeof OpenLayers === "object" && typeof settings.dlts.image === "object") {
         for (var image = 0, imageLength = settings.dlts.image.filepath.length; image < imageLength; image++) {
            var element     = settings.dlts.image.filepath[image].id,
                rft_id      = settings.dlts.image.filepath[image].url,
                service     = settings.dlts.image.service,
                metadataUrl = location.protocol + "//" + location.hostname + (location.port ? ":" + location.port : "" ) +
                              settings.basePath + "dlts/image/" + settings.dlts.image.filepath[image].fid + "/metadata";
            Drupal.dlts.image.openlayer(element, rft_id, service, metadataUrl, 1);
          }
        }
        else {
          throw "Err1";
        }
      }
      catch (er) {
        switch (er) {
          case "Err1":
            if (window.console) window.console.log("Not ready.");
            break;
        }
      }
    },
    'maps' : [], // Array to hold references to instances of OpenLayers.Map
    'openlayer' : function( element, rft_id, service, metadataUrl, zoomLevel ) {

        function getServicesURL() {
            return service;
        }

        var params = {
            url_ver: "Z39.88-2004",
            svc_id: "info:lanl-repo/svc/getMetadata",
            rft_id: rft_id,
            layername: "basic",
            format:  "image/jpeg",
            metadataUrl:  metadataUrl
        };
        
        var OUlayer = new OpenLayers.Layer.OpenURL('OpenURL', getServicesURL(), { layername: params.layername, format: params.format, rft_id: params.rft_id, metadataUrl: params.metadataUrl });
      
        var metadata = OUlayer.getImageMetadata();
      
      
        var options = {
            center: new OpenLayers.LonLat( metadata.width / 2, metadata.height / 2),
            zoom: zoomLevel,
            layers: [ OUlayer ],
            theme: null,
            resolutions: OUlayer.getResolutions(),
            maxExtent: new OpenLayers.Bounds(0, 0, metadata.width, metadata.height),
            tileSize: OUlayer.getTileSize(), 
            controls: []
        };
        
        var controls = [
            new OpenLayers.Control.KeyboardDefaults(),
            new OpenLayers.Control.Attribution(),
            new OpenLayers.Control.DLTSZoomInPanel({div: OpenLayers.Util.getElement("control-zoom-in") }),
            new OpenLayers.Control.DLTSZoomOutPanel({div: OpenLayers.Util.getElement("control-zoom-out") }),            
            new OpenLayers.Control.Navigation({
                dragPanOptions: {
                    enableKinetic: true
                },
                zoomWheelEnabled: false
            }),
            new OpenLayers.Control.ScrollWheel(),            
            new OpenLayers.Control.TouchNavigation({
              dragPanOptions: {
                     enableKinetic: true
                 }
            })         
        ];
     
        var map = new OpenLayers.Map(element, options);

        map.addControls(controls);      
      
        // Instances of OpenLayers.Map
        map.pan(0, (((map.getSize().h - (map.getTileSize().h * map.resolutions[(map.resolutions.length - (map.getZoom() + 1))])) / 2) - 5));

        // Create a reference to "this" map
        Drupal.dlts.image.maps.push(map);
    }
  };
})(jQuery);