using namespace std;
#include <iostream>
#include <stdlib.h>
#include <wiringPi.h>
#include <sys/time.h>
#include <fstream>
#include <iostream>
#include <string>
#include <poll.h>
#include <unistd.h>
#include <fcntl.h>
#include <typeinfo>
#include <algorithm>

#include "Constants.h"
#include "Controller.h"
#include "SnesController.h"
#include "XboxController.h"
#include "Ps4Controller.h"
#include "ControllerConverter.h"
#include "XboxToSnesControllerConverter.h"
#include "Ps4ToSnesControllerConverter.h"
#include "ControllerConverterFactory.h"
#include "SNESBackend.h"

struct button_struct_t {       //16 bytes total
	struct timeval time;   //8 bytes
	unsigned short type;   //2 bytes
	unsigned short code;   //2 bytes
	unsigned int value;    //4 bytes
} button_struct;


/***************************************************/

void read_ps4_controller(button_struct_t button_struct, ps4_controller_t *input_controller) {
	switch(button_struct.code) {
		case(PS4_LEFT_Y_AXIS):
			printf("Left Analog Stick Y\n");
			input_controller->LS_Y = button_struct.value;
			break;
		case(PS4_LEFT_X_AXIS):
			printf("Left Analog Stick X\n");
			input_controller->LS_X = button_struct.value;
			break;
		case(PS4_RIGHT_Y_AXIS):
			printf("Right Analog Stick Y\n");
			input_controller->RS_Y = button_struct.value;
			break;
		case(PS4_RIGHT_X_AXIS):
			printf("Right Analog Stick X\n");
			input_controller->RS_X = button_struct.value;
			break;
		case(PS4_DPAD_X):
			if (button_struct.value == 1) {
				printf("DPAD-Right\n");
				input_controller->D_RIGHT = true;
			}
			else if (button_struct.value == 0) {
				printf("DPAD-X Released\n");
				input_controller->D_RIGHT = false;
				input_controller->D_LEFT = false;
			}
			else {
				printf("DPAD-Left\n");
				input_controller->D_LEFT = true;
			}
			break;
		case(PS4_DPAD_Y):
			if (button_struct.value == 1) {
				printf("DPAD-Down\n");
				input_controller->D_DOWN = true;
			}
			else if (button_struct.value == 0) {
				printf("DPAD-Y Released\n");
				input_controller->D_DOWN = false;
				input_controller->D_UP = false;
			}
			else {
				printf("DPAD-Up\n");
				input_controller->D_UP = true;
			}
			break;
		case(PS4_BTN_CROSS):
			if (button_struct.value == 0) {
				printf("X released\n");
				input_controller->X = false;
			}
			else {
				printf("X pressed\n");
				input_controller->X = true;
			}
			break;
		case(PS4_BTN_CIRCLE):
			if (button_struct.value == 0) {
				printf("Circle released\n");
				input_controller->CIRCLE = false;
			}
			else {
				printf("Circle pressed\n");
				input_controller->CIRCLE = true;
			}
			break;
		case(PS4_BTN_SQUARE):
			if (button_struct.value == 0) {
				printf("Square released\n");
				input_controller->SQUARE = false;
			}
			else {
				printf("Square pressed\n");
				input_controller->SQUARE = true;
			}
			break;
		case(PS4_BTN_TRIANGLE):
			if (button_struct.value == 0) {
				printf("Triangle released\n");
				input_controller->TRIANGLE = false;
			}
			else {
				printf("Triangle pressed\n");
				input_controller->TRIANGLE = true;
			}
			break;
		case(PS4_BTN_L1):
			if (button_struct.value == 0) {
				printf("L1 released\n");
				input_controller->L1 = false;
			}
			else {
				printf("L1 pressed\n");
				input_controller->L1 = true;
			}
			break;
		case(PS4_BTN_R1):
			if (button_struct.value == 0) {
				printf("R1 released\n");
				input_controller->R1 = false;
			}
			else {
				printf("R1 pressed\n");
				input_controller->R1 = true;
			}
			break;
		case(PS4_BTN_START):
			if (button_struct.value == 0) {
				printf("Start released\n");
				input_controller->START = false;
			}
			else {
				printf("Start pressed\n");
				input_controller->START = true;
			}
			break;
		case(PS4_BTN_SELECT):
			if (button_struct.value == 0) {
				printf("Select released\n");
				input_controller->SELECT = false;
			}
			else {
				printf("Select pressed\n");
				input_controller->SELECT = true;
			}
			break;
		case(PS4_BTN_LS):
			if (button_struct.value == 0) {
				printf("Left Thumb released\n");
				input_controller->LS_PRESS = false;
			}
			else {
				printf("Left Thumb pressed\n");
				input_controller->LS_PRESS = true;
			}
			break;
		case(PS4_BTN_RS):
			if (button_struct.value == 0) {
				printf("Right Thumb released\n");
				input_controller->RS_PRESS = false;
			}
			else {
				printf("Right Thumb pressed\n");
				input_controller->RS_PRESS = true;
			}
			break;
		case(PS4_BTN_HOME):
			if (button_struct.value == 0) {
				printf("Home released\n");
				input_controller->HOME = false;
			}
			else {
				printf("Home pressed\n");
				input_controller->HOME = true;
			}
			break;
		case(PS4_RIGHT_TRIGGER):
			if (button_struct.value == 0) {
				printf("Right Trigger released\n");
			}
			else {
				printf("Right Trigger pressed\n");
			}
			input_controller->R2 = button_struct.value;
			break;
		case(PS4_LEFT_TRIGGER):
			if (button_struct.value == 0) {
				printf("Left Trigger released\n");
			}
			else {
				printf("Left Trigger pressed\n");
			}
			input_controller->L2 = button_struct.value;
			break;

		default:
			printf("!!! Unknown button code: %d !!!\n", button_struct.code);
	}
}

