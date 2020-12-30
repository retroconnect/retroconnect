#include <string>
#include <fstream>
#include <Controller.h>
#include <Converter.h>

#ifndef CONVERTER_FACTORY_H
#define CONVERTER_FACTORY_H

class ConverterFactory
{
	public:
		static Converter* create_converter(controller_t& input_controller, controller_t& output_controller) {	
			std::map<std::string, std::string> user_map;
			
			try {
				std::string input_controller_name = CONTROLLERNAME[input_controller.type];
			}
			catch (int e) {
				printf("ERROR: Unknown input controller\n");
				exit(0);
			}

			try {
				std::string output_controller_name = CONTROLLERNAME[output_controller.type];
			}
			catch (int e) {
				printf("ERROR: Unknown output controller\n");
				exit(0);
			}
		
			user_map = get_map_from_config_file(CONTROLLERNAME[input_controller.type] + "_to_" + CONTROLLERNAME[output_controller.type] + ".txt");
			return new Converter(user_map);		
		}

	private:
		ConverterFactory() {};

		static std::map<std::string, std::string> get_map_from_config_file(std::string config_filename) {
			std::map<std::string, std::string> config_map = {};
			std::string line;
			bool marker_found = false;
			config_filename = "./configs/" + config_filename;
			std::ifstream config_file (config_filename);

			if(config_file.is_open()) {
				while(getline(config_file, line)) {
					if(!marker_found) {
						//this is a special marker that signifies the start of the actual config text.
						//until we find this line, we're scanning through the instructions at the top, which should be ignored in processing
						if(line == "*================================*") {
							marker_found = true;
						}
					} 
					else {
						//split line into left and right of =
						int equal_index = line.find("=");
						std::string left_value = line.substr(0, equal_index);
						std::string right_value = line.substr(equal_index+1);

						//ignore null mappings
						if(right_value != "NULL") {
							//if right value exists in map already, add left value to its value (for multiple mappings to one button)
							//otherwise it is a new entry in the map
							if(config_map.find(right_value) == config_map.end()) { //key not found
								config_map.insert({right_value, left_value + " "});
							} 
							else { //key is found
								config_map.at(right_value) = config_map.at(right_value) + left_value + " ";
							}
						}
					}
				}
				config_file.close();
			} 
			else {
				printf("ERROR: Config file %s not found!", config_filename.c_str());
			}

			return config_map;
		}
};

#endif
