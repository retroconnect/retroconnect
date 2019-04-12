using namespace std;
#include <iostream>
#include <stdlib.h>
// #include <wiringPi.h>
#include <sys/time.h>
#include <fstream>
#include <iostream>
#include <string>
#include <poll.h>
#include <unistd.h>
#include <fcntl.h>
#include <typeinfo>


#include "Mapping/ControllerModels/Controller.h"
#include "Mapping/ControllerModels/SnesController.h"
#include "Mapping/ControllerModels/XboxController.h"
#include "Mapping/ControllerConverters/ControllerConverter.h"
#include "Mapping/ControllerConverters/ControllerConverterFactory.h"

#define DATA 27
#define CLOCK 28
#define LATCH 29

//iXbox One Mapping
#define BTN_A		0x130
#define BTN_B		0x131
#define BTN_X		0x133
#define BTN_Y		0x134
#define BTN_LB		0x136
#define BTN_RB		0x137
#define BTN_SELECT	0x9E
#define BTN_START	0x13B
#define BTN_LS		0x13D
#define BTN_RS		0x13E
#define BTN_HOME	0xAC
#define AXIS_0		0x00
#define AXIS_1		0x01
#define AXIS_2		0x02
#define AXIS_5		0x05
#define RIGHT_TRIGGER   0x09
#define LEFT_TRIGGER    0x0A
#define DPAD_X		0x10
#define DPAD_Y		0x11

//Xbox One Alternate Mapping (reconnected controller)
/*
#define BTN_A		0x130
#define BTN_B		0x131
#define BTN_X		0x132
#define BTN_Y		0x133
#define BTN_LB		0x134
#define BTN_RB		0x135
#define BTN_SELECT	0x136
#define BTN_START	0x137
#define BTN_LS		0x138
#define BTN_RS		0x139
#define BTN_HOME	0xAC
#define RIGHT_TRIGGER   0x09
#define LEFT_TRIGGER    0x0A
*/

/*
//PS4 Mappings
LT = Xbox Right Analog Y
RT = Xbox Right Analog X
Right Analog = 0x03
Square = Xbox Y
Triangle = Xbox X
PS_HOME = 0x13C
SELECT = 0x13A
LT-Digital = 0x138
RT-Digital = 0x139
*/


struct button_struct_t {        //16 bytes total
	struct timeval time;   //8 bytes
	unsigned short type;   //2 bytes
	unsigned short code;   //2 bytes
	unsigned int value;    //4 bytes
} button_struct;


/***************************************************/

void clock_isr() {
	cout << "Hardware Button Pressed!\n" << endl;
}

void latch_isr() {
	cout << "Hardware Button Pressed!\n" << endl;
}


// void setup_pins() {
// 	wiringPiSetup();

// 	pinMode(DATA, OUTPUT);
// 	pinMode(CLOCK, INPUT);
// 	pinMode(LATCH, INPUT);

// 	wiringPiISR(CLOCK, INT_EDGE_FALLING, clock_isr);
// 	wiringPiISR(LATCH, INT_EDGE_FALLING, latch_isr);
// }



void read_buttons(button_struct_t button_struct, xbox_controller_t *input_controller) {

	if(button_struct.type) {
		switch(button_struct.code) {
			case(4): break; //filters out row of input
			case(AXIS_0):
				printf("Left Analog Stick Y\n");
				break;
			case(AXIS_1):
				printf("Left Analog Stick X\n");
				break;
			case(AXIS_2):
				printf("Right Analog Stick Y\n");
				break;
			case(AXIS_5):
				printf("Right Analog Stick X\n");
						break;
			case(DPAD_X):
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
			case(DPAD_Y):
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
			case(BTN_A):
				if (button_struct.value == 0) {
					printf("A released\n");
					input_controller->A = false;
				}
				else {
					printf("A pressed\n");
					input_controller->A = true;
				}
				break;
			case(BTN_B):
				if (button_struct.value == 0) {
					printf("B released\n");
					input_controller->B = false;
				}
				else {
					printf("B pressed\n");
					input_controller->B = true;
				}
				break;
			case(BTN_X):
				if (button_struct.value == 0) {
					printf("X released\n");
					input_controller->X = false;
				}
				else {
					printf("X pressed\n");
					input_controller->X = true;
				}
				break;
			case(BTN_Y):
				if (button_struct.value == 0) {
					printf("Y released\n");
					input_controller->Y = false;
				}
				else {
					printf("Y pressed\n");
					input_controller->Y = true;
				}
				break;
			case(BTN_LB):
				if (button_struct.value == 0) {
					printf("LB released\n");
					input_controller->LB = false;
				}
				else {
					printf("LB pressed\n");
					input_controller->LB = true;
				}
				break;
			case(BTN_RB):
				if (button_struct.value == 0) {
					printf("RB released\n");
					input_controller->RB = false;
				}
				else {
					printf("RB pressed\n");
					input_controller->RB = true;
				}
				break;
			case(BTN_START):
				if (button_struct.value == 0) {
					printf("Start released\n");
					input_controller->START = false;
				}
				else {
					printf("Start pressed\n");
					input_controller->START = true;
				}
				break;
			case(BTN_SELECT):
				if (button_struct.value == 0) {
					printf("Select released\n");
					input_controller->SELECT = false;
				}
				else {
					printf("Select pressed\n");
					input_controller->SELECT = true;
				}
				break;
			case(BTN_LS):
				if (button_struct.value == 0) {
					printf("Left Thumb released\n");
					input_controller->LS_PRESS = false;
				}
				else {
					printf("Left Thumb pressed\n");
					input_controller->LS_PRESS = true;
				}
				break;
			case(BTN_RS):
				if (button_struct.value == 0) {
					printf("Right Thumb released\n");
					input_controller->RS_PRESS = false;
				}
				else {
					printf("Right Thumb pressed\n");
					input_controller->RS_PRESS = true;
				}
				break;
			case(BTN_HOME):
				if (button_struct.value == 0) {
					printf("Home released\n");
					input_controller->HOME = false;
				}
				else {
					printf("Home pressed\n");
					input_controller->HOME = true;
				}
				break;
			case(RIGHT_TRIGGER):
				if (button_struct.value == 0) {
					printf("Right Trigger released\n");
					input_controller->RT = 0;
				}
				else {
					printf("Right Trigger pressed\n");
					input_controller->RT = 1;
				}
				break;
			case(LEFT_TRIGGER):
				if (button_struct.value == 0) {
					printf("Left Trigger released\n");
					input_controller->LT = 0;
				}
				else {
					printf("Left Trigger pressed\n");
					input_controller->LT = 1;
				}
				break;

			default:
				printf("!!! Unknown button code: %d !!!\n", button_struct.code);
		}
	}

	// Print full struct for button press debugging
	//printf("\nButton Timestamp: %08X", button_struct.time);
	//printf("\nButton Type: %02X", button_struct.type);
	//printf("\nButton Code: %02X", button_struct.code);
	//printf("\nButton Value: %04X\n", button_struct.value);
}

