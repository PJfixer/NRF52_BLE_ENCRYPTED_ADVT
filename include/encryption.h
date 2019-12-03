/*
 ============================================================================
 Name        : encryption.h
 Author      : Polytech
 Version     :
 Copyright   : Your copyright notice
 Description :
 ============================================================================
 */

#ifndef INCLUDE_ENCRYPTION_H_
#define INCLUDE_ENCRYPTION_H_

#include <stdint.h>

/**
 * @brief Fonction d'encryptage.
 * @param key        La clef d'encryptage
 * @param key_size   La taille de la clef
 * @param msg        Le message à encrypter (clear text). En sortie, le message crypté.
 * @param msg_size   La taille du message à encrypter.
 * @return taille du message encrypté
 */
uint8_t encrypt_message(const uint8_t *key, uint8_t key_size, uint8_t *msg, uint8_t msg_size);

/**
 * @brief Fonction de décryptage.
 * @param key        La clef d'encryptage
 * @param key_size   La taille de la clef
 * @param msg        Le message à décrypter (cipher text). En sortie, le message décrypté.
 * @param msg_size   La taille du message à décrypter.
 * @return taille du message décrypté
 */
uint8_t decrypt_message(const uint8_t *key, uint8_t key_size, uint8_t *msg, uint8_t msg_size);

#endif /* INCLUDE_ENCRYPTION_H_ */
