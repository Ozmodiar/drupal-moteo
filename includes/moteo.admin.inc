<?php
/**
 * @file This file contains all the admin functionality.
 */

/**
 * Moteo admin configuration form.
 *
 * @param array $form
 * @param array $form_state
 *
 * @return array
 */
function moteo_service_admin_form($form, &$form_state) {
  $form['moteo_service_login'] = array(
    '#type' => 'textfield',
    '#title' => t('Login'),
    '#default_value' => variable_get('moteo_service_login'),
    '#size' => 60,
    '#maxlength' => 256,
    '#required' => TRUE,
  );

  $form['moteo_service_password'] = array(
    '#type' => 'password',
    '#title' => t('Password'),
    '#default_value' => variable_get('moteo_service_password'),
    '#size' => 60,
    '#maxlength' => 256,
    '#required' => TRUE,
  );

  $form['moteo_service_url'] = array(
    '#type' => 'textfield',
    '#title' => t('URL'),
    '#default_value' => variable_get('moteo_service_url'),
    '#size' => 60,
    '#maxlength' => 256,
    '#required' => TRUE,
  );

  return system_settings_form($form);
}
