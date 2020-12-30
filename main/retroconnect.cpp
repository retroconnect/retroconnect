//#include <fstream>
//#include <algorithm>

#include <string>
#include <map>
#include <unistd.h>
#include <fcntl.h>
#include "esp_hid_host_main.h"
#include "ConverterFactory.h"
#include "driver/uart.h"
#include "driver/gpio.h"

#include "NesController.h"
#include "SnesController.h"
#include "XboxController.h"
#include "Ps4Controller.h"
#include "GenController.h"
#include "SmsController.h"
#include "Atari2600Controller.h"
#include "Atari7800Controller.h"

extern "C" {
    void app_main(void);
}

using namespace std;

//#include "esp_hid_host_main.c"

typedef controller_t* ControllerMaker();
controller_t* controller;
controller_t* input_controller;
controller_t* output_controller;
Converter* converter;

template <class controller> controller_t* make() {
	return new controller;
}

ControllerMaker* get_controller[] = {
	make<xbox_controller_t>, //default, todo: change it to "XB1"
	make<xbox_controller_t>,
	make<ps4_controller_t>,
	make<snes_controller_t>, 
	make<nes_controller_t>,
	make<gen_controller_t>,
	make<sms_controller_t>,
	make<atari_2600_controller_t>,
	make<atari_7800_controller_t>
};

/***************************************************/

void init_uart() {
  // Configure parameters of an UART driver,
  // communication pins and install the driver
  uart_config_t uart_config = {
    .baud_rate = 921600,
    .data_bits = UART_DATA_8_BITS,
    .parity = UART_PARITY_DISABLE,
    .stop_bits = UART_STOP_BITS_1,
    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
  };
  // Configure UART parameters
  ESP_ERROR_CHECK(uart_param_config(UART_NUM_1, &uart_config));
  ESP_ERROR_CHECK(uart_set_pin(UART_NUM_1, 22, 21, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));
  ESP_ERROR_CHECK(uart_driver_install(UART_NUM_1, 2048, 0, 0, NULL, 0));
}

void parse_inputs(button_struct_t* button_struct) {

	//Inputs are passed in from esp_hid_host_main callback
	
	//DELETE// Below only applies to PS4?
	/*if (button_struct->type != 1 && button_struct->type != 3) {
		return;
	}*/

	//Parse button presses
	input_controller->read_buttons(button_struct);

	//Check if a button combo is pressed
	if (int new_input_controller = input_controller->combo_pressed()) {	
		printf("Combo detected! Switching to %s output\n", CONTROLLERNAME[new_input_controller].c_str());
		output_controller = (controller_t*) get_controller[new_input_controller]();
		converter = ConverterFactory::create_converter(*input_controller, *output_controller);

		//input_controller->gpio_setup();
		//input_controller->SerialHandler(); 
	}

	//Convert button inputs to outputs
	converter->convert(*input_controller, *output_controller);

	//DEBUG - Print output controller state
	////output_controller->print_state();
}

void home_button_handler (unsigned int value) {
	((controller_t*)input_controller)->button_states["HOME"] = value;
}


void app_main(void)
{
	//Initialize UART
	init_uart();

	//Initialize controller models (SNES to XB1 by default)
	input_controller  = new xbox_controller_t(); 
	output_controller = new snes_controller_t();
	//input_controller->gpio_setup();
	//input_controller->SerialHandler();

	//Initialize converter
	converter = ConverterFactory::create_converter(*input_controller, *output_controller);

	//Start esp_hid_host function and wait for input
	esp_hid_host_start();

	while (1) {
		sleep(5);
		input_controller->print_state();
	}

	return;
}
