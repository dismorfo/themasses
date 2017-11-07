Y.use('handlebars', 'node-base', 'datasource-get', 'datasource-jsonschema', 'datasource-cache', 'cache-offline', function (Y) {
    'use strict';
    
    // http://annotations.dlib.nyu.edu/home/demos/0002/json.annotations.php
    // https://github.com/caridy/yui3-gallery/blob/master/src/gallery-get-selection/js/get-selection.js

    var D = Y.DLTS,
        Lang = Y.Lang,
        H = Y.Handlebars,
        components = D.components,
        settings = D.settings;
    
    var getBoxesForTarget = function(target) {
        //var annotations = requestToJSON(OpenLayers.Request.issue({ url: 'http://annotations.dlib.nyu.edu/home/demos/0002/json.annotations.php' + '?targetUri=' + target, async: false }));
        //return annotations.response.annotations;
        return [];
    };
    
	Y.DLTS.boxes = {};
    
    var getCoordinates = function(target) {
        var str_coord = getQuerystring('coordinates', undefined, target), coord = [], mas;
        
        if (str_coord) {
        	mas = str_coord.split(',');
            for ( var k in mas ) {
                if (isNaN(mas[k])) {
                    return [];
                }
                coord[k] = parseInt(mas[k]);
            }
        }
        return coord;
    };
  
    var getQuerystring = function(key, default_, from_) {
      
      var regex, qs;
      
      if (default_ == null) {
          default_= ''; 
      }

       if (from_ == null) {
           from = window.location.href;
       }

       key = key.replace(/[\[]/,"\\\[").replace(/[\]]/,"\\\]");

       regex = new RegExp("[\\?&]" + key + "=([^&#]*)");
	   
       qs = regex.exec(from_);
	    
        if (qs == null) {
            return default_;
        }
        else {
            return qs[1];
        }
    };

    var requestToJSON = function(request) {
        if (request.status === 200) {
            return new OpenLayers.Format.JSON().read(request.responseText);
        }
        else {
            return [];
        }
    };
		  
    var buttons = { annotate: Y.one('.button.annotations') };
    
    var templates = {
        input: Y.Handlebars.compile(Y.one('#annotations-input-template').getHTML()),
        body: Y.Handlebars.compile(Y.one('#annotations-body-template').getHTML()),
        annotation: Y.Handlebars.compile(Y.one('#annotations-body-template').getHTML())
    };
  
    var panes = {
        annotate: components.panes.annotate || Y.one('.pane.annotations'),
        navbar: Y.one('.navbar'),
        main: components.panes.main || Y.one('#main'),
        top: components.panes.top || Y.one('#top')
    };
    
    Y.one('.pane.annotations').delegate('hover', function(e) {
    	var vid = e.currentTarget.getAttribute('data-vector');
        e.currentTarget.addClass('highlighted');
        Y.DLTS.constrols.select.highlight(Y.DLTS.boxes[vid].box);
      }, function(e) {
        e.currentTarget.removeClass('highlighted');
        var vid = e.currentTarget.getAttribute('data-vector');
        Y.DLTS.constrols.select.unhighlight(Y.DLTS.boxes[vid].box);
    }, '.docos-box');
     
    Y.one('.pane.annotations').delegate('click', function(e) {
        var elm = e.currentTarget,
           parent = elm.ancestor('.annotations-input');
       Y.DLTS.boxes[parent.getAttribute('data-vector')].destroy();
       parent.remove();
    }, '.docos-input-cancel');
     
    Y.one('.pane.annotations').delegate('click', function(e) {
        var elm = e.currentTarget,
   	        parent = elm.ancestor('.annotations-input'),
   	        textarea = Y.one('.docos-input-textarea'),
   	        feature = Y.DLTS.boxes[parent.getAttribute('data-vector')],
   	        value = textarea.get('value'),
            url = window.location.href + '?coordinates=' + feature.data.coords;
       
        var data = {
            id: 'annon' + Y.DLTS.boxes.length,
            vid: Y.DLTS.boxes[parent.getAttribute('data-vector')].id,
            username: 'Alberto Ortiz Flores',
            text: value,
            modification_date_utc: new Date()
        };

        Y.one('.pane.annotations').append(templates.body(data));
       
        Y.on('io:success', function() {
        	Y.log('io:success');
        	Y.log(this);
            this.remove();
        }, parent);
       
        var uri = 'http://annotations.dlib.nyu.edu/home/demos/0001/add?target=' + url + '&data=' + data.text;

        Y.io(uri);
        
    }, '.docos-input-buttons-post');    

    var onClick = function(e) {
        e.preventDefault();
        if (this.hasClass('on')) {
            this.removeClass('on');
            Y.fire('button:' + this.get('id') + ':off', e);
        }
        else {
            this.addClass('on');
            Y.fire('button:' + this.get('id') + ':on', e);
        }
        Y.fire('button:' + this.get('id') + ':toggle', e);
    };
    
    var boxes;
  
    var searchCallback = {
        success: function(e) {
	        var panes_main_height = panes.main.get("offsetHeight"),
                panes_navbar_height = panes.navbar.get("offsetHeight"),
                panes_top_height = panes.top.get("offsetHeight"),
	            data,
	            numFound;
        
	        panes.annotate.empty();
	    
	        /** Get results from cache if available */
	        if (Lang.isValue(e.cached)) {
	            data = e.response.results;
	            numFound = data.length;
	        }
	        else {
		        data = e.response.results;
		        numFound = e.data.response.numFound;
            }
	        
      if (numFound > 0) {
          Y.Object.each(data, function(value) {
        	  Y.log('value');
        	  Y.log(value);
              Y.Object.each(value.target, function(element, i) {
  	              var bounds = OpenLayers.Bounds.fromArray(getCoordinates(element.url), false);
  	              var box = new OpenLayers.Feature.Vector(bounds.toGeometry(), { coords: bounds.toString() });

  	              // Y.DLTS.boxes[box.id] = { box: box, id: 'annon' + element.vid };
                  
  	              element.username = 'Alberto Ortiz Flores';
  	              
  	              element.vid = box.id;
  	              
  	              Y.DLTS.boxes[box.id] = { box: box, id: 'annon' + box.id };  	              
  	              
  	              Y.one('.pane.annotations').append(templates.body(element));
  	              
  	              Y.DLTS.layers.boxes.addFeatures(box);
  	                    
              });              
		      panes.annotate.append(templates.annotation(value));
          });
      }
	    
    },
    failure: function(e) {
  	  Y.log('failure');
	  Y.log(e); 
    }
  }
    
  var dataSource = new Y.DataSource.Get({source: Y.DLTS.settings.annotations.environment + '/api/annotations.json'});
	  
  dataSource.plug(Y.Plugin.DataSourceJSONSchema, {
    schema: {
      resultListLocator: 'response.annotations',
	  resultFields: ['type', 'target', 'creator', 'text', 'id', 'modification_date_utc']
	}
  });
	        
    dataSource.plug(Y.Plugin.DataSourceCache, {cache: Y.CacheOffline, max:5});
    
    dataSource.cache.flush();
  
    Y.on('button:button-annotations:on', function(e) {
        this.removeClass("hidden");
        dataSource.sendRequest({
            request: '?targetUri=' + Y.DLTS.settings.annotations.url + '&',
  	        callback: searchCallback
        });
    }, panes.annotate);

    Y.on('button:button-annotations:off', function(e) {
        this.addClass('hidden');
    }, panes.annotate);
  
    buttons.annotate.on('click', onClick);
  
    OpenLayers.Feature.Vector.style.default.fillColor = 'transparent';
    
    OpenLayers.Feature.Vector.style.default.strokeColor = 'white';
    
    OpenLayers.Feature.Vector.style.select.fillColor = 'transparent';
    
    OpenLayers.Feature.Vector.style.select.strokeColor = '#FFC';
	
    Y.DLTS.layers = { boxes: new OpenLayers.Layer.Vector('Boxes') };
  
    var imageURL = 'http://dlib.nyu.edu/alba-moscow/sites/dlib.nyu.edu.alba-moscow/files/177_195013d.jp2';
    
	Y.DLTS.constrols = {};
	
    var cControl = new OpenLayers.Control();

    OpenLayers.Util.extend(cControl, {
        draw : function() {
            /** This Handler.Box will intercept the shift-mousedown before Control.MouseDefault gets to see it */
            this.box = new OpenLayers.Handler.Box(cControl, { done: this.notice }, { keyMask : OpenLayers.Handler.MOD_SHIFT });
		    this.box.activate();
        },
        notice : function(bounds) {
            var ll = this.map.getLonLatFromPixel(new OpenLayers.Pixel(bounds.left, bounds.bottom)),
                ur = this.map.getLonLatFromPixel(new OpenLayers.Pixel(bounds.right, bounds.top)),
                coords = ll.lon.toFixed(4) + ',' + ll.lat.toFixed(4) + ',' + ur.lon.toFixed(4) + ',' + ur.lat.toFixed(4),
                bounds = OpenLayers.Bounds.fromString(coords, false),
                box = new OpenLayers.Feature.Vector(bounds.toGeometry(), { coords: bounds.toString() });
        
            Y.DLTS.layers.boxes.addFeatures(box);
            Y.DLTS.boxes[box.id] = box;
        
            Y.one('#annotations-textarea').append(templates.input({
                username: 'Alberto Ortiz Flores',
                vid: box.id
            }));        
        }
    });
    
    var onSelect = Y.DLTS.constrols.select = new OpenLayers.Control.SelectFeature(Y.DLTS.layers.boxes, {
        onSelect: function(feature) {
            Y.all('div[data-vector="'+feature.id+'"]').addClass('highlighted');
        },
        onUnselect: function(feature) {
            Y.all('div[data-vector="'+feature.id+'"]').removeClass('highlighted');
        },
        toggleKey: 'ctrlKey',
        box: false,
        hover: true
    });

    OpenLayers.DLTS.pages[0].addControl(onSelect);
    OpenLayers.DLTS.pages[0].addControl(cControl);
    onSelect.activate();
  

});