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

struct xbox_controller_t {
	bool A;
	bool B;
	bool X;
	bool Y;
	bool D_UP;
	bool D_DOWN;
	bool D_LEFT;
	bool D_RIGHT;
	bool SELECT;
	bool START;
	bool HOME;
	bool LS_PRESS;
	bool RS_PRESS;
	bool LB;
	bool RB;

	int LT;
	int RT;
	int LS_X;
	int LS_Y;
	int RS_X;
	int RS_Y; 
} xbox_controller;

struct snes_controller_t {
	bool A;
	bool B;
	bool X;
	bool Y;
	bool D_UP;
	bool D_DOWN;
	bool D_LEFT;
	bool D_RIGHT;
	bool SELECT;
	bool START;
	bool LB;
	bool RB;
} snes_controller;


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



void read_buttons(button_struct_t button_struct, xbox_controller_t input_controller) {

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
					input_controller.D_RIGHT = true;
				}
				else if (button_struct.value == 0) {
					printf("DPAD-X Released\n");
					input_controller.D_RIGHT = false;
					input_controller.D_LEFT = false;
				}
				else {
					printf("DPAD-Left\n");
					input_controller.D_LEFT = true;
				}
				break;
			case(DPAD_Y):
				if (button_struct.value == 1) {
					printf("DPAD-Down\n");
					input_controller.D_DOWN = true;
				}
				else if (button_struct.value == 0) {
					printf("DPAD-Y Released\n");
					input_controller.D_DOWN = false;
					input_controller.D_UP = false;
				}
				else {
					printf("DPAD-Up\n");
					input_controller.D_UP = true;
				}
				break;
			case(BTN_A):
				if (button_struct.value == 0) {
					printf("A released\n");
					input_controller.A = false;
				}
				else {
					printf("A pressed\n");
					input_controller.A = true;
				}
				break;
			case(BTN_B):
				if (button_struct.value == 0) {
					printf("B released\n");
					input_controller.B = false;
				}
				else {
					printf("B pressed\n");
					input_controller.B = true;
				}
				break;
			case(BTN_X):
				if (button_struct.value == 0) {
					printf("X released\n");
					input_controller.X = false;
				}
				else {
					printf("X pressed\n");
					input_controller.X = true;
				}
				break;
			case(BTN_Y):
				if (button_struct.value == 0) {
					printf("Y released\n");
					input_controller.Y = false;
				}
				else {
					printf("Y pressed\n");
					input_controller.Y = true;
				}
				break;
			case(BTN_LB):
				if (button_struct.value == 0) {
					printf("LB released\n");
					input_controller.LB = false;
				}
				else {
					printf("LB pressed\n");
					input_controller.LB = true;
				}
				break;
			case(BTN_RB):
				if (button_struct.value == 0) {
					printf("RB released\n");
					input_controller.RB = false;
				}
				else {
					printf("RB pressed\n");
					input_controller.RB = true;
				}
				break;
			case(BTN_START):
				if (button_struct.value == 0) {
					printf("Start released\n");
					input_controller.START = false;
				}
				else {
					printf("Start pressed\n");
					input_controller.START = true;
				}
				break;
			case(BTN_SELECT):
				if (button_struct.value == 0) {
					printf("Select released\n");
					input_controller.SELECT = false;
				}
				else {
					printf("Select pressed\n");
					input_controller.SELECT = true;
				}
				break;
			case(BTN_LS):
				if (button_struct.value == 0) {
					printf("Left Thumb released\n");
					input_controller.LS_PRESS = false;
				}
				else {
					printf("Left Thumb pressed\n");
					input_controller.LS_PRESS = true;
				}
				break;
			case(BTN_RS):
				if (button_struct.value == 0) {
					printf("Right Thumb released\n");
					input_controller.RS_PRESS = false;
				}
				else {
					printf("Right Thumb pressed\n");
					input_controller.RS_PRESS = true;
				}
				break;
			case(BTN_HOME):
				if (button_struct.value == 0) {
					printf("Home released\n");
					input_controller.HOME = false;
				}
				else {
					printf("Home pressed\n");
					input_controller.HOME = true;
				}
				break;
			case(RIGHT_TRIGGER):
				if (button_struct.value == 0) {
					printf("Right Trigger released\n");
					input_controller.RT = 0;
				}
				else {
					printf("Right Trigger pressed\n");
					input_controller.RT = 1;
				}
				break;
			case(LEFT_TRIGGER):
				if (button_struct.value == 0) {
					printf("Left Trigger released\n");
					input_controller.LT = 0;
				}
				else {
					printf("Left Trigger pressed\n");
					input_controller.LT = 1;
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
	xbox_controller_t c = new xbox_controller_t();
	c.A = false;
	c.B = false;
	c.X = false;
	c.Y = false;

	c.D_DOWN = false;
	c.D_LEFT = false
	c.D_RIGHT = false;
	c.D_UP = false;

	c.HOME = false;
	c.SELECT = false;
	c.START = false;

	c.LB = false;
	c.RB = false;

	c.LS_PRESS = false;
	c.LS_X = 0;
	c.LS_Y = 0;

	c.RS_PRESS = false;
	c.RS_X = 0;
	c.RS_Y = 0;

	c.LT = 0;
	c.RT = 0;

	return c;
}

void print_xbox_controller_state(xbox_controller_t x) {
	printf("Current state of xbox controller: \n");

	printf("A: " + x.A + ", B: " + x.B + ", X: " + x.X + ", Y: " + x.Y + "\n");
	printf("D-up: " + x.D_UP + ", D-down: " + x.D_DOWN + ", D-left: " + x.D_LEFT + ", D-right: " + x.D_RIGHT + "\n");
	printf("LT: " + x.LT + ", RT: " + x.RT + "\n");
	printf("LB: " + x.LB + ", RB: " + x.RB + "\n");
	printf("Select: " + x.SELECT + ", Home: " + x.HOME + ", Start: " + x.START + "\n");
	printf("LS-x: " + x.LS_X + ", LS-y: " + x.LS_Y + ", LS-press: " + x.LS_PRESS + "\n");
	printf("RS-x: " + x.RS_X + ", RS-y: " + x.RS_Y + ", RS-press: " + x.RS_PRESS + "\n");
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


	//initialize controller model
	xbox_controller_t input_controller = init_xbox_controller();

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
			read_buttons(button_struct, input_controller);
			print_xbox_controller_state();
		}

		if (fds[1].revents & POLLIN) {
			read(fds[1].fd, (char*)&button_struct, 16);
			read_buttons(button_struct, input_controller);
			print_xbox_controller_state();
		}
	}

	return 0;
}


