<?php

/**
 * Overrides default @see scald_atom_delete_confirm_ajax
 */
function scald_extra_atom_delete_confirm_ajax($js, $atom) {
  $form = drupal_get_form('scald_atom_delete_confirm', $atom);
  $output = drupal_render($form);

  print theme('html', array(
    'page' => array(
      'page_top' => array(),
      'page_bottom' => array(),
      '#children' => $output
    )
  ));
}

/**
 * Overrides default @see scald_atom_delete_confirm_submit
 */
function scald_extra_atom_delete_confirm_submit($form, &$form_state) {
  $form_state['redirect'] = FALSE;

  if ($form_state['values']['confirm']) {
    $atom = scald_atom_load($form_state['values']['sid']);
    scald_atom_delete($atom->sid);
    watchdog('scald_atom', '@type: deleted %title.', array('@type' => $atom->type, '%title' => $atom->title));
    $types = scald_types();
    $type = scald_type_property_translate($types[$atom->type]);
    drupal_set_message(t('@type %title has been deleted.', array('@type' => $type, '%title' => $atom->title)));
  }

  drupal_add_js("Drupal.scald_extra.atom_add_wizard_finish();", array("type" => "inline"));
}

/**
 * Overrides default @see scald_atom_edit_page
 */
function scald_extra_atom_edit_page($js, $atom) {
  // The edit page is nothing else other than the add page, at the Options step.
  // We prepare data for this step then send back to the add page. The only
  // useful information at this step is the atom itself.
  $scald = array(
    'atoms' => array($atom),
  );
  $types = scald_types();
  ctools_include('object-cache');
  ctools_object_cache_set('scald_atom', 'edit:' . $atom->sid, $scald);

  scald_extra_atom_add_page($js, $types[$atom->type], 'options', $atom->sid);
}

/**
 * Overrides default @see scald_atom_add_page, to print only the form
 */
function scald_extra_atom_add_page($js, $type, $step = NULL, $atom_id = NULL) {
  ctools_include('object-cache');
  ctools_include('wizard');

  // If we are not currently edit an atom and there is a temporary saved atom,
  // reopen it.
  $cache = ctools_object_cache_get('scald_atom', 'edit:-1');
  if (!$atom_id && $cache && $cache['atoms'][0]->type === $type->type) {
    $atom_id = -1;
    $step = 'options';
  }

  $cache_id = isset($atom_id) ? 'edit:' . $atom_id : 'add';

  // Start by getting the list of all the modules that said they can provide
  // this atom type.
  $providers = scald_atom_providers_opt();
  $sources = $providers[$type->type];
  $source = key($sources);
  $provider = current($sources);

  // If there's more than one, provide a choice between them. Otherwise, skip
  // a step and select the only provider upfront.
  if (empty($step)) {
    if (count($sources) < 2) {
      if (!empty($provider['starting_step'])) {
        $step = $provider['starting_step'];
      }
      else {
        $step = 'add';
      }
    }
    else {
      $step = 'source';
    }
    ctools_object_cache_clear('scald_atom', $cache_id);
  }

  $form_state = array(
    'ajax' => $js,
    'scald' => ctools_object_cache_get('scald_atom', $cache_id),
  );

  // Entity Translation workaround when the fix https://drupal.org/node/2027513
  // is not corporated in a stable release.
  if (isset($form_state['scald']['atoms'][0])) {
    $form_state['atom'] = $form_state['scald']['atoms'][0];
  }

  if (empty($form_state['scald'])) {
    $form_state['scald'] = array(
      'type' => $type,
      'source' => isset($source) ? $source : NULL,
      'provider' => $provider,
    );
  }

  $form_state['scald']['step'] = $step;

  $form_info = array(
    'id' => 'scald-atom-add',
    'path' => 'atom/add/' . $type->type . '/' . ($js ? 'ajax' : 'nojs') . '/%step',
    'show trail' => TRUE,
    'show back' => FALSE,
    'show cancel' => TRUE,
    'show return' => FALSE,
    'next callback' => 'scald_extra_atom_add_wizard_next',
    'finish callback' => 'scald_extra_atom_add_wizard_finish',
    'cancel callback' => 'scald_extra_atom_add_wizard_cancel',
    'order' => array(
      'source' => t('Source'),
      'add' => t('Add'),
      'options' => t('Options'),
    ),
    'forms' => array(
      'source' => array(
        'form id' => 'scald_extra_atom_add_form_source',
      ),
      'add' => array(
        'form id' => 'scald_extra_atom_add_form_add',
      ),
      'options' => array(
        'form id' => 'scald_extra_atom_add_form_options',
      ),
    ),
  );

  // Send this all off to our form. This is like drupal_get_form only wizardy.
  $form = ctools_wizard_multistep_form($form_info, $step, $form_state);
  $output = drupal_render($form);

  print theme('html', array(
    'page' => array(
      'page_top' => array(),
      'page_bottom' => array(),
      '#children' => $output
    )
  ));
}

/**
 * Handle the 'next' click on the add/edit pane form wizard.
 */
function scald_extra_atom_add_wizard_next(&$form_state) {
  scald_atom_add_wizard_next($form_state);
}

/**
 * Handle the 'finish' click on the add/edit pane form wizard.
 */
function scald_extra_atom_add_wizard_finish(&$form_state) {
  drupal_add_js("Drupal.scald_extra.atom_add_wizard_finish();", array("type" => "inline"));
  scald_atom_add_wizard_finish($form_state);
}

/**
 * Handle the 'cancel' click on the add/edit pane form wizard.
 */
function scald_extra_atom_add_wizard_cancel(&$form_state) {
  scald_atom_add_wizard_cancel($form_state);
}

/**
 * Source form.
 */
function scald_extra_atom_add_form_source($form, &$form_state) {
  return scald_atom_add_form_source($form, $form_state);
}

/**
 * Handles the source step form submission.
 */
function scald_extra_atom_add_form_source_submit(&$form, &$form_state) {
  scald_atom_add_form_source_submit($form, $form_state);
}

/**
 * Add form.
 */
function scald_extra_atom_add_form_add($form, &$form_state) {
  return scald_atom_add_form_add($form, $form_state);
}

/**
 * Handles the add step form submission.
 */
function scald_extra_atom_add_form_add_submit(&$form, &$form_state) {
  scald_atom_add_form_add_submit($form, $form_state);
}


/**
 * Options form.
 */
function scald_extra_atom_add_form_options($form, &$form_state) {
  return scald_atom_add_form_options($form, $form_state);
}

/**
 * Handles the final atom creation step form submission.
 */
function scald_extra_atom_add_form_options_submit(&$form, &$form_state) {
  scald_atom_add_form_options_submit($form, $form_state);
}

/**
 * Handles the atom translation page.
 */
function scald_extra_atom_translate($atom) {
  module_load_include('inc', 'entity_translation', 'entity_translation.admin');

  $output = entity_translation_overview('scald_atom', $atom);

  print theme('html', array(
    'page' => array(
      'page_top' => array(),
      'page_bottom' => array(),
      '#children' => drupal_render($output)
    )
  ));
}
