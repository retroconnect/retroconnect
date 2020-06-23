#include <string>
#include <XboxController.h>
#include <ControllerConverter.h>

ControllerConverter::ControllerConverter(std::map<std::string, std::string> userMap) {
        user_map = userMap;
}

void ControllerConverter::convert(controller_t& input_controller, controller_t& output_controller)
{
 	for (std::map<std::string, int>::iterator it = input_controller->button_states.begin(); it != input_controller->button_states.end(); ++it) {
		it->second = input_controller->compileMappingsForButton(it->first, user_map);
	}

	//OLD	
	//snes_controller.button_states["B"] = compileButtonMappingsFor("B", xbox_controller);
}
