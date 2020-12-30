#include <Controller.h>

#ifndef GEN_CONTROLLER_H
#define GEN_CONTROLLER_H

struct gen_controller_t: controller_t {

	gen_controller_t() {
		type = GEN;

		//Note: these strings must be exactly the ones used in config files
		button_states["A"] = 0;
		button_states["B"] = 0;
		button_states["C"] = 0;
		button_states["X"] = 0;
		button_states["Y"] = 0;
		button_states["Z"] = 0;
		button_states["D_UP"] = 0;
		button_states["D_DOWN"] = 0;
		button_states["D_LEFT"] = 0;
		button_states["D_RIGHT"] = 0;
		button_states["START"] = 0;
		button_states["MODE"] = 0;
	}

	virtual int combo_pressed() override {return false;}
	virtual void read_buttons(button_struct_t* b) override {return;}
	virtual int get_mapped_button_state(std::string button, std::map<std::string, std::string> user_map) override {return false;}

	virtual void print_state() override {
		printf("\n---GEN Controller State---\n");
		printf("A: %d, B: %d, C: %d, X: %d, Y: %d, Z: %d\n", button_states["A"], button_states["B"], button_states["C"], button_states["X"], button_states["Y"], button_states["Z"]);
		printf("D-up: %d, D-down: %d, D-left: %d, D-right: %d\n", button_states["D_UP"], button_states["D_DOWN"], button_states["D_LEFT"], button_states["D_RIGHT"]);
		printf("Start: %d\n\n", button_states["START"]);
	}

	virtual void send_state(int serial_fd, unsigned char data[2]) override {
	        data[0] = 0;
		data[1] = 0;
		data[0] |= (this->button_states["D_UP"] ? 1 : 0 ) << 0;
		data[0] |= (this->button_states["D_DOWN"] ? 1 : 0 ) << 1;
		data[0] |= (this->button_states["D_LEFT"] ? 1 : 0 ) << 2;
		data[0] |= (this->button_states["D_RIGHT"] ? 1 : 0 ) << 3;
		data[0] |= (this->button_states["B"] ? 1 : 0 ) << 4;
		data[0] |= (this->button_states["C"] ? 1 : 0 ) << 5;
		data[0] |= (this->button_states["A"] ? 1 : 0 ) << 6;
		data[0] |= (this->button_states["START"] ? 1 : 0 ) << 7;
		data[1] |= (this->button_states["MODE"] ? 1 : 0 ) << 0;
		data[1] |= (this->button_states["Z"] ? 1 : 0 ) << 1;
		data[1] |= (this->button_states["Y"] ? 1 : 0 ) << 2;
		data[1] |= (this->button_states["X"] ? 1 : 0 ) << 3;
		data[0] = ~data[0];
		data[1] = ~data[1];
		write(serial_fd, data, 2);
	}
};

#endif
