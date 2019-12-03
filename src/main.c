/*
 ============================================================================
 Name        : main.c
 Author      : Polytech
 Version     :
 Copyright   : Your copyright notice
 Description :
 ============================================================================
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "application.h"

/**
 * @brief Point d'entrée principal de l'application.
 */
int main(void)
{
	app_error_t err;
	uint8_t end = 0;
	int ret = 0;

	// Run the application loop
	while(end == 0 && err == APP_NO_ERROR)
	{
		// Run the update loop of the application
		err = app_update(&end);
		if(err != APP_NO_ERROR)
		{
			printf("Error returned by app_update(): %d\n", err);
			goto end;
		}
	}

end:
	return ret;
}
