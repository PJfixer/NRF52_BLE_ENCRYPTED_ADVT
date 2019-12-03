/*
 ============================================================================
 Name        : application.h
 Author      : Polytech
 Version     :
 Copyright   : Your copyright notice
 Description :
 ============================================================================
 */

#ifndef INCLUDE_APPLICATION_H_
#define INCLUDE_APPLICATION_H_

#include "bsp.h"
#include "ble.h"

#define APP_BUTTON1_PRESSED		((uint8_t) 1)
#define APP_BUTTON2_PRESSED		((uint8_t) 2)
#define APP_BUTTON3_PRESSED		((uint8_t) 4)
#define APP_BUTTON4_PRESSED		((uint8_t) 8)

/**
 * @brief Code d'erreurs de l'application
 */
typedef enum
{
	APP_NO_ERROR = 0,
	APP_ERROR_INIT_TIMER,
	APP_ERROR_INIT_BUTTONS,
	APP_ERROR_UNINIT_TIMER,
	APP_ERROR_UNINIT_BUTTONS,
	APP_ERROR_ENABLE_SOFTDEVICE_CONFIG,
	APP_ERROR_ENABLE_SOFTDEVICE,
	APP_ERROR_INITIALISE_LOG,
	APP_ERROR_SOFTDEVICE_BLE_GAP,
	APP_ERROR_SOFTDEVICE_BLE_ADVERTISING,
	APP_ERROR_SOFTDEVICE_BLE_SCAN,
	APP_ERROR_EVENT,
} app_error_t;

/**
 * @brief Etats de l'application
 */
typedef enum
{
	APP_INITIALISE = 0,
	APP_RUNNING,
	APP_SCANNING,
	APP_DESTROY,
	APP_ENDED,
} app_state_t;

/**
 * @brief Fonction d'initialisation du matériel utilisé par l'application.
 * @return APP_NO_ERROR si aucune erreur, sinon une erreur
 */
app_error_t app_initialise_hardware(void);

/**
 * @brief Fonction de déinitialisation du matériel utilisé par l'application.
 * @return APP_NO_ERROR si aucune erreur, sinon une erreur
 */
app_error_t app_uninitialise_hardware(void);

/**
 * @brief Fonction de mise à jour de l'application.
 * @return APP_NO_ERROR si aucune erreur, sinon une erreur
 */
app_error_t app_update(uint8_t *end);

/**
 * @brief Fonction de scanning BLE.
 * @return APP_NO_ERROR si aucune erreur, sinon une erreur
 */
app_error_t app_scan_start(void);

/**
 * @brief Fonction d'arret du scanning BLE.
 * @return APP_NO_ERROR si aucune erreur, sinon une erreur
 */
app_error_t app_scan_stop(void);

/**
 * @brief Fonction de rappel sur évènement de la plateforme.
 * @param event        Evènement sysème à traiter
 * @return APP_NO_ERROR si aucune erreur, sinon une erreur
 */
void app_event_handler(bsp_event_t event);

/**
 * @brief Fonction de gestion des assert softdevice
 * @param line_num     Numéro de ligne où l'assert a été envoyée
 * @param p_file_name  Fichier source où l'assert a été envoyée
 */
void assert_nrf_callback(uint16_t line_num, const uint8_t * p_file_name);

/**
 * @brief Fonction de rappel sur évènement du BLE.
 * @param event        Evènement BLE à traiter
 * @return APP_NO_ERROR si aucune erreur, sinon une erreur
 */
void app_ble_event_handler(ble_evt_t const * event, void * p_context);

/**
 * @brief Fonction d'affichage d'info système.
 * @return APP_NO_ERROR si aucune erreur, sinon une erreur
 */
void app_display_info(void);

/**
 * @brief Fonction de remplissage avec des données de l'advertisement.
 * @param adv_src        Payload advertisement modèle
 * @param adv_src_length Taille su payload adv_srv
 * @param msg            Message à inclure pour compléter le payload
 * @param msg_length     Taille du message pouvant être inclu
 * @return -1 si aucune données ne peut être incluses, sinon le nombre d'octets inclus dans le message
 */
int8_t app_create_ble_adv(const uint8_t *adv_src, uint8_t adv_src_length, const uint8_t *msg, uint8_t msg_length);

#endif /* INCLUDE_APPLICATION_H_ */
