#include <Controller.h>

#ifndef SMS_CONTROLLER_H
#define SMS_CONTROLLER_H

struct sms_controller_t: controller_t {

	sms_controller_t() {
		type = SMS;

		//Note: these strings must be exactly the ones used in config files
		button_states["1"] = 0;
		button_states["2"] = 0;
		button_states["D_UP"] = 0;
		button_states["D_DOWN"] = 0;
		button_states["D_LEFT"] = 0;
		button_states["D_RIGHT"] = 0;
	}

	virtual int combo_pressed() override {return false;}
	virtual void read_buttons(button_struct_t b) override {return;}
	virtual int get_mapped_button_state(std::string button, std::map<std::string, std::string> user_map) override {return false;}

	virtual void print_state() override {
		printf("\n---Master System Controller State---\n");
		printf("1: %d, 2: %d\n", button_states["1"], button_states["2"]);
		printf("D-up: %d, D-down: %d, D-left: %d, D-right: %d\n", button_states["D_UP"], button_states["D_DOWN"], button_states["D_LEFT"], button_states["D_RIGHT"]);
	}

	virtual void send_state(int serial_fd, unsigned char data[2]) override {
	        data[0] = 0;
		data[0] |= (this->button_states["D_UP"] ? 1 : 0 ) << 0;
		data[0] |= (this->button_states["D_DOWN"] ? 1 : 0 ) << 1;
		data[0] |= (this->button_states["D_LEFT"] ? 1 : 0 ) << 2;
		data[0] |= (this->button_states["D_RIGHT"] ? 1 : 0 ) << 3;
		data[0] |= (this->button_states["1"] ? 1 : 0 ) << 4;
		data[0] |= (this->button_states["2"] ? 1 : 0 ) << 5;
		data[0] = ~data[0];
		write(serial_fd, data, 2);
	}
};

#endif
