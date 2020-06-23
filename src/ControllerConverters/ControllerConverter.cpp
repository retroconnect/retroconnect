#include <string>
#include <ControllerConverter.h>

ControllerConverter::ControllerConverter(std::map<std::string, std::string> userMap) {
        user_map = userMap;
}

void ControllerConverter::convert(controller_t& input_controller, controller_t& output_controller)
{
 	for (std::map<std::string, std::string>::iterator it = (user_map).begin(); it != (user_map).end(); ++it) {
		std::string button_name = it->first;
		if (button_name == "STICK_DEADZONE" || button_name == "TRIGGER_DEADZONE") {continue;}
		output_controller.button_states.at(button_name) = input_controller.compileMappingsForButton(button_name, user_map);
	}
}
