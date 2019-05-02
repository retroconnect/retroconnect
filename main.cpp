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
#include "NesController.h"
#include "SnesController.h"
#include "XboxController.h"
#include "Ps4Controller.h"
#include "ControllerConverter.h"
#include "XboxToNesControllerConverter.h"
#include "XboxToSnesControllerConverter.h"
#include "Ps4ToNesControllerConverter.h"
#include "Ps4ToSnesControllerConverter.h"
#include "ControllerConverterFactory.h"
#include "NESBackend.h"
#include "SNESBackend.h"


/***************************************************/

int main() {
	
	//Set serial baud rate
	system("sudo stty -F /dev/ttyS0 115200");
	

	//Copy disable_ertm config to /etc/modprobe.d/disable_ertm.conf
	char buf[100];
	int src = open("disable_ertm.conf", O_RDONLY, 0);
	int dst = open("/etc/modprobe.d/disable_ertm.conf", O_WRONLY | O_CREAT, 0644);
	size_t size = read(src, buf, 100);
	write(dst, buf, size);
	close(src);
	close(dst);


	//Initialize controller models (SNES default output)
	controller_t* input_controller; 
  	controller_t* output_controller = new snes_controller_t();


	//Find which event# datastreams are for controller / consumer control device
	string line, event_controller, event_consumer;
	int event_position;
	int devices_found = 0;
	ifstream devices_list("/proc/bus/input/devices");

	while(devices_found == 0) {	
		while(getline(devices_list, line) && devices_found != 2) {
			if (line.find("Vendor=054c Product=05c4", 0) != string::npos) { //PlayStation 4
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
					while( getline(devices_list, line) ) { //Xbox One Consumer Control
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
			printf("Supported input device not connected, scanning for supported Bluetooth controller...\n");
			if (system("bash bluetooth.bash") == 2) {
				return 0;
			}

			printf("\nBluetooth controller found!\n");
			devices_list.clear();
			devices_list.seekg(0);
		}
	}


	//Initialize converter
	ControllerConverter* converter;
	converter = ControllerConverterFactory::createConverter(*input_controller, *output_controller);

	//read user config and convert to map for converter
	std::map<std::string, std::string> userMap = {
		{"A", "B "},
		{"B", "A "},
		{"X", "X "},
		{"Y", "Y "},
		{"START", "START "},
		{"SELECT", "SELECT "},
		{"LB", "LB LT "},
		{"RB", "RB RT "},
		{"D_LEFT", "D_LEFT LS_LEFT "},
		{"D_RIGHT", "D_RIGHT LS_RIGHT "},
		{"D_UP", "D_UP LS_UP "},
		{"D_DOWN", "D_DOWN LS_DOWN "},
		{"TRIGGER_DEADZONE", "100"},
		{"STICK_DEADZONE", "10000"}
		//map built on this config: (xbox to snes)
		// A=A
		// B=B
		// X=X
		// Y=Y
		// START=START
		// SELECT=SELECT
		// HOME=NULL
		// LS_PRESS=NULL
		// RS_PRESS=NULL
		// LB=LB
		// RB=RB
		// LT=LB
		// RT=RB
		// TRIGGER_DEADZONE=100
		// D_LEFT=D_LEFT
		// D_RIGHT=D_RIGHT
		// D_DOWN=D_DOWN
		// D_UP=D_UP
		// LS_LEFT=D_LEFT
		// LS_RIGHT=D_RIGHT
		// LS_UP=D_UP
		// LS_DOWN=D_DOWN
		// RS_LEFT=NULL
		// RS_RIGHT=NULL
		// RS_UP=NULL
		// RS_DOWN=NULL
		// STICK_DEADZONE=10000
	};


	//Set pin modes and interrupts
	snesbackend::setup();
	snesbackend::update_controller((snes_controller_t*) output_controller);


	//Setup input streams
	string event_string = "/dev/input/event";
	struct pollfd fds[2];
	event_controller.erase(std::remove(event_controller.begin(), event_controller.end(), ' '), event_controller.end());
	fds[0].events = POLLIN;
        fds[0].fd = open(event_string.append(event_controller).c_str(), O_RDONLY);

	if (devices_found == 2) { //Special handling for Xbox One Consumer Control
		event_consumer.erase(std::remove(event_consumer.begin(), event_consumer.end(), ' '), event_consumer.end());
		fds[1].events = POLLIN;
		event_string = "/dev/input/event";
		fds[1].fd = open(event_string.append(event_consumer).c_str(), O_RDONLY);
	}
	

	//Monitor streams for input
	printf("Starting input collection...\n");
	struct button_struct_t button_struct;
	unsigned char data[3] = {0xFF, 0, 0};
	int serial_fd = open("/dev/ttyS0", O_WRONLY);
	if (serial_fd == 0) {
		printf("Teensy not connected!");
		return 0;
	}

	while (1) {
		poll(fds, 2, -1);

		if (fds[0].revents & POLLIN) {
			read(fds[0].fd, (char*)&button_struct, sizeof(button_struct));
			if (button_struct.type != 1 && button_struct.type != 3) {
				continue;
			}
			
			input_controller->read_buttons(button_struct);
			
			if(input_controller->snes_combo_pressed()) {
				printf("Combo detected! Switching to SNES output\n");
				output_controller = new snes_controller_t();

				converter = ControllerConverterFactory::createConverter(*input_controller, *output_controller);
			}
			else if (input_controller->nes_combo_pressed()) {
				printf("Combo detected! Switching to NES output\n");
				output_controller = new nes_controller_t();

				converter = ControllerConverterFactory::createConverter(*input_controller, *output_controller);
			}

			//input_controller->print_state();

			//Convert button inputs to outputs
			converter->convert(*input_controller, *output_controller, userMap);
			//output_controller->print_state();
			
			//Send button state to Teensy
			output_controller->send_state(serial_fd, data);
		}

		if (fds[1].revents & POLLIN) {
			read(fds[1].fd, (char*)&button_struct, 16);
			if (button_struct.type != 1 && button_struct.type != 3) {
				continue;
			}
			
			//input_controller->read_buttons(button_struct);
			if (button_struct.code == XB1_BTN_HOME) {
				((xbox_controller_t*)input_controller)->button_states["HOME"] = button_struct.value;
			}	
			
			//input_controller->print_state();
			
			//Convert button inputs to outputs
			converter->convert(*input_controller, *output_controller, userMap);
			//output_controller->print_state();
			
			//Send button state to Teensy
			//output_controller->send_state();
		}	
	}

	return 0;
}
