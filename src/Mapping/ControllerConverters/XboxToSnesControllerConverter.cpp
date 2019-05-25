#include <string>
#include <ControllerConverter.h>
#include <SnesController.h>
#include <XboxController.h>
#include <XboxToSnesControllerConverter.h>

XboxToSnesControllerConverter::XboxToSnesControllerConverter(std::map<std::string, std::string> userMap) :AXIS_DEADZONE{10000}, TRIGGER_DEADZONE{100} {
        user_map = userMap;
}

void XboxToSnesControllerConverter::convert(controller_t& input_controller, controller_t& output_controller)
{
        snes_controller_t& snes_controller = (snes_controller_t&) output_controller;
        xbox_controller_t& xbox_controller = (xbox_controller_t&) input_controller;

        //A, B, X, Y, START, SELECT
        snes_controller.button_states["B"] = compileButtonMappingsFor("B", xbox_controller);
        snes_controller.button_states["A"] = compileButtonMappingsFor("A", xbox_controller);
        snes_controller.button_states["X"] = compileButtonMappingsFor("X", xbox_controller);
        snes_controller.button_states["Y"] = compileButtonMappingsFor("Y", xbox_controller);
        snes_controller.button_states["START"] = compileButtonMappingsFor("START", xbox_controller);
        snes_controller.button_states["SELECT"] = compileButtonMappingsFor("SELECT", xbox_controller);

        //D-PAD
        snes_controller.button_states["D_UP"] = compileButtonMappingsFor("D_UP", xbox_controller);
        snes_controller.button_states["D_DOWN"] = compileButtonMappingsFor("D_DOWN", xbox_controller);
        snes_controller.button_states["D_RIGHT"] = compileButtonMappingsFor("D_RIGHT", xbox_controller);
        snes_controller.button_states["D_LEFT"] = compileButtonMappingsFor("D_LEFT", xbox_controller);

        //Triggers and bumpers
        snes_controller.button_states["LB"] = compileButtonMappingsFor("LB", xbox_controller);
        snes_controller.button_states["RB"] = compileButtonMappingsFor("RB", xbox_controller);
}

int XboxToSnesControllerConverter::compileButtonMappingsFor(std::string b, xbox_controller_t xbox) {
        std::string xboxButtons = user_map[b];

        //split user_map string by space
        size_t pos = 0;
        std::string token;

        while((pos = xboxButtons.find(" ")) != std::string::npos) {
                token = xboxButtons.substr(0, pos);

                int triggerValue, xboxValue;

                //handling for sticks is different for each direction, handling for triggers is unique, all other buttons captured by else
                if(token == "LS_LEFT") {
                        triggerValue = std::stoi(user_map["STICK_DEADZONE"]);
                        xboxValue = -(xbox.button_states["LS_X"] - MAX_AXIS_VALUE / 2);
                } else if (token == "LS_RIGHT") {
                        triggerValue = std::stoi(user_map["STICK_DEADZONE"]);
                        xboxValue = xbox.button_states["LS_X"] - MAX_AXIS_VALUE / 2;
                } else if (token == "LS_UP") {
                        triggerValue = std::stoi(user_map["STICK_DEADZONE"]);
                        xboxValue = -(xbox.button_states["LS_Y"] - MAX_AXIS_VALUE / 2);
                } else if (token == "LS_DOWN") {
                        triggerValue = std::stoi(user_map["STICK_DEADZONE"]);
                        xboxValue = xbox.button_states["LS_Y"] - MAX_AXIS_VALUE / 2;
                } else if (token == "RS_LEFT") {
                        triggerValue = std::stoi(user_map["STICK_DEADZONE"]);
                        xboxValue = -(xbox.button_states["RS_X"] - MAX_AXIS_VALUE / 2);
                } else if (token == "RS_RIGHT") {
                        triggerValue = std::stoi(user_map["STICK_DEADZONE"]);
                        xboxValue = xbox.button_states["RS_X"] - MAX_AXIS_VALUE / 2;
                } else if (token == "RS_UP") {
                        triggerValue = std::stoi(user_map["STICK_DEADZONE"]);
                        xboxValue = -(xbox.button_states["RS_Y"] - MAX_AXIS_VALUE / 2);
                } else if (token == "RS_DOWN") {
                        triggerValue = std::stoi(user_map["STICK_DEADZONE"]);
                        xboxValue = xbox.button_states["RS_Y"] - MAX_AXIS_VALUE / 2;
                } else if (token == "LT" || token == "RT") {
                        triggerValue = std::stoi(user_map["TRIGGER_DEADZONE"]);
                        xboxValue = xbox.button_states[token];
                } else {
                        triggerValue = 1;
                        xboxValue = xbox.button_states[token];
                }

                if(xboxValue >= triggerValue) {
                        //if any of the buttons are pressed, we're ready to return. 
                        //note, this assumes all buttons on output controller are not analog
                        return 1;
                }

                xboxButtons.erase(0, pos + 1);
        }

        return 0;
}
