<?php

/**
 * Expose primary and secondary links as context reactions.
 */

class context_reaction_primary_links extends context_reaction {

  /**
   * Allow admins to set a primary and secondary links menu source for the context.
   */
  function options_form($context) {
    $values = $this->fetch_from_context($context); // get any values already set for this context

    // build a list of available menus to include as options in our form
    $options = array();
    $menus = menu_get_menus(); 
    foreach($menus as $mid => $name) {
     	$options[$mid] = $name;
    }

    $form = array(
      '#tree' => TRUE,
      '#title' => t('Primary and Secondary Links'),
      'primary_links' => array(
        '#title' => t('Active primary links menu'),
        '#description' => t('Choose a menu to use for primary links when this context is active.'),
        '#type' => 'select',
        '#options' => $options,
        '#default_value' => isset($values['primary_links']) ? $values['primary_links'] : 'primary-links',
      ),
      'secondary_links' => array(
        '#title' => t('Active secondary links menu'),
        '#description' => t('Choose a menu to use for secondary links when this context is active.'),
        '#type' => 'select',
        '#options' => $options,
        '#default_value' =>  isset($values['secondary_links']) ? $values['secondary_links'] : 'secondary-links',
      ),
    );
    return $form;
  }

  /**
   * Set the primary links menu;
   */
  function execute(&$vars) {
    $contexts = context_active_contexts();
    $classes = array();

    foreach ($contexts as $k => $v) {
      $plinks = $v->reactions[$this->plugin]['primary_links'];
      $slinks = $v->reactions[$this->plugin]['secondary_links'];
      if (!empty($plinks)) {
          global $conf;
	  $conf['menu_primary_links_source'] = $plinks;
      } 

      if (!empty($slinks)) {
          global $conf;
	  $conf['menu_secondary_links_source'] = $slinks;
      } 


    }
  }
}
