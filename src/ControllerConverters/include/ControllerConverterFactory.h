#include <typeinfo>
#include <string>
#include <Controller.h>
#include <ControllerConverter.h>
//#include <XboxToSnesControllerConverter.h>
//#include <XboxToNesControllerConverter.h>
//#include <XboxToGenControllerConverter.h>
//#include <XboxTo2600ControllerConverter.h>
//#include <XboxTo7800ControllerConverter.h>
//#include <XboxToSmsControllerConverter.h>
//#include <Ps4ToSnesControllerConverter.h>
//#include <Ps4ToNesControllerConverter.h>
//#include <Ps4ToGenControllerConverter.h>
//#include <Ps4To2600ControllerConverter.h>
//#include <Ps4To7800ControllerConverter.h>
//#include <Ps4ToSmsControllerConverter.h>

#ifndef CONTROLLER_CONVERTER_FACTORY_H
#define CONTROLLER_CONVERTER_FACTORY_H

class ControllerConverterFactory
{
	public:
		static ControllerConverter* createConverter(controller_t& input_controller, controller_t& output_controller)
	{
		
		std::map<std::string, std::string> userMap;

		//List of supported input/output combinations currently supported
		userMap = getMapFromConfigFile(CONTROLLERNAME[input_controller.type] + "_to_" + CONTROLLERNAME[output_controller.type] + ".txt");
		
		if(input_controller.type == XB1) {
			if (output_controller.type == SNES) {
				return new XboxToSnesControllerConverter(userMap);
			} else if (output_controller.type == NES) {
				return new XboxToNesControllerConverter(userMap);
			} else if (output_controller.type == GEN) {
				return new XboxToGenControllerConverter(userMap);
			} else if (output_controller.type == ATARI_2600) {
				return new XboxTo2600ControllerConverter(userMap);
			} else if (output_controller.type == ATARI_7800) {
				return new XboxTo7800ControllerConverter(userMap);
			} else if (output_controller.type == SMS) {
				return new XboxToSmsControllerConverter(userMap);
			}
		} else if(input_controller.type == PS4) {
			if (output_controller.type == SNES) {
				return new Ps4ToSnesControllerConverter(userMap);
			} else if (output_controller.type == NES) { 
				return new Ps4ToNesControllerConverter(userMap);
			} else if (output_controller.type == GEN) {
				return new Ps4ToGenControllerConverter(userMap);
			} else if (output_controller.type == ATARI_2600) {
				return new Ps4To2600ControllerConverter(userMap);
			} else if (output_controller.type == ATARI_7800) {
				return new Ps4To7800ControllerConverter(userMap);
			} else if (output_controller.type == SMS) {
				return new Ps4ToSmsControllerConverter(userMap);
			}
		}

		        
		printf("ERROR: Controller combination not supported in ControllerConverterFactory.h\n");
       		exit(EXIT_FAILURE);
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
					} else {
						//split line into left and right of =
						int equalIndex = line.find("=");
						std::string leftValue = line.substr(0, equalIndex);
						std::string rightValue = line.substr(equalIndex+1);

						//ignore null mappings
						if(rightValue != "NULL") {
							//special handling for int values, don't want a space on the end
							if(leftValue == "STICK_DEADZONE" || leftValue == "TRIGGER_DEADZONE") {
								cfgMap.insert({leftValue, rightValue});
							} else {
								//if right value exists in map already, add left value to it's value with a space in between (handles multiple mappings to one button)
								//otherwise we haven't read it yet and we need to make a new entry in the map
								if(cfgMap.find(rightValue) == cfgMap.end()) { //key not found
									cfgMap.insert({rightValue, leftValue + " "});
								} else { //key is found
									cfgMap.at(rightValue) = cfgMap.at(rightValue) + leftValue + " ";
								}
							}
						}
					}
				}
				cfgFile.close();
			} else {
				printf("ERROR: config file not found");
			}

			return cfgMap;
		}

};

#endif
