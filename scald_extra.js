(function($, Drupal) {
    var element_id = 'scald-extra--atom-add-page--modal';

    function processImages() {
      $( ".atom_reference_processed" ).each(function() {
        var $this = $(this);
        var match_id = /<!-- scald=(\d+):.*-->/g.exec($this.html());
        var id = match_id ? match_id[1] : false;

        if (!Drupal.dnd.Atoms[id]) return;

        Drupal.dnd.currentAtom = Drupal.dnd.Atoms[id].sas;
        delete Drupal.dnd.Atoms[id].contexts;

        $this.trigger('drop');
      });
    }

    function show_element(href) {
      // add a query parameter to the modal url, so the system can be aware he
      // is inside a modal
      href += ( href.indexOf('?') >= 0 ? '&' : '?' ) + 'modal=true';

      var div = $('<div>', {
        id: element_id,
        click: function () {
          Drupal.scald_extra.remove_iframe();
        }
      });

      var iframe = $('<iframe>', { src: href });

      div.append(iframe);
      $('body').append(div);
    }

    function remove_element() {
      $('#' + element_id).remove();
    }

    Drupal.scald_extra = {
        remove_iframe: function () {
            window.parent.postMessage({message: 'Close Modal', type: 'close'}, location);

            remove_element();
        },
        update_reference: function () {
          window.parent.postMessage({message: 'Update Reference', type: 'update_reference'}, location);
        },
        atom_add_wizard_finish: function () {
            // Refresh atoms view
            if (window.parent && window.parent.Drupal && window.parent.Drupal.dnd) {
                window.parent.Drupal.dnd.refreshLibraries();
                Drupal.scald_extra.update_reference();
            }

            // Remove iframe
            Drupal.scald_extra.remove_iframe();
        }
    };

    $(document).ready(function () {
        var link_selectors = '.dnd-library-wrapper .add-buttons a, .dnd-library-wrapper .edit a, .dnd-library-wrapper .delete a, .dnd-library-wrapper .translate a, .atom_reference_operations .edit a';

        // Remove every events added to links, so we can handle it
        $(document).on('DOMNodeInserted', '.dnd-library-wrapper, .atom_reference_operations', function() {
            window.setTimeout( function () {
                $(link_selectors).off();
            }, 0);
        });

        // Add modal on anchor click with source of anchor href
        $(document).on('click', link_selectors, function(event) {
            event.preventDefault();

          show_element($(this).attr('href'));
        });

        // Remove iframe if user clicks on cancel button
        $('#edit-cancel').click(function() {
            Drupal.scald_extra.remove_iframe();
        });

      if (window.addEventListener){
        window.addEventListener('message', function(event) {
          if (!event.data) {
            return;
          }

          if (event.data.type == 'close') {
            remove_element();
          }

          if (event.data.type == 'show') {
            show_element(event.data.href);
          }

          if (event.data.type == 'update_reference') {
            processImages();
          }
        }, false);

      } else if (window.attachEvent){
          // To work on IE
        window.attachEvent('message', function(event) {
          if (!event.data) {
            return;
          }

          if (event.data.type == 'close') {
            remove_element();
          }

          if (event.data.type == 'show') {
            show_element(event.data.href);
          }

          if (event.data.type == 'update_reference') {
            processImages();
          }
        }, false);
      }

    });
}(jQuery, Drupal));
