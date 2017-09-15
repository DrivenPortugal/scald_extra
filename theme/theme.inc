<?php

/**
 * Implements hook_preprocess_HOOK().
 */
function scald_extra_preprocess_scald_extra_atom(&$vars) {
  // Atom Entity
  $atom = $vars['atom'];

  // Make sure align is defined
  $vars['align'] = empty($vars['align']) ? '' : $vars['align'];

  // Fallback to type preprocess
  switch ($atom->type) {
    case 'file':
      scald_extra_preprocess_scald_extra_atom__file($vars);
      break;
    case 'image':
      scald_extra_preprocess_scald_extra_atom__image($vars);
      break;
    case 'video':
      scald_extra_preprocess_scald_extra_atom__video($vars);
      break;
  }
}

/**
 * Implements hook_preprocess_HOOK().
 */
function scald_extra_preprocess_scald_extra_atom__file(&$vars) {
  // Atom Entity
  $atom = $vars['atom'];

  // Get file source
  $vars['src'] = file_create_url($atom->file_source);

  // Get file extension for class
  $info = pathinfo($vars['src']);
  $vars['extension'] = empty($info['extension']) ? '' : $info['extension'];

  scald_extra_add_suggestion($vars);
}

/**
 * Implements hook_preprocess_HOOK().
 */
function scald_extra_preprocess_scald_extra_atom__image(&$vars) {
  // Atom Entity
  $atom = $vars['atom'];

  // Make sure options is defined
  $vars['options'] = empty($vars['options']) ? '' : $vars['options'];

  // Options have to be json decoded
  $vars['decoded_options'] = drupal_json_decode($vars['options']);

  // Get file source
  $vars['src'] = file_create_url($atom->file_source);

  // Get link entered by user in atom properties to wrap image
  if (!empty($vars['decoded_options']['link'])) {
    $url = urldecode($vars['decoded_options']['link']);
    $vars['url'] = url($url);
  }

  if (!empty($vars['atom']->file_source)) {
    $vars['image_info'] = image_get_info($vars['atom']->file_source);
  }

  scald_extra_add_suggestion($vars);
}

/**
 * Implements hook_preprocess_HOOK().
 */
function scald_extra_preprocess_scald_extra_atom__video(&$vars) {
  // Atom Entity
  $atom = $vars['atom'];

  $vars['data'] = $atom->data;

  if ($atom->provider == 'scald_youtube') {
    // Add youtube parameters
    $query = array();
    if (!empty($atom->data['list'])) {
      $query['list'] = $atom->data['list'];
    }
    if (isset($atom->data['show_related']) && empty($atom->data['show_related'])) {
      $query['rel'] = '0';
    }
    // Create youtube url for iframe
    $vars['youtube'] = url(SH_SCALD_YOUTUBE_EMBED . $atom->base_id, array(
      'query' => $query,
    ));
  } else {
    $vars['video'] = file_create_url($atom->file_source);
  }

  scald_extra_add_suggestion($vars);
}

/**
 * Add suggestion based on atom type
 *
 * @param $vars
 */
function scald_extra_add_suggestion(&$vars) {
  // If context or atom nor available bail out
  if(empty($vars['context']) || empty($vars['atom'])) {
    return;
  }

  // The atom object
  $atom = $vars['atom'];
  // The atom context
  $context = scald_context_config_load($vars['context']);

  // Create hook suggestions
  $vars['theme_hook_suggestions'][] = 'scald_extra_atom';
  $vars['theme_hook_suggestions'][] = 'scald_extra_atom__' . $atom->type;

  if (!empty($context->context)) {
    $vars['theme_hook_suggestions'][] = 'scald_extra_atom__' . $atom->type . '__' . $context->context;

    if (!empty($context->player[$atom->type]['*'])) {
      $vars['theme_hook_suggestions'][] = 'scald_extra_atom__' . $atom->type . '__' . $context->context . '__' . $context->player[$atom->type]['*'];
    }
  }
}
