# README

## Scald Extra
This module provides default configuration to scald module, 
see https://www.drupal.org/project/scald.

### Description Field
This module provides a description field to every atom types.

### Hook hook_scald_extra_modes
- Extends scald contexts, ex: 

```
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
```

### Default Templates
This module provides default templates to atoms of type image, file and video.

The default theme can be overrided in your main theme with the following structure:
	
	scald-extra-atom--TYPE--CONTEXT.tpl.php

	- TYPE should be replaced by your atom type ex: file, image, etc;
	- CONTEXT the key of your contexts array provided in hook_scald_extra_modes;

Filename example: 
	scald-extra-atom--image--shc-full.tpl.php