/*
 ============================================================================
 Name        : application.c
 Author      : Polytech
 Version     :
 Copyright   : Your copyright notice
 Description :
 ============================================================================
 */

#include "application.h"
#include "encryption.h"

#include "app_timer.h"
#include "app_button.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "ble_advdata.h"
#include "ble_gap.h"
#include "ble_lbs.h"
#include "boards.h"
#include "nrf_sdm.h"
#include "nrf_sdh.h"
#include "nrf_sdh_ble.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#include <string.h>

void test_ciphering(void);

static app_state_t app_state = APP_INITIALISE;
static uint8_t app_buttons = 0;

/**< Number of central links used by the application. When changing this number remember to adjust the RAM settings*/
#define CENTRAL_LINK_COUNT              0
/**< Number of peripheral links used by the application. When changing this number remember to adjust the RAM settings*/
#define PERIPHERAL_LINK_COUNT           1

/**< Value of the RTC1 PRESCALER register. */
#define APP_TIMER_PRESCALER             0
/**< Size of timer operation queues. */
#define APP_TIMER_OP_QUEUE_SIZE         4

/**< Determines scan interval in units of 0.625 millisecond. */
#define SCAN_INTERVAL             0x00A0
/**< Determines scan window in units of 0.625 millisecond. */
#define SCAN_WINDOW               0x0050
/**< Timeout when scanning. 0x0000 disables timeout. */
#define SCAN_TIMEOUT              0x0000
/**< Active scanning is not set. */
#define SCAN_REQUEST              0
/**< We will not ignore unknown devices. */
#define SCAN_WHITELIST_ONLY       0

/**< The SoftDevice BLE configuration id. */
#define APP_BLE_CONN_CFG_TAG      1
/**< Application's BLE observer priority. You shouldn't need to modify this value. */
#define APP_BLE_OBSERVER_PRIO     3

//personal define PJEANNE

//AD type
#define BLE_TYP_COMP_LOCAL_NAME 0x09
#define BLE_TYP_16BIT_UUID 0x03
#define BLE_TYP_FLAGS 0x01
#define BLE_TYP_APPAREANCE  0x19

//




/**< The Bluetooth scan parameters */
static const ble_gap_scan_params_t app_scan_param =
{
    SCAN_REQUEST,
    SCAN_WHITELIST_ONLY,
    NULL,
    (uint16_t)SCAN_INTERVAL,
    (uint16_t)SCAN_WINDOW,
    (uint16_t)SCAN_TIMEOUT
};

const uint8_t ble_adv_data[] = {0x0A, BLE_TYP_COMP_LOCAL_NAME, 'P','J','E','A','-','D','E','S','N',     /* Complete local name */  // pjeann desnos
								0x02, BLE_TYP_FLAGS, BLE_GAP_ADV_FLAG_BR_EDR_NOT_SUPPORTED,   /* Flags */
								0x03, BLE_TYP_APPAREANCE, 0xc7, 0x03,                         /* GAP Appearance :
																								  0x03C6 pens:
																								! */
								0x03, BLE_TYP_16BIT_UUID, 0x1c, 0x18};                        /* Complete list of 16 bits UUID GATT TYPE USER DATA */
								// complete size = 22 bytes user data can't exceed 31-22  = 9 bytes ?

static ble_gap_adv_params_t ble_adv_params = {0};

static uint8_t MESSAGE[] = "CE MESSAGE NE DOIT PAS ETRE VISIBLE";
static uint8_t KEY[] = {0x0A, 0x1B, 0xFE, 0xDE, 0xFD, 0xAB, 0xB1, 0x04};

static uint8_t ble_adv[31];
static uint8_t ble_adv_length;
static uint8_t ble_mess_count;



/**
 * @test ciphering
 *
 *
 */

void test_ciphering(void)
{
	printf("cipher test \n");
	 uint8_t i;
	 uint8_t MESSAGE_TEST[] = "CECI EST UN TEST DE CHIFFREMENT";
	 uint8_t KEY_TEST[] = {0x0A, 0x1B, 0xFE, 0xDE, 0xFD, 0xAB, 0xB1, 0x04};

	 printf("taille du message  : %d \n",sizeof(MESSAGE_TEST));
	 printf("taille de la clef  : %d \n",sizeof(KEY_TEST));


	 printf("message initial : ");
	 for(i=0;i<sizeof(MESSAGE_TEST);i++)
	 {
		 printf("%c",MESSAGE_TEST[i]);
	 }
	 printf("\n");

	 encrypt_message(&KEY_TEST,sizeof(KEY_TEST),&MESSAGE_TEST,sizeof(MESSAGE_TEST));

	 printf("message chiffrer : ");
	 for(i=0;i<sizeof(MESSAGE_TEST);i++)
		 {
			 printf("%c",MESSAGE_TEST[i]);
		 }
		 printf("\n");

	 decrypt_message(&KEY_TEST,sizeof(KEY_TEST),&MESSAGE_TEST,sizeof(MESSAGE_TEST));

	 printf("message dechiffrer : ");
	 for(i=0;i<sizeof(MESSAGE_TEST);i++)
		 {
			 printf("%c",MESSAGE_TEST[i]);
		 }
		 printf("\n");

}