xbox_controller_t init_xbox_controller() {	
	return {};
}

snes_controller_t init_snes_controller() {
	return {};
}

void print_xbox_controller_state(xbox_controller_t x) {
	printf("Current state of xbox controller: \n");

	printf("A: %d, B: %d, X: %d, Y: %d\n", x.A, x.B, x.X, x.Y);
	printf("D-up: %d, D-down: %d, D-left: %d, D-right: %d\n", x.D_UP, x.D_DOWN, x.D_LEFT, x.D_RIGHT);
	printf("LT: %d, RT: %d\n", x.LT, x.RT);
	printf("LB: %d, RB: %d\n", x.LB, x.RB);
	printf("Select: %d, Home: %d, Start: %d\n", x.SELECT, x.HOME, x.START);
	printf("LS-x: %d, LS-y: %d, LS-press: %d\n", x.LS_X, x.LS_Y, x.LS_PRESS);
	printf("RS-x: %d, RS-y: %d, RS-press: %d\n", x.RS_X, x.RS_Y, x.RS_PRESS);
}

int main() {
	//system("/bin/echo commandhere"); //Execute bash commands from C++

	//Copy disable_ertm config to /etc/modprobe.d/disable_ertm.conf
	char buf[100];
	size_t size;
	int src = open("disable_ertm.conf", O_RDONLY, 0);
	int dst = open("/etc/modprobe.d/disable_ertm.conf", O_WRONLY | O_CREAT, 0644);
	size = read(src, buf, 100);
	write(dst, buf, size);
	close(src);
	close(dst);


	//Set pin modes and interrupts
	// setup_pins();


	//DBUS Bluetooth Setup
	// Chris`


	//Find which event# datastreams are for controller / consumer control device
	string line;
	char event_controller, event_consumer;
	int event_position;
	int exit = 0;
	ifstream devices_list("/proc/bus/input/devices");


	//initialize controller models
	xbox_controller_t input_controller = init_xbox_controller();
	snes_controller_t output_controller;

	//initialize converter
	ControllerConverter* converter;
	converter = ControllerConverterFactory::createConverter(input_controller, output_controller);

	while(getline(devices_list, line) && exit != 2) {
		if (line.find("Xbox Wireless Controller", 0)  != string::npos) {
			if (line.find("Consumer Control", 0) != string::npos) {
				while( getline(devices_list, line) ) {
					if ((event_position = line.find("event", 0)) != string::npos) {
						event_consumer = line.at(event_position+5);
						exit++;
						printf("Consumer Control is event%c\n", event_consumer);
						break;
					}
				}
			}
			else {
				while( getline(devices_list, line) ) {
					if ((event_position = line.find("event", 0)) != string::npos) {
						event_controller = line.at(event_position+5);
						exit++;
						printf("Controller is event%c\n", event_controller);
						break;
					}
				}
			}
		}
	}

	if (exit == 0) {
		printf("Input device not found!\n");
		return 0;
	}

	//Monitor event channels for input
	struct pollfd fds[2];
	fds[0].events = POLLIN;
	fds[1].events = POLLIN;

	//PS4 test
	//fds[0].fd = open("/dev/input/event10", O_RDONLY);

	string event_string = "/dev/input/event";
	fds[0].fd = open(event_string.append(1, event_controller).c_str(), O_RDONLY);
	event_string = "/dev/input/event";
	fds[1].fd = open(event_string.append(1, event_consumer).c_str(), O_RDONLY);

	printf("Starting input collection...\n");

	while (1) {
		poll(fds, 2, -1);

		if (fds[0].revents & POLLIN) {
			read(fds[0].fd, (char*)&button_struct, 16);
			read_buttons(button_struct, &input_controller);
			print_xbox_controller_state(input_controller);

			//conversion step
			output_controller = converter->convert(input_controller, "user config path goes here");
		}

		if (fds[1].revents & POLLIN) {
			read(fds[1].fd, (char*)&button_struct, 16);
			read_buttons(button_struct, &input_controller);
			print_xbox_controller_state(input_controller);
			output_controller =  converter->convert(input_controller, "user config path goes here");
		}
	}

	return 0;
}


