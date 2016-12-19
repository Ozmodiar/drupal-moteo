<?php
/**
 * @file This file contains the MoteoService class.
 */

/**
 * Defines the MoteoService class.
 */
class MoteoService {

  /**
   * @var string
   */
  private $login;

  /**
   * @var string
   */
  private $password;

  /**
   * @var string
   */
  private $url;

  /**
   * MoteoService constructor.
   */
  public function __construct() {
    $this->login = variable_get('moteo_service_login');
    $this->password = variable_get('moteo_service_password');
    $this->url = variable_get('moteo_service_url');
  }

  /**
   * Get a registration by code and return it. If an error occurs, return FALSE.
   *
   * @param string $code
   *
   * @return mixed
   */
  public function getRegistration($code) {
    if ($this->checkConfiguration()) {
      $client = new SoapClient($this->url);
      $result = $client->REG_GetRegistration(array(
        'login' => $this->login,
        'password' => $this->password,
        'registrationCode' => $code,
      ));

      if ($result->REG_GetRegistrationResult->succesfull) {
        return $result->REG_GetRegistrationResult->data->WS_VehicleRegistration;
      }
      else {
        watchdog('moteo', t($result->REG_GetRegistrationResult->message . ' (%code)', array('%code' => $code)));
      }
    }

    return FALSE;
  }

  /**
   * Save a registration object. Return TRUE on success, FALSE on failure.
   *
   * @param stdClass $registration
   *
   * @return bool
   */
  public function saveRegistration($registration) {
    if ($this->checkConfiguration()) {
      $client = new SoapClient($this->url);
      $result = $client->REG_SaveRegistration(array(
        'login' => $this->login,
        'password' => $this->password,
        'registration' => $registration,
      ));

      if ($result->REG_SaveRegistrationResult->succesfull) {
        return TRUE;
      }
      else {
        watchdog('moteo', t($result->REG_SaveRegistrationResult->message));
      }
    }

    return FALSE;
  }

  /**
   * Check if the configuration settings are set.
   *
   * @return bool
   */
  private function checkConfiguration() {
    if (is_null($this->login) || is_null($this->password) || is_null($this->url)) {
      watchdog('moteo', t('The Moteo webservice is being used, but the parameters are not configured.'));
      drupal_set_message(t('The Moteo webservice is being used, but the parameters are not configured. Please go to the Moteo configuration page to configure them.'), 'error');

      return FALSE;
    }

    return TRUE;
  }
}
