<?php

/**
 * Expose primary links as context reactions.
 */
class context_reaction_primary_links extends context_reaction {

  /**
   * Allow admins to set a primary links menu source for the context.
   */
  function options_form($context) {
    $options = array();
    $menus = menu_get_menus();
    foreach($menus as $mid => $name) {
     	$options[$mid] = $name;
    }

    $form = array(
      '#tree' => TRUE,
      '#title' => t('Menu'),
      'primary_links' => array(
        '#title' => t('Active primary links menu'),
        '#description' => t('Choose a menu to use for primary links when this context is active.'),
        '#type' => 'select',
        '#options' => $options,
        '#default_value' => 0//$this->fetch_from_context($context),
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
      $custom = $v->reactions[$this->plugin]['primary_links'];
      if (!empty($custom)) {
          global $conf;
	  $conf['menu_primary_links_source'] = $custom;
      } 
    }
  }
}
