/*
 ============================================================================
 Name        : encryption.c
 Author      : Polytech
 Version     :
 Copyright   : Your copyright notice
 Description :
 ============================================================================
 */

#include "encryption.h"

uint8_t encrypt_message(const uint8_t *key, uint8_t key_size, uint8_t *msg, uint8_t msg_size)
{
	uint8_t ret = 0;
	uint8_t i = 0 ;
	uint8_t block = 0;

	for(i=0;i<msg_size;i++)
	{
		msg[i] = msg[i]^key[block];
		block++;
		if(block > 7)
		{
			block = 0;
		}

	}


	return ret;
}

uint8_t decrypt_message(const uint8_t *key, uint8_t key_size, uint8_t *msg, uint8_t msg_size)
{
	return encrypt_message(key, key_size, msg, msg_size);
}
