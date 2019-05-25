#include <Controller.h>
#include <unistd.h>
#include <fcntl.h>

#ifndef NES_CONTROLLER_H
#define NES_CONTROLLER_H

struct nes_controller_t: controller_t {

	nes_controller_t() {
		type = NES;

		//Note: these strings must be exactly the ones used in config files
		button_states["A"] = 0;
		button_states["B"] = 0;
		button_states["D_UP"] = 0;
		button_states["D_DOWN"] = 0;
		button_states["D_LEFT"] = 0;
		button_states["D_RIGHT"] = 0;
		button_states["SELECT"] = 0;
		button_states["START"] = 0;
	}

	virtual bool snes_combo_pressed() override {
                return false;
        }
            
        virtual bool nes_combo_pressed() override {
                return false;
        }
	
	virtual bool gen_combo_pressed() override {
		return false;
	}

	virtual void read_buttons(button_struct_t b) override {
	        return;
	}

	virtual void print_state() override {
		printf("\n---NES Controller State---\n");

		printf("A: %d, B: %d\n", button_states["A"], button_states["B"]);
		printf("D-up: %d, D-down: %d, D-left: %d, D-right: %d\n", button_states["D_UP"], button_states["D_DOWN"], button_states["D_LEFT"], button_states["D_RIGHT"]);
		printf("Select: %d, Start: %d\n\n", button_states["SELECT"], button_states["START"]);
	}

	virtual void send_state(int serial_fd, unsigned char data[3]) override {
		data[1] = 0;
		data[2] = 0;
		data[1] |= (this->button_states["A"] ? 1 : 0 ) << 0;
		data[1] |= (this->button_states["B"] ? 1 : 0 ) << 1;
		data[1] |= (this->button_states["SELECT"] ? 1 : 0 ) << 2;
		data[1] |= (this->button_states["START"] ? 1 : 0 ) << 3;
		data[1] |= (this->button_states["D_UP"] ? 1 : 0 ) << 4;
		data[1] |= (this->button_states["D_DOWN"] ? 1 : 0 ) << 5;
		data[1] |= (this->button_states["D_LEFT"] ? 1 : 0 ) << 6;
		data[1] |= (this->button_states["D_RIGHT"] ? 1 : 0 ) << 7;
		write(serial_fd, &data, sizeof(data));
	}

};

#endif
