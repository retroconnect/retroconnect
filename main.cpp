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

//#include <experimental/filesystem>

//Mapping 1
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
#define RIGHT_TRIGGER   0x09
#define LEFT_TRIGGER    0x0A

//Mapping 2
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

using namespace std;
//namespace fs=std::experimental::filesystem;


#define DATA 27
#define CLOCK 28
#define LATCH 29

struct button_struct_t {        //16 bytes total
	struct timeval time;   //8 bytes
	unsigned short type;   //2 bytes
	unsigned short code;   //2 bytes
	unsigned int value;    //4 bytes
} button_struct;

/*void setupPins() {
	wiringPiSetup();

	pinMode(DATA, OUTPUT);
	pinMode(CLOCK, INPUT);
	pinMode(LATCH, INPUT);

	wiringPiISR(CLOCK, INT_EDGE_FALLING, isr);
	wiringPiISR(LATCH, INT_EDGE_FALLING, isr);
}*/

void isr(void)
{
	cout << "Hardware Button Pressed" << endl;
}


void read_buttons(button_struct_t button_struct) {

	if(button_struct.type) {
		switch(button_struct.code) {
			case(4): break;
			case(0):
				printf("Left Analog Stick Y\n");
				break;
			case(1):
				printf("Left Analog Stick X\n");
				break;
			case(2):
				printf("Right Analog Stick Y\n");
				break;
			case(5):
				printf("Right Analog Stick X\n");
						break;
			case(16):
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
			case(17):
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
			case(BTN_RB): //Top Right
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
			case(RIGHT_TRIGGER): //Right Trigger
				if (button_struct.value == 0) {
					printf("Right Trigger released\n");
				}
				else {
					printf("Right Trigger pressed\n");
				}
				break;
			case(LEFT_TRIGGER): //Left Trigger
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

	//printf("\nButton Timestamp: %08X", button_struct.time);
	//printf("\nButton Type: %02X", button_struct.type);
	//printf("\nButton Code: %02X", button_struct.code);
	//printf("\nButton Value: %04X\n", button_struct.value);
}


int main() {
	//cout << "Hello world" << endl;   //Print to standard output
	//system("/bin/echo commandhere"); //Execute bash commands from C++

	//Copy disable_ertm config to /etc/modprobe.d/disable_ertm.conf
	//std::filesystem::copy("./disable_etrm.conf", "./deleteme/disable_etrm.conf");

	//Set pin modes and interrupts
	//SetupPins();

	//DBUS Bluetooth Setup
	//(Chris)

	//Find which event# datastreams are for controller / consumer control device
	//ifstream myfile("/proc/bus/input/devices");

	//Get datastream from event#'s
	//ifstream event_handle("/dev/input/event8", std::ios::binary);
	////ifstream home_button("/dev/input/event9", std::ios::binary);

	struct pollfd fds[2];
	int ret;

	fds[0].fd = open("/dev/input/event8", O_RDONLY);
	fds[1].fd = open("/dev/input/event9", O_RDONLY);

	fds[0].events = POLLIN;
	fds[1].events = POLLIN;


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


