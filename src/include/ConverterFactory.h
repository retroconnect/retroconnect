#include <typeinfo>
#include <string>
#include <Controller.h>
#include <Converter.h>

#ifndef CONTROLLER_CONVERTER_FACTORY_H
#define CONTROLLER_CONVERTER_FACTORY_H

class ControllerConverterFactory
{
	public:
		static ControllerConverter* createConverter(controller_t& input_controller, controller_t& output_controller) {	
			std::map<std::string, std::string> userMap;
			

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
		
			userMap = getMapFromConfigFile(CONTROLLERNAME[input_controller.type] + "_to_" + CONTROLLERNAME[output_controller.type] + ".txt");
			return new ControllerConverter(userMap);		
		}

	private:
		ControllerConverterFactory() {};

		static std::map<std::string, std::string> getMapFromConfigFile(std::string configFileName) {
			//create empty map
			std::map<std::string, std::string> cfgMap = {};
			string line;
			bool passedInstructions = false;
			configFileName = "./configs/" + configFileName;
			ifstream cfgFile (configFileName);

			if(cfgFile.is_open()) {
				while(getline(cfgFile, line)) {
					if(!passedInstructions) {
						//this is a special marker that signifies the start of the actual config text.
						//until we find this line, we're scanning through the instructions at the top, which should be ignored in processing
						if(line == "*================================*") {
							passedInstructions = true;
						}
					} 
					else {
						//split line into left and right of =
						int equalIndex = line.find("=");
						std::string leftValue = line.substr(0, equalIndex);
						std::string rightValue = line.substr(equalIndex+1);

						//ignore null mappings
						if(rightValue != "NULL") {
							//if right value exists in map already, add left value to its value (for multiple mappings to one button)
							//otherwise it is a new entry in the map
							if(cfgMap.find(rightValue) == cfgMap.end()) { //key not found
								cfgMap.insert({rightValue, leftValue + " "});
							} 
							else { //key is found
								cfgMap.at(rightValue) = cfgMap.at(rightValue) + leftValue + " ";
							}
						}
					}
				}
				cfgFile.close();
			} 
			else {
				printf("ERROR: Config file %s not found!", configFileName.c_str());
			}

			return cfgMap;
		}
};

#endif
