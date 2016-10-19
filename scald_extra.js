(function($, Drupal) {
    var element_id = 'scald-extra--atom-add-page--modal';

    Drupal.scald_extra = {
        remove_iframe: function () {
            var parent_element = window.parent.document.getElementById(element_id);
            var element = document.getElementById(element_id);

            // Remove element if in iframe context
            if (parent_element) {
                parent_element.remove();
            }

            // Remove element if in parent context
            if (element) {
                element.remove();
            }
        },
        atom_add_wizard_finish: function () {
            // Refresh atoms view
            if (window.parent && window.parent.Drupal && window.parent.Drupal.dnd) {
                window.parent.Drupal.dnd.refreshLibraries();
            }

            // Remove iframe
            Drupal.scald_extra.remove_iframe();
        }
    };

    $(document).ready(function () {
        var link_selectors = '.dnd-library-wrapper .add-buttons a, .dnd-library-wrapper .edit a, .dnd-library-wrapper .delete a';

        // Remove every events added to links, so we can handle it
        $(document).on('DOMNodeInserted', '.dnd-library-wrapper', function() {
           window.setTimeout( function () {
               $(link_selectors).off();
           }, 0);
        });

        // Add modal on anchor click with source of anchor href
        $(document).on('click', link_selectors, function(event) {
            event.preventDefault();

            var div = $('<div>', {
                id: element_id,
                click: function () {
                    Drupal.scald_extra.remove_iframe();
                }
            });

            var iframe = $('<iframe>', { src: $(this).attr('href') });

            div.append(iframe);
            $('body').append(div);
        });


        // Remove iframe if user clicks on cancel button
        $('#edit-cancel').click(function() {
            Drupal.scald_extra.remove_iframe();
        });
    });
}(jQuery, Drupal));
