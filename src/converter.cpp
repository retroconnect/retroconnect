#include <string>
#include <Converter.h>

std::string button_name = "";

Converter::Converter(std::map<std::string, std::string> passed_user_map) {
        user_map = passed_user_map;
}

void Converter::convert(controller_t& input_controller, controller_t& output_controller)
{
	try {
 		for (std::map<std::string, std::string>::iterator it = (user_map).begin(); it != (user_map).end(); ++it) {
			button_name = it->first;
			output_controller.button_states.at(button_name) = input_controller.get_mapped_button_state(button_name, user_map);
		}
	}
	catch (const std::out_of_range& e) {
		printf("Bad config file: %s_to_%s.txt!\n", CONTROLLERNAME[input_controller.type].c_str(), CONTROLLERNAME[output_controller.type].c_str());
		exit(0);
	}
}