void read_xbox_buttons(button_struct_t button_struct, xbox_controller_t *input_controller) {

	switch(button_struct.code) {
		case(XB1_LEFT_Y_AXIS):
			printf("Left Analog Stick Y\n");
			input_controller->LS_Y = button_struct.value;
			break;
		case(XB1_LEFT_X_AXIS):
			printf("Left Analog Stick X\n");
			input_controller->LS_X = button_struct.value;
			break;
		case(XB1_RIGHT_Y_AXIS):
			printf("Right Analog Stick Y\n");
			input_controller->RS_Y = button_struct.value;
			break;
		case(XB1_RIGHT_X_AXIS):
			printf("Right Analog Stick X\n");
			input_controller->RS_X = button_struct.value;
			break;
		case(XB1_DPAD_X):
			if (button_struct.value == 1) {
				printf("DPAD-Right\n");
				input_controller->D_RIGHT = true;
			}
			else if (button_struct.value == 0) {
				printf("DPAD-X Released\n");
				input_controller->D_RIGHT = false;
				input_controller->D_LEFT = false;
			}
			else {
				printf("DPAD-Left\n");
				input_controller->D_LEFT = true;
			}
			break;
		case(XB1_DPAD_Y):
			if (button_struct.value == 1) {
				printf("DPAD-Down\n");
				input_controller->D_DOWN = true;
			}
			else if (button_struct.value == 0) {
				printf("DPAD-Y Released\n");
				input_controller->D_DOWN = false;
				input_controller->D_UP = false;
			}
			else {
				printf("DPAD-Up\n");
				input_controller->D_UP = true;
			}
			break;
		case(XB1_BTN_A):
			if (button_struct.value == 0) {
				printf("A released\n");
				input_controller->A = false;
			}
			else {
				printf("A pressed\n");
				input_controller->A = true;
			}
			break;
		case(XB1_BTN_B):
			if (button_struct.value == 0) {
				printf("B released\n");
				input_controller->B = false;
			}
			else {
				printf("B pressed\n");
				input_controller->B = true;
			}
			break;
		case(XB1_BTN_X):
			if (button_struct.value == 0) {
				printf("X released\n");
				input_controller->X = false;
			}
			else {
				printf("X pressed\n");
				input_controller->X = true;
			}
			break;
		case(XB1_BTN_Y):
			if (button_struct.value == 0) {
				printf("Y released\n");
				input_controller->Y = false;
			}
			else {
				printf("Y pressed\n");
				input_controller->Y = true;
			}
			break;
		case(XB1_BTN_LB):
			if (button_struct.value == 0) {
				printf("LB released\n");
				input_controller->LB = false;
			}
			else {
				printf("LB pressed\n");
				input_controller->LB = true;
			}
			break;
		case(XB1_BTN_RB):
			if (button_struct.value == 0) {
				printf("RB released\n");
				input_controller->RB = false;
			}
			else {
				printf("RB pressed\n");
				input_controller->RB = true;
			}
			break;
		case(XB1_BTN_START):
			if (button_struct.value == 0) {
				printf("Start released\n");
				input_controller->START = false;
			}
			else {
				printf("Start pressed\n");
				input_controller->START = true;
			}
			break;
		case(XB1_BTN_SELECT):
			if (button_struct.value == 0) {
				printf("Select released\n");
				input_controller->SELECT = false;
			}
			else {
				printf("Select pressed\n");
				input_controller->SELECT = true;
			}
			break;
		case(XB1_BTN_LS):
			if (button_struct.value == 0) {
				printf("Left Thumb released\n");
				input_controller->LS_PRESS = false;
			}
			else {
				printf("Left Thumb pressed\n");
				input_controller->LS_PRESS = true;
			}
			break;
		case(XB1_BTN_RS):
			if (button_struct.value == 0) {
				printf("Right Thumb released\n");
				input_controller->RS_PRESS = false;
			}
			else {
				printf("Right Thumb pressed\n");
				input_controller->RS_PRESS = true;
			}
			break;
		case(XB1_BTN_HOME):
			if (button_struct.value == 0) {
				printf("Home released\n");
				input_controller->HOME = false;
			}
			else {
				printf("Home pressed\n");
				input_controller->HOME = true;
			}
			break;
		case(XB1_RIGHT_TRIGGER):
			if (button_struct.value == 0) {
				printf("Right Trigger released\n");
			}
			else {
				printf("Right Trigger pressed\n");
			}
			input_controller->RT = button_struct.value;
			break;
		case(XB1_LEFT_TRIGGER):
			if (button_struct.value == 0) {
				printf("Left Trigger released\n");
			}
			else {
				printf("Left Trigger pressed\n");
			}
			input_controller->LT = button_struct.value;
			break;

		default:
			printf("!!! Unknown button code: %d !!!\n", button_struct.code);
	}

	// Print full struct for button press debugging
	//printf("\nButton Timestamp: %08X", button_struct.time);
	//printf("\nButton Type: %02X", button_struct.type);
	//printf("\nButton Code: %02X", button_struct.code);
	//printf("\nButton Value: %04X\n", button_struct.value);
}