app_error_t app_initialise_hardware(void)
{
	app_error_t ret = APP_NO_ERROR;
	ret_code_t errcode;


	// Initialise the log system used by the drivers to report errors and warnings
    errcode = NRF_LOG_INIT(NULL);
    if(errcode != NRF_SUCCESS)
    {
    	printf("Error returned by NRF_LOG_INIT: %lu\n", errcode);
    	ret = APP_ERROR_INITIALISE_LOG;
    	goto end;
    } else
    {
    	// And the backend log system to use (in our case it is RTT)
    	NRF_LOG_DEFAULT_BACKENDS_INIT();
    }

    // Initialise the timer
    errcode = app_timer_init(); // enable for BP reading

    // Install the system callback to get notified on button changes and reset the LEDs

    bsp_init(BSP_INIT_BUTTONS|BSP_INIT_LED,app_event_handler);  // register app_event_handler callback for BP event


    // Configure LED-pins as outputs and turn them off
   	  // LEDS_CONFIGURE(LEDS_MASK); // configure leds tris
   	   bsp_board_leds_off(); // shut down all the onboard leds


    // Initialise SoftDevice
   	nrf_sdh_enable_request();
    // Initialise BLE stack

    uint32_t ram_start = 0;
    errcode = nrf_sdh_ble_default_cfg_set(APP_BLE_CONN_CFG_TAG, &ram_start);
    if(errcode != NRF_SUCCESS)
    {
    	printf("Error returned by nrf_sdh_ble_default_cfg_set(): %lu\n", errcode);
    	ret = APP_ERROR_ENABLE_SOFTDEVICE_CONFIG;
    	goto end;
    }

    errcode = nrf_sdh_ble_enable(&ram_start);
    if(errcode != NRF_SUCCESS)
    {
    	printf("Error returned by nrf_sdh_ble_enable(): %lu\n", errcode);
    	ret = APP_ERROR_ENABLE_SOFTDEVICE;
    	goto end;
    }

    // Register the BLE handler function

    NRF_SDH_BLE_OBSERVER(ble_observer, APP_BLE_OBSERVER_PRIO, app_ble_event_handler, NULL);

    // Initialise the Generic Access Profile

	app_create_ble_adv(&ble_adv_data[0], sizeof(ble_adv_data), NULL, 0);

    // Set the advertisement data to send

    errcode = sd_ble_gap_adv_data_set(ble_adv, ble_adv_length, NULL, 0);
    if(errcode != NRF_SUCCESS)
    {
    	printf("Error returned by sd_ble_gap_adv_data_set(): %lu\n", errcode);
    	ret = APP_ERROR_SOFTDEVICE_BLE_ADVERTISING;
    	goto end;
    }

    // Start the advertisement

    ble_adv_params.type = BLE_GAP_ADV_TYPE_ADV_IND;
    ble_adv_params.p_peer_addr = NULL;
    ble_adv_params.fp = BLE_GAP_ADV_FP_ANY;
    ble_adv_params.interval = 64;
    ble_adv_params.timeout = 10;
    errcode = sd_ble_gap_adv_start(&ble_adv_params, APP_BLE_CONN_CFG_TAG);
    if(errcode != NRF_SUCCESS)
    {
    	printf("Error returned by sd_ble_gap_adv_start(): %lu\n", errcode);
    	ret = APP_ERROR_SOFTDEVICE_BLE_ADVERTISING;
    	goto end;
    }

end:
	return ret;
}

