#include <Controller.h>
#include <unistd.h>
#include <fcntl.h>

#ifndef ATARI_2600_CONTROLLER_H
#define ATARI_2600_CONTROLLER_H

struct atari_2600_controller_t: controller_t {

	atari_2600_controller_t() {
		type = ATARI_2600;

		//Note: these strings must be exactly the ones used in config files
		button_states["BUTTON"] = 0;
		button_states["D_UP"] = 0;
		button_states["D_DOWN"] = 0;
		button_states["D_LEFT"] = 0;
		button_states["D_RIGHT"] = 0;
	}

	virtual int combo_pressed() override {return false;}
	virtual void read_buttons(button_struct_t b) override {return;}
	virtual int get_mapped_button_state(std::string button, std::map<std::string, std::string> user_map) override {return false;}
	
	virtual void print_state() override {
		printf("\n---Atari 2600 Controller State---\n");
		printf("Button: %d\n", button_states["BUTTON"]);
		printf("D-up: %d, D-down: %d, D-left: %d, D-right: %d\n", button_states["D_UP"], button_states["D_DOWN"], button_states["D_LEFT"], button_states["D_RIGHT"]);
	}

	virtual void send_state(int serial_fd, unsigned char data[2]) override {
	        data[0] = 0;
		data[0] |= (this->button_states["D_UP"] ? 1 : 0 ) << 0;
		data[0] |= (this->button_states["D_DOWN"] ? 1 : 0 ) << 1;
		data[0] |= (this->button_states["D_LEFT"] ? 1 : 0 ) << 2;
		data[0] |= (this->button_states["D_RIGHT"] ? 1 : 0 ) << 3;
		data[0] |= (this->button_states["BUTTON"] ? 1 : 0 ) << 4;
		data[0] = ~data[0];
		write(serial_fd, data, 2);
	}
};

#endif