void print_xbox_controller_state(xbox_controller_t* x) {
	printf("\n---Xbox Controller State---\n");

	printf("A: %d, B: %d, X: %d, Y: %d\n", x->A, x->B, x->X, x->Y);
	printf("D-up: %d, D-down: %d, D-left: %d, D-right: %d\n", x->D_UP, x->D_DOWN, x->D_LEFT, x->D_RIGHT);
	printf("LT: %d, RT: %d\n", x->LT, x->RT);
	printf("LB: %d, RB: %d\n", x->LB, x->RB);
	printf("Select: %d, Home: %d, Start: %d\n", x->SELECT, x->HOME, x->START);
	printf("LS-x: %d, LS-y: %d, LS-press: %d\n", x->LS_X, x->LS_Y, x->LS_PRESS);
	printf("RS-x: %d, RS-y: %d, RS-press: %d\n", x->RS_X, x->RS_Y, x->RS_PRESS);
}

void print_snes_controller_state(snes_controller_t* s) {
	printf("\n---SNES Controller State---\n");

	printf("A: %d, B: %d, X: %d, Y: %d\n", s->A, s->B, s->X, s->Y);
	printf("D-up: %d, D-down: %d, D-left: %d, D-right: %d\n", s->D_UP, s->D_DOWN, s->D_LEFT, s->D_RIGHT);
	printf("LB: %d, RB: %d\n", s->LB, s->RB);
	printf("Select: %d, Start: %d\n\n", s->SELECT, s->START);
}

void print_ps4_controlller_state(ps4_controller_t* x) {
	printf("\n---PS4 Controller State---\n");

	printf("X: %d, Circle: %d, Triangle: %d, Square: %d\n", x->X, x->CIRCLE, x->TRIANGLE, x->SQUARE);
	printf("D-up: %d, D-down: %d, D-left: %d, D-right: %d\n", x->D_UP, x->D_DOWN, x->D_LEFT, x->D_RIGHT);
	printf("L2: %d, R2: %d\n", x->L2, x->R2);
	printf("L1: %d, R1: %d\n", x->L1, x->R1);
	printf("Select: %d, Home: %d, Start: %d\n", x->SELECT, x->HOME, x->START);
	printf("LS-x: %d, LS-y: %d, LS-press: %d\n", x->LS_X, x->LS_Y, x->LS_PRESS);
	printf("RS-x: %d, RS-y: %d, RS-press: %d\n", x->RS_X, x->RS_Y, x->RS_PRESS);
}