app_error_t app_uninitialise_hardware(void)
{
	app_error_t ret = APP_NO_ERROR;
	ret_code_t errcode;

	// Stop advertisement
	sd_ble_gap_adv_stop();

    // Uninstall the BLE handler.
	NRF_SDH_BLE_OBSERVER(ble_observer, APP_BLE_OBSERVER_PRIO, NULL, NULL);

	// Disable the buttons
	bsp_buttons_disable();


	// Uninitialise the timer
	app_timer_stop_all();


    // Turn all LEDS off
	bsp_board_leds_off();

	// Turn off the system
	/* ... A COMPLETER */

    // Disable BLE stack
	//nrf_sdh_ble_disable();

    // Disable softdevice
	nrf_sdh_disable_request();
end:
	return ret;
}

app_error_t app_update(uint8_t *end)
{
	app_error_t ret = APP_NO_ERROR;
	uint32_t err;

	switch(app_state)
	{
		case APP_INITIALISE:


			ret = app_initialise_hardware();
			if(ret != APP_NO_ERROR)
			{
				printf("Error returned by app_initialise_hardware(): %d\n", ret);
			}
			printf("Hardware initialised\n");

			// Display some information
			app_display_info();

			// Start the message to send from the start
			ble_mess_count = 0;

			// Go to the next state
			test_ciphering();
			app_state = APP_RUNNING;
			break;

		case APP_DESTROY:
			// Uninitialise the hardware required by the application
			ret = app_uninitialise_hardware();
			if(ret != APP_NO_ERROR)
			{
				printf("Error returned by app_uninitialise_hardware(): %d\n", ret);
			}
			printf("Hardware uninitialised\n");

			// Go to the next state (the end)
			app_state = APP_ENDED;
			if(end != NULL) *end = 1;
			break;

		case APP_RUNNING:
			if(app_buttons & APP_BUTTON1_PRESSED)
				{
					app_buttons &= ~APP_BUTTON1_PRESSED; //Reset BP state 1
					app_state=APP_SCANNING;
					app_scan_stop();
					app_scan_start();// scan for ble devices
					printf("state : Scanning....\n");

					LEDS_ON(BSP_LED_0_MASK); // turn on onboard led0
				}

				if(app_buttons & APP_BUTTON2_PRESSED)
				{
					app_buttons &= ~APP_BUTTON2_PRESSED; ////Reset BP state 2
					app_state=APP_DESTROY; // destroy app !!
					printf(" state : Destroy\n");
				}

				// wait the softdevice
				sd_app_evt_wait();
			break;

		case APP_SCANNING:
				if(app_buttons & APP_BUTTON1_PRESSED)
				{
					app_buttons &= ~APP_BUTTON1_PRESSED; //Reset l'appui du bouton
					app_state=APP_RUNNING; // Goto app scanning mode at next cycle
					app_scan_stop();
					printf("stop scan");
					printf("State :  Running\n");

					LEDS_OFF(BSP_LED_0_MASK); // turn off onboard led0
				}

				// wait the softdevice
				sd_app_evt_wait();
		break;

		default:
			break;
	};

	return ret;
}

app_error_t app_scan_start(void)
{
	app_error_t ret = APP_NO_ERROR;
	uint32_t err;

	ble_gap_scan_params_t params; //create a ble_gap_scan_params_t sruct

	params.interval=SCAN_INTERVAL; // config scan interval
	params.timeout=SCAN_TIMEOUT; // config timeout
	params.window=SCAN_WINDOW; //  config window

	sd_ble_gap_scan_start(&params); // run scan with parameters


	return ret;
}

app_error_t app_scan_stop(void)
{
	app_error_t ret = APP_NO_ERROR;
	uint32_t err;

	// Stop the scan
	sd_ble_gap_scan_stop();

	return ret;
}

void app_event_handler(bsp_event_t event)
{
	switch(event)
	{
		case BSP_EVENT_KEY_0:

			printf("BP0\n");
			app_buttons |= APP_BUTTON1_PRESSED;
			break;

		case BSP_EVENT_KEY_1:

			printf("BP1\n");
			app_buttons |= APP_BUTTON2_PRESSED;
			break;

		case BSP_EVENT_KEY_2:

			printf("BP2\n");
			app_buttons |= APP_BUTTON3_PRESSED;
			break;

		case BSP_EVENT_KEY_3:

			printf("BP3\n");
			app_buttons |= APP_BUTTON4_PRESSED;
			break;

		default:
			printf("Unknow event !! \n");
			break;
	};
}

void assert_nrf_callback(uint16_t line_num, const uint8_t * p_file_name)
{
    app_error_handler(0xffffffff, line_num, p_file_name);
}

