<?php

/**
 * Allows modules to add scald contexts and players.
 */
function hook_scald_extra_modes() {
  // The format depend on the providers you added to your project
  // ex: if you enable scald_image, format image is now available
  return array(
    'shc_full' => array(
      'title' => t('Full'),
      'formats'    => array(),
      'classes' => ''
    ),
    'shc_teaser' => array(
      'title' => t('Teaser'),
      'formats'    => array(),
      'classes' => ''
    ),
  );
}
