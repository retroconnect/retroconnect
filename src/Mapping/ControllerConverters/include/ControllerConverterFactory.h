#include <typeinfo>
#include <string>
#include <Controller.h>
#include <ControllerConverter.h>
#include <XboxToSnesControllerConverter.h>
#include <XboxToNesControllerConverter.h>
#include <Ps4ToSnesControllerConverter.h>
#include <Ps4ToNesControllerConverter.h>

#ifndef CONTROLLER_CONVERTER_FACTORY_H
#define CONTROLLER_CONVERTER_FACTORY_H

class ControllerConverterFactory
{
	public:
		static ControllerConverter* createConverter(controller_t& input_controller, controller_t& output_controller)
	{
		
		std::map<std::string, std::string> userMap;

		//List of supported input/output combinations currently supported
		if(input_controller.type == XB1) {
			if (output_controller.type == SNES) {
				userMap = getMapFromConfigFile(".\\Config\\XboxToSnesConfig.txt");
				return new XboxToSnesControllerConverter(userMap);
			} else if (output_controller.type == NES) {
				userMap = getMapFromConfigFile(".\\Config\\XboxToNesConfig.txt");
				return new XboxToNesControllerConverter(userMap);
			}
		} else if(input_controller.type == PS4) {
			if (output_controller.type == SNES) {
				userMap = getMapFromConfigFile(".\\Config\\Ps4ToSnesConfig.txt");
				return new Ps4ToSnesControllerConverter(userMap);
			} else if (output_controller.type == NES) { 
				userMap = getMapFromConfigFile(".\\Config\\Ps4ToNesConfig.txt");
				return new Ps4ToNesControllerConverter(userMap);
			}
		}

		        
		printf("ERROR: Controller combination not supported\n");
       		exit(EXIT_FAILURE);
	}

	private:
		ControllerConverterFactory() {};

		static std::map<std::string, std::string> getMapFromConfigFile(std::string configFileName) {
			// return {
			// 	{"A", "B "},
			// 	{"B", "A "},
			// 	{"X", "X "},
			// 	{"Y", "Y "},
			// 	{"START", "START "},
			// 	{"SELECT", "SELECT "},
			// 	{"LB", "LB LT "},
			// 	{"RB", "RB RT "},
			// 	{"D_LEFT", "D_LEFT LS_LEFT "},
			// 	{"D_RIGHT", "D_RIGHT LS_RIGHT "},
			// 	{"D_UP", "D_UP LS_UP "},
			// 	{"D_DOWN", "D_DOWN LS_DOWN "},
			// 	{"TRIGGER_DEADZONE", "100"},
			// 	{"STICK_DEADZONE", "10000"}
			// 	//map built on this config: (xbox to snes)
			// 	// A=A
			// 	// B=B
			// 	// X=X
			// 	// Y=Y
			// 	// START=START
			// 	// SELECT=SELECT
			// 	// HOME=NULL
			// 	// LS_PRESS=NULL
			// 	// RS_PRESS=NULL
			// 	// LB=LB
			// 	// RB=RB
			// 	// LT=LB
			// 	// RT=RB
			// 	// TRIGGER_DEADZONE=100
			// 	// D_LEFT=D_LEFT
			// 	// D_RIGHT=D_RIGHT
			// 	// D_DOWN=D_DOWN
			// 	// D_UP=D_UP
			// 	// LS_LEFT=D_LEFT
			// 	// LS_RIGHT=D_RIGHT
			// 	// LS_UP=D_UP
			// 	// LS_DOWN=D_DOWN
			// 	// RS_LEFT=NULL
			// 	// RS_RIGHT=NULL
			// 	// RS_UP=NULL
			// 	// RS_DOWN=NULL
			// 	// STICK_DEADZONE=10000
			// };

			//create empty map
			std::map<std::string, std::string> cfgMap = {};
			string line;
			bool passedInstructions = false;
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
						std::string rightValue = line.substr(equalIndex+1, line.length);

						//ignore null mappings
						if(rightValue != "NULL") {
							//special handling for int values, don't want a space on the end
							if(leftValue == "STICK_DEADZONE" || leftValue == "TRIGGER_DEADZONE") {
								cfgMap.insert({rightValue, leftValue});
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
