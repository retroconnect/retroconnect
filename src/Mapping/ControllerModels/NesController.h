#include <Controller.h>
#include <unistd.h>
#include <fcntl.h>

#ifndef NES_CONTROLLER_H
#define NES_CONTROLLER_H

struct nes_controller_t: controller_t {
	bool A;
	bool B;
	bool SELECT;
	bool START;
	bool D_UP;
	bool D_DOWN;
	bool D_LEFT;
	bool D_RIGHT;

	nes_controller_t() {
		type = NES;
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
		printf("\n---NES Controller State---\n");

		printf("A: %d, B: %d\n", A, B);
		printf("D-up: %d, D-down: %d, D-left: %d, D-right: %d\n", D_UP, D_DOWN, D_LEFT, D_RIGHT);
		printf("Select: %d, Start: %d\n\n", SELECT, START);
	}

	virtual void send_state(int serial_fd, unsigned char data[3]) override {
		data[1] = 0;
		data[2] = 0;
		data[1] |= (this->A ? 1 : 0 ) << 0;
		data[1] |= (this->B ? 1 : 0 ) << 1;
		data[1] |= (this->SELECT ? 1 : 0 ) << 2;
		data[1] |= (this->START ? 1 : 0 ) << 3;
		data[1] |= (this->D_UP ? 1 : 0 ) << 4;
		data[1] |= (this->D_DOWN ? 1 : 0 ) << 5;
		data[1] |= (this->D_LEFT ? 1 : 0 ) << 6;
		data[1] |= (this->D_RIGHT ? 1 : 0 ) << 7;
		write(serial_fd, &data, sizeof(data));
	}

};

#endif
