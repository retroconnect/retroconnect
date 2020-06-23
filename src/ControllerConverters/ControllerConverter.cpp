#include <string>
#include <ControllerConverter.h>

std::string button_name = "";

ControllerConverter::ControllerConverter(std::map<std::string, std::string> userMap) {
        user_map = userMap;
}

void ControllerConverter::convert(controller_t& input_controller, controller_t& output_controller)
{
 	for (std::map<std::string, std::string>::iterator it = (user_map).begin(); it != (user_map).end(); ++it) {
		button_name = it->first;
		output_controller.button_states.at(button_name) = input_controller.compileMappingsForButton(button_name, user_map);
	}
}
