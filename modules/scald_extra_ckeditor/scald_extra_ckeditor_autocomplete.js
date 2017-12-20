(function ($) {
  var initAutocomplete = function(input, uri) {
    input.setAttribute('autocomplete', 'OFF');
    var jsAC = new Drupal.jsAC($(input), new Drupal.ACDB(uri));

    // Override Drupal.jsAC.prototype.onkeydown().
    // @see https://drupal.org/node/1991076
    var _onkeydown = jsAC.onkeydown;
    jsAC.onkeydown = function(input, e) {
      if (!e) {
        e = window.event;
      }
      switch (e.keyCode) {
        case 13: // Enter.
          this.hidePopup(e.keyCode);
          return true;
        default: // All other keys.
          return _onkeydown.call(this, input, e);
      }
    };
  };

  var extractPath = function(value) {
    value = CKEDITOR.tools.trim(value);
    var match;
    match = /\(([^\(]*?)\)$/i.exec(value);
    if (match && match[1]) {
      value = match[1];
    }
    var basePath = Drupal.settings.basePath;
    if (value.indexOf(basePath) == 0) {
      value = value.substr(basePath.length);
    }
    if (/^[a-z][\w\/\.-]*$/i.test(value)) {
      return value;
    }
    return false;
  };

  var cache = {}, revertPath = function(value,callback) {
    // debugger;
    var path = extractPath(value);
    if (!path) {
      return false;
    }
    if (cache[path] !== undefined) {
      return cache[path];
    }
    $.getJSON(Drupal.settings.scald_extra_ckeditor.revert_path + '/' + Drupal.encodePath(path), function(data) {
      cache[path] = data;
      callback(data);
    });
  };

  Drupal.behaviors.scaldImageLink = {
    attach: function (context, settings) {
      if (typeof Drupal.dndck4 !== 'undefined') {
        Drupal.dndck4.addOption('txtLink', 'image', 'atom', 'scald_image', function (infoTab, dialogDefinition) {
          infoTab.add({
            id: 'txtLink',
            type: 'text',
            label: Drupal.t('Link'),
            // "Link" edits the 'link' property in the options JSON string.
            setup: function (widget) {
              var options = JSON.parse(widget.data.options);
              if (options.link) {
                // console.log(revertPath(options.link));
                // this.setValue(revertPath(options.link));
                var self = this;
                revertPath(options.link, function (data) {
                  self.setValue(data);
                });
              }
            },
            onLoad: function() {
              this.getInputElement().addClass('form-autocomplete');
              initAutocomplete(this.getInputElement().$, Drupal.settings.scald_extra_ckeditor.autocomplete_path);
            },
            commit: function (widget) {
              // Copy the current options into a new object,
              var options = JSON.parse(widget.data.options);
              var value = this.getValue();
              debugger;
              if (value != '') {
                options.link = extractPath(value);
              }
              else {
                delete options.link;
              }

              widget.setData('options', JSON.stringify(options));
            }
          });
        });
      }
    }
  };
})(jQuery);
