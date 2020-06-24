#include <string>
#include <Controller.h>

#ifndef CONVERTER_H
#define CONVERTER_H

class Converter {
	private:
		std::string button_name;
	public:
		Converter(std::map<std::string, std::string> user_map);
	        std::map<std::string, std::string> user_map;
        	void convert(controller_t& input_controller, controller_t& output_controller);
};

#endif
