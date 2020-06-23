#include <string>
//#include <XboxController.h>
#include <ControllerConverter.h>

ControllerConverter::ControllerConverter(std::map<std::string, std::string> userMap) {
        user_map = userMap;
}

void ControllerConverter::convert(controller_t& input_controller, controller_t& output_controller)
{
 	for (std::map<std::string, int>::iterator it = (input_controller.button_states).begin(); it != (input_controller.button_states).end(); ++it) {
		//SEGFAULT CITY
		printf("Compiling: %s\n", (it->first).c_str());
		printf("OUTPUT: %d\n", output_controller.button_states.at(it->first));
		//output_controller.button_states.at(it->first) = input_controller.compileMappingsForButton(it->first, user_map);
	}

	printf("FINISHED CONTROLLER CONVERTER\n\n");
	//OLD	
	//snes_controller.button_states["B"] = compileButtonMappingsFor("B", xbox_controller);
}