int main() {
	//system("/bin/echo commandhere"); //Execute bash commands from C++
	//Call the bluetooth.bash script here
	

	//Copy disable_ertm config to /etc/modprobe.d/disable_ertm.conf
	char buf[100];
	int src = open("disable_ertm.conf", O_RDONLY, 0);
	int dst = open("/etc/modprobe.d/disable_ertm.conf", O_WRONLY | O_CREAT, 0644);
	size_t size = read(src, buf, 100);
	write(dst, buf, size);
	close(src);
	close(dst);


	//Initialize controller models
	controller_t* input_controller; 
  	controller_t* output_controller = new snes_controller_t();
  

	//Find which event# datastreams are for controller / consumer control device
	string line;
	string event_controller, event_consumer;
	int event_position;
	int devices_found = 0;
	ifstream devices_list("/proc/bus/input/devices");
	
	while(getline(devices_list, line) && devices_found != 2) {
		if (line.find("Vendor=054c Product=05c4", 0) != string::npos) {
			getline(devices_list, line);
			if (line.find("\"Wireless Controller\"", 0) != string::npos) {
				while( getline(devices_list, line) ) {
					if ((event_position = line.find("event", 0)) != (int) string::npos) {
						event_controller = line.substr(event_position+5,2);
						devices_found++;
						input_controller = new ps4_controller_t();
						printf("PlayStation 4 Controller detected on event%s\n", event_controller.c_str());
						continue;
					}
				}
			}
		}
		if (line.find("Vendor=045e Product=02fd", 0)  != string::npos) { //Xbox One
			getline(devices_list, line);
			if (line.find("Consumer Control", 0) != string::npos) {
				while( getline(devices_list, line) ) {
					if ((event_position = line.find("event", 0)) != (int) string::npos) {
						event_consumer = line.substr(event_position+5, 2);
						devices_found++;
						printf("Xbox One Consumer Control detected on event%s\n", event_consumer.c_str());
						break;
					}
				}
			}
			else {
				while( getline(devices_list, line) ) {
					if ((event_position = line.find("event", 0)) != (int) string::npos) {
						event_controller = line.substr(event_position+5, 2);
						devices_found++;
						printf("Xbox One Controller detected on event%s\n", event_controller.c_str());
						input_controller = new xbox_controller_t();
						break;
					}
				}
			}
		}
	}

	if (devices_found == 0) {
		printf("Input device not found!\n");
		return 0;
	}


	//Initialize converter
	ControllerConverter* converter;
	converter = ControllerConverterFactory::createConverter(*input_controller, *output_controller);


	//Set pin modes and interrupts
	snesbackend::setup();
	snesbackend::update_controller((snes_controller_t*) output_controller);


	//Monitor event channels for input
	string event_string = "/dev/input/event";
	struct pollfd fds[2];
	event_controller.erase(std::remove(event_controller.begin(), event_controller.end(), ' '), event_controller.end());
	fds[0].events = POLLIN;
        fds[0].fd = open(event_string.append(event_controller).c_str(), O_RDONLY);


	if (devices_found == 2) {
		event_consumer.erase(std::remove(event_consumer.begin(), event_consumer.end(), ' '), event_consumer.end());
		fds[1].events = POLLIN;
		event_string = "/dev/input/event";
		fds[1].fd = open(event_string.append(event_consumer).c_str(), O_RDONLY);
	}
	
	printf("Starting input collection...\n");

	while (1) {
		poll(fds, 2, -1);

		if (fds[0].revents & POLLIN) {
			read(fds[0].fd, (char*)&button_struct, sizeof(button_struct));
			if (button_struct.code == 4 || button_struct.type == 0) {
				continue;
			}
			read_xbox_buttons(button_struct, (xbox_controller_t*) input_controller);
			print_xbox_controller_state((xbox_controller_t*) input_controller);

			//conversion step
			converter->convert(*input_controller, *output_controller, "user config path goes here");
			print_snes_controller_state((snes_controller_t*) output_controller);
		}

		if (fds[1].revents & POLLIN) {
			read(fds[1].fd, (char*)&button_struct, 16);
			read_xbox_buttons(button_struct, (xbox_controller_t*) input_controller);
			print_xbox_controller_state((xbox_controller_t*) input_controller);

			//convserion step
			converter->convert(*input_controller, *output_controller, "user config path goes here");
			print_snes_controller_state((snes_controller_t*) output_controller);
		}
	}

	return 0;
}