void app_ble_event_handler(ble_evt_t const * event, void * p_context)
{
	int8_t mess_length;
	ret_code_t errcode;
	size_t i;
	uint8_t j;

	if(event != NULL)
	{
		switch(event->header.evt_id)
		{
			case BLE_GAP_EVT_TIMEOUT:
				{
			    	printf("Evenement BLE_GAP_EVT_TIMEOUT\n");

			    	// Create the advertisement payload
			    	if(ble_mess_count >= sizeof(MESSAGE))
			    	{
			    		// Reset the counter
			    		ble_mess_count = 0;
			    	}

			    	/* ... A REACTIVER POUR LA PARTIE BLE ... */
			    	mess_length = app_create_ble_adv(&ble_adv_data[0], sizeof(ble_adv_data),
			    		&MESSAGE[ble_mess_count], sizeof(MESSAGE) - ble_mess_count);
			    	if(mess_length > 0)
			    	{
			    		ble_mess_count += mess_length;
			    	}

				    // Set the advertisement data to send
			    	/* ... A REACTIVER POUR LA PARTIE BLE ... */
				    errcode = sd_ble_gap_adv_data_set(ble_adv, ble_adv_length, NULL, 0);
				    if(errcode != NRF_SUCCESS)
				    {
				    	printf("Error returned by sd_ble_gap_adv_data_set(): %lu\n", errcode);
				    }

					// Restart the advertisement
			    	/* ... A REACTIVER POUR LA PARTIE BLE ... */
			        errcode = sd_ble_gap_adv_start(&ble_adv_params, APP_BLE_CONN_CFG_TAG);
			        if(errcode != NRF_SUCCESS)
			        {
			        	printf("Error returned by sd_ble_gap_adv_start(): %lu\n", errcode);
				    }
				}
				break;

			case BLE_GAP_EVT_ADV_REPORT:
				{
					uint8_t* data = event->evt.gap_evt.params.adv_report.data;
					size_t data_len = event->evt.gap_evt.params.adv_report.dlen;
					printf("Received advertisement of length %lu\n", (uint32_t) data_len);

					/* Print the different ADs */
					for(i = ((size_t) 0); i < data_len; i += ((size_t)(data[i] + 1)))
					{
						printf("  AD: len=%d type=%x ", data[i], data[i + 1]);
						switch(data[i + 1])
						{
							case 0x9:
								printf("local_name=%.*s ", data[i] - 1, &data[i + 2]);
								break;
							case 0xff:
								printf("manufacturer_data= ");
								for(j = 0; j < data[i] - 1; j++)
								{
									printf("%.2x ", data[i + 2 + j]);
								}
								break;
							default:
								break;
						};
						printf("\n");
					}
				}
				break;

			default:
				printf("Unmanaged event in app_ble_event_handler: %d\n", event->header.evt_id);
				break;
		};
	} else
	{
		printf("No event passed to app_ble_event_handler()\n");
	}
}

void app_display_info(void)
{
	ble_gap_addr_t addr;
	uint32_t err;
	uint8_t i;

	/* Retrieve the BLE address */
	/* ... A REACTIVER POUR LA PARTIE BLE ... */
	err = sd_ble_gap_addr_get(&addr);
	if(err != NRF_SUCCESS)
	{
    	printf("Error returned by sd_ble_gap_address_get(): %lu\n", err);
	} else
	{
		printf("Local BLE test address is ");
		for(i = sizeof(addr.addr) / sizeof(addr.addr[0]); i > 0; i--)
		{
			printf((i > 1) ? "%.2x:" : "%.2x", addr.addr[i - 1]);
		}
		printf("\n");
	}
}

int8_t app_create_ble_adv(const uint8_t *adv_src, uint8_t adv_src_length, const uint8_t *msg, uint8_t msg_length)
{
	int8_t ret = -1;
	int8_t size;

	// First, copy the advertisement source payload
	if(adv_src_length < sizeof(ble_adv))
	{
		memcpy(&ble_adv[0], adv_src, adv_src_length);
	}

	// Copy the AD payload (Manufacturer)
	size = MIN(sizeof(ble_adv) - adv_src_length - 2, msg_length);
	if(size > 0)
	{
		// Integrate the rest of the payload
		ble_adv[adv_src_length] = size + 1;
		ble_adv[adv_src_length + 1] = 0xff;
		memcpy(&ble_adv[adv_src_length + 2], msg, size);
		ret = size;

		// Encrypt the data
		encrypt_message(KEY, sizeof(KEY), &ble_adv[adv_src_length + 2], size);
	}

	// Set the size ready to be sent
	ble_adv_length = adv_src_length;
	if(ret > 0)
	{
		ble_adv_length += size + 2;
	}

	return ret;
}
