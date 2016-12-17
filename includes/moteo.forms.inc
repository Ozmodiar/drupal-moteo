<?php
/**
 * @file This file contains all the form functionality.
 */

/**
 * Moteo registration form.
 *
 * @param array $form
 * @param array $form_state
 * @param string $code
 *
 * @return array
 */
function moteo_registration_form($form, &$form_state, $code) {

  $service = new MoteoService();
  if ($registration = $service->getRegistration($code)) {

    // Store registration object for later use.
    $form_state['storage']['registration'] = $registration;

    $form['infobox'] = array(
      '#type' => 'container',
    );
    $form['infobox']['framenumber'] = array(
      '#type' => 'item',
      '#title' => t('Framenumber'),
      '#markup' => $registration->FrameNumber,
    );
    $form['infobox']['warranty_start_date'] = array(
      '#type' => 'item',
      '#title' => t('Warranty start date'),
      '#markup' => $registration->WarrantyStartDate,
    );
    $form['infobox']['registration_entry_date'] = array(
      '#type' => 'item',
      '#title' => t('Registration entry date'),
      '#markup' => $registration->RegistrationEntryDate,
    );
    $form['infobox']['model_code'] = array(
      '#type' => 'item',
      '#title' => t('Model code'),
      '#markup' => $registration->ModelCode,
    );

    $form['email_address'] = array(
      '#type' => 'textfield',
      '#title' => t('E-mail'),
      '#default_value' => $registration->EmailAddress,
      '#size' => 60,
      '#maxlength' => 256,
      '#required' => TRUE,
    );

    $form['is_private_owner'] = array(
      '#type' => 'radios',
      '#title' => NULL,
      '#default_value' => $registration->IsPrivateOwner,
      '#options' => array(1 => t('Private'), 0 => t('Organisation')),
    );

    $form['organisation_name'] = array(
      '#type' => 'textfield',
      '#title' => t('Organisation name'),
      '#default_value' => $registration->OrganisationName,
      '#size' => 60,
      '#maxlength' => 256,
      '#required' => FALSE,
      '#states' => array(
        'visible' => array(
          ':input[name="is_private_owner"]' => array('value' => 0),
        ),
      ),
    );

    $form['first_name'] = array(
      '#type' => 'textfield',
      '#title' => t('First name'),
      '#default_value' => $registration->FirstName,
      '#size' => 60,
      '#maxlength' => 128,
      '#required' => TRUE,
    );

    $form['last_name'] = array(
      '#type' => 'textfield',
      '#title' => t('Last name'),
      '#default_value' => $registration->LastName,
      '#size' => 60,
      '#maxlength' => 128,
      '#required' => TRUE,
    );

    $form['birth_date'] = array(
      '#type' => 'date_popup',
      '#title' => t('Date of birth'),
      '#date_label_position' => 'invisible',
      '#date_format' => 'd/m/Y',
      '#date_year_range' => '-99:+0',
      '#default_value' => $registration->BirthDate,
    );

    $country_list = country_get_list();
    $form['country_code'] = array(
      '#type' => 'select',
      '#title' => t('Country'),
      '#options' => $country_list,
      '#default_value' => $registration->CountryCode,
    );

    $form['postal_code'] = array(
      '#type' => 'textfield',
      '#title' => t('Postal code'),
      '#default_value' => $registration->PostalCode,
      '#size' => 16,
      '#maxlength' => 16,
    );

    $form['postal_code_letters'] = array(
      '#type' => 'textfield',
      '#title' => t('Postal code letters'),
      '#default_value' => $registration->PostalCodeLetters,
      '#size' => 16,
      '#maxlength' => 16,
      '#states' => array(
        'visible' => array(
          ':input[name="country_code"]' => array('value' => 'NL'),
        ),
      ),
    );

    $form['city'] = array(
      '#type' => 'textfield',
      '#title' => t('City'),
      '#default_value' => $registration->City,
      '#size' => 60,
      '#maxlength' => 128,
    );

    $form['street'] = array(
      '#type' => 'textfield',
      '#title' => t('Street'),
      '#default_value' => $registration->Street,
      '#size' => 60,
      '#maxlength' => 128,
    );

    $form['house_number'] = array(
      '#type' => 'textfield',
      '#title' => t('Number'),
      '#default_value' => $registration->HouseNumber,
      '#size' => 16,
      '#maxlength' => 16,
    );

    $form['license_plate'] = array(
      '#type' => 'textfield',
      '#title' => t('License plate'),
      '#default_value' => $registration->LicensePlate,
      '#size' => 60,
      '#maxlength' => 128,
      '#required' => TRUE,
    );

    $form['allow_email_contact'] = array(
      '#type' => 'checkbox',
      '#title' => t('Tomos is allowed to contact me for commercial reasons.'),
      '#default_value' => $registration->AllowEmailContact,
    );

    $form['ANWB_requested'] = array(
      '#type' => 'checkbox',
      '#title' => t('Yes, I would like to request a free "ANWB Pechpas".'),
      '#default_value' => $registration->ANWBRequested,
      '#states' => array(
        'visible' => array(
          ':input[name="country_code"]' => array('value' => 'NL'),
        ),
      ),
      '#disabled' => $registration->RegistrationSavedByCustomer ? TRUE : FALSE,
    );

    $form['ANWB_member'] = array(
      '#type' => 'checkbox',
      '#title' => t('I\'m already a member of the ANWB.'),
      '#default_value' => $registration->ANWBMember,
      '#states' => array(
        'visible' => array(
          ':input[name="country_code"]' => array('value' => 'NL'),
        ),
      ),
      '#disabled' => $registration->RegistrationSavedByCustomer ? TRUE : FALSE,
    );

    $form['scooter_x_press'] = array(
      '#type' => 'checkbox',
      '#title' => t('I would like to request a free trail of the ScooterXPress magazine.'),
      '#default_value' => $registration->ScooterXPress,
      '#states' => array(
        'visible' => array(
          ':input[name="country_code"]' => array('value' => 'NL'),
        ),
      ),
      '#disabled' => $registration->RegistrationSavedByCustomer ? TRUE : FALSE,
    );

    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
    );

  }
  else {
    drupal_set_message(t('Something went wrong while getting the registration. Please try again later.'), 'error');
  }

  return $form;
}

