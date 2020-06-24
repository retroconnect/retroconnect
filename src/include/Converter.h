#include <string>
#include <Controller.h>

#ifndef CONTROLLER_CONVERTER_H
#define CONTROLLER_CONVERTER_H

class ControllerConverter {
	private:
		std::string button_name;
	public:
		ControllerConverter(std::map<std::string, std::string> userMap);
	        std::map<std::string, std::string> user_map;
        	void convert(controller_t& input_controller, controller_t& output_controller);
};

#endif
