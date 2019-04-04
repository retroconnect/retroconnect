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
/***************************************************/

void clock_isr() {
	cout << "Hardware Button Pressed!\n" << endl;
}

void latch_isr() {
	cout << "Hardware Button Pressed!\n" << endl;
}


void setup_pins() {
	wiringPiSetup();

	pinMode(DATA, OUTPUT);
	pinMode(CLOCK, INPUT);
	pinMode(LATCH, INPUT);

	wiringPiISR(CLOCK, INT_EDGE_FALLING, clock_isr);
	wiringPiISR(LATCH, INT_EDGE_FALLING, latch_isr);
}



void read_buttons(button_struct_t button_struct) {

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
				}
				else if (button_struct.value == 0) {
					printf("DPAD-X Released\n");
				}
				else {
					printf("DPAD-Left\n");
				}
				break;
			case(DPAD_Y):
				if (button_struct.value == 1) {
					printf("DPAD-Down\n");
				}
				else if (button_struct.value == 0) {
					printf("DPAD-Y Released\n");
				}
				else {
					printf("DPAD-Up\n");
				}
				break;
			case(BTN_A):
				if (button_struct.value == 0) {
					printf("A released\n");
				}
				else {
					printf("A pressed\n");
				}
				break;
			case(BTN_B):
				if (button_struct.value == 0) {
					printf("B released\n");
				}
				else {
					printf("B pressed\n");
				}
				break;
			case(BTN_X):
				if (button_struct.value == 0) {
					printf("X released\n");
				}
				else {
					printf("X pressed\n");
				}
				break;
			case(BTN_Y):
				if (button_struct.value == 0) {
					printf("Y released\n");
				}
				else {
					printf("Y pressed\n");
				}
				break;
			case(BTN_LB):
				if (button_struct.value == 0) {
					printf("LB released\n");
				}
				else {
					printf("LB pressed\n");
				}
				break;
			case(BTN_RB):
				if (button_struct.value == 0) {
					printf("RB released\n");
				}
				else {
					printf("RB pressed\n");
				}
				break;
			case(BTN_START):
				if (button_struct.value == 0) {
					printf("Start released\n");
				}
				else {
					printf("Start pressed\n");
				}
				break;
			case(BTN_SELECT):
				if (button_struct.value == 0) {
					printf("Select released\n");
				}
				else {
					printf("Select pressed\n");
				}
				break;
			case(BTN_LS):
				if (button_struct.value == 0) {
					printf("Left Thumb released\n");
				}
				else {
					printf("Left Thumb pressed\n");
				}
				break;
			case(BTN_RS):
				if (button_struct.value == 0) {
					printf("Right Thumb released\n");
				}
				else {
					printf("Right Thumb pressed\n");
				}
				break;
			case(BTN_HOME):
				if (button_struct.value == 0) {
					printf("Home released\n");
				}
				else {
					printf("Home pressed\n");
				}
				break;
			case(RIGHT_TRIGGER):
				if (button_struct.value == 0) {
					printf("Right Trigger released\n");
				}
				else {
					printf("Right Trigger pressed\n");
				}
				break;
			case(LEFT_TRIGGER):
				if (button_struct.value == 0) {
					printf("Left Trigger released\n");
				}
				else {
					printf("Left Trigger pressed\n");
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
	setup_pins();


	//DBUS Bluetooth Setup
	// Chris


	//Find which event# datastreams are for controller / consumer control device
	string line;
	char event_controller, event_consumer;
	int event_position;
	int exit = 0;
	ifstream devices_list("/proc/bus/input/devices");

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
			read_buttons(button_struct);
		}

		if (fds[1].revents & POLLIN) {
			read(fds[1].fd, (char*)&button_struct, 16);
			read_buttons(button_struct);
		}
	}

	return 0;
}