/**
 * Moteo registration form validation.
 *
 * @param array $form
 * @param array $form_state
 */
function moteo_registration_form_validate($form, &$form_state) {
  if (!valid_email_address($form_state['values']['email_address'])) {
    form_set_error('email', t('The provided e-mailaddress is not valid.'));
  }
}

/**
 * Moteo registration form submit.
 *
 * @param array $form
 * @param array $form_state
 */
function moteo_registration_form_submit($form, &$form_state) {
  $registration = $form_state['storage']['registration'];

  // Remove all non-field information from the form_state['values'] so it can be looped safely.
  $dummy_form_state = $form_state;
  form_state_values_clean($dummy_form_state);

  $one_time_properties = array(
    'ANWB_requested',
    'ANWB_member',
    'scooter_x_press',
  );

  foreach ($dummy_form_state['values'] as $key => $value) {
    // Extra check for users that were able to bypass the disabled fields and managed to change the form values anyway.
    if ($registration->RegistrationSavedByCustomer == FALSE ||
      ($registration->RegistrationSavedByCustomer == TRUE && !in_array($key, $one_time_properties))
    ) {
      $property = camelize($key);

      // Development only, remove later
      if (!property_exists($registration, $property)) {
        die('Incorrect mapping: ' . $property);
      }

      $registration->{$property} = $value;
    }
  }

  // Mark registration as saved by the customer.
  $registration->RegistrationSavedByCustomer = TRUE;

  $service = new MoteoService();
  if ($service->saveRegistration($registration)) {
    drupal_set_message(t('Thank you, your registration was saved successfully.'), 'status');
  }
  else {
    drupal_set_message(t('An error occured while saving your registration, please try again later.'), 'error');
    watchdog('meteo', t('Something went wrong while saving registration with code: !code', array('!code' => $registration->Code)));
  }
}

/**
 * Helper function to translate the underscored values to the camelcased notation.
 *
 * This will ease the mapping pain between the form fields and the webservice properties.
 *
 * @param string $input
 * @param string $separator
 *
 * @return string
 */
function camelize($input, $separator = '_') {
  return str_replace($separator, '', ucwords($input, $separator));
}
