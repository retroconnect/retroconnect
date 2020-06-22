#include <string>
#include <Controller.h>

#ifndef CONTROLLER_CONVERTER_H
#define CONTROLLER_CONVERTER_H

class ControllerConverter {
	private:
		int AXIS_DEADZONE = 10000;
		int TRIGGER_DEADZONE = 100;
		static const int MAX_AXIS_VALUE = 65535; //255 for PS4	
	public:
		ControllerConverter(std::map<std::string, std::string> userMap);
	        std::map<std::string, std::string> user_map;
        	void convert(controller_t& input_controller, controller_t& output_controller) = 0;
};

#endif
