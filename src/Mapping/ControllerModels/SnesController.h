#include <Controller.h>
#include <unistd.h>
#include <fcntl.h>

#ifndef SNES_CONTROLLER_H
#define SNES_CONTROLLER_H

struct snes_controller_t: controller_t {
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

	snes_controller_t() {
		type = SNES;
	}

	virtual bool snes_combo_pressed() override {
	        return false;
	}
	 
	virtual bool nes_combo_pressed() override {
	        return false;
	}

	virtual void read_buttons(button_struct_t b) override {
		return;
	}
	
	virtual void print_state() override {
		printf("\n---SNES Controller State---\n");

		printf("A: %d, B: %d, X: %d, Y: %d\n", A, B, X, Y);
		printf("D-up: %d, D-down: %d, D-left: %d, D-right: %d\n", D_UP, D_DOWN, D_LEFT, D_RIGHT);
		printf("LB: %d, RB: %d\n", LB, RB);
		printf("Select: %d, Start: %d\n\n", SELECT, START);
	}

	virtual void send_state() override {
		int serial_fd = open("/dev/ttyS0", O_WRONLY);
		if (serial_fd == 0) {
			return;
		}
		unsigned char data[3] = {0, 0, 0};
		data[0] = 0xFF; 
		data[1] |= (this->B ? 1 : 0 ) << 0;
		data[1] |= (this->Y ? 1 : 0 ) << 1;
		data[1] |= (this->SELECT ? 1 : 0 ) << 2;
		data[1] |= (this->START ? 1 : 0 ) << 3;
		data[1] |= (this->D_UP ? 1 : 0 ) << 4;
		data[1] |= (this->D_DOWN ? 1 : 0 ) << 5;
		data[1] |= (this->D_LEFT ? 1 : 0 ) << 6;
		data[1] |= (this->D_RIGHT ? 1 : 0 ) << 7;
		data[2] |= (this->A ? 1 : 0 ) << 0;
		data[2] |= (this->X ? 1 : 0 ) << 1;
		data[2] |= (this->LB ? 1 : 0 ) << 2;
		data[2] |= (this->RB ? 1 : 0 ) << 3;
		write(serial_fd, data, sizeof(data));
		close(serial_fd);
	}
};

#endif
