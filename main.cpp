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


	//Initialize controller models (SNES default output)
	controller_t* input_controller; 
  	controller_t* output_controller = new snes_controller_t();

	//Find which event# datastreams are for controller / consumer control device
	string line, event_controller, event_consumer;
	int event_position;
	int devices_found = 0;
	ifstream devices_list("/proc/bus/input/devices");
	
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
				while( getline(devices_list, line) ) {
					if ((event_position = line.find("event", 0)) != (int) string::npos) {
						event_controller = line.substr(event_position+5, 2);
						devices_found++;
						printf("Xbox One Controller detected on event%s\n", event_controller.c_str());
						input_controller = new xbox_controller_t();
						input_controller->type = XB1;
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
			input_controller->read_buttons(button_struct);
			input_controller->print_state();

			if(input_controller->snes_combo_pressed())
				printf("Combo detected! Switching to SNES output\n");
				output_controller = new snes_controller_t();

				converter = ControllerConverterFactory::createConverter(*input_controller, *output_controller);
			}
			else if (input_controller->nes_combo_pressed()) {
				printf("Combo detected! Switching to NES output\n");
				output_controller = new nes_controller_t();

				converter = ControllerConverterFactory::createConverter(*input_controller, *output_controller);
			}

			//conversion step
			converter->convert(*input_controller, *output_controller, "user config path goes here");
			input_controller->print_state();
		}

		if (fds[1].revents & POLLIN) {
			read(fds[1].fd, (char*)&button_struct, 16);
			if (button_struct.code == 4 || button_struct.type == 0) {
				continue;
			}
			input_controller->read_buttons(button_struct);
			input_controller->print_state();
			
			//convserion step
			converter->convert(*input_controller, *output_controller, "user config path goes here");
			input_controller->print_state();
		}
	}

	return 0;
}
