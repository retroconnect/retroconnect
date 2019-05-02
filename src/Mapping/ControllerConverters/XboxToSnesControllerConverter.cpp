#include <string>
#include <ControllerConverter.h>
#include <SnesController.h>
#include <XboxController.h>
#include <XboxToSnesControllerConverter.h>

XboxToSnesControllerConverter::XboxToSnesControllerConverter() :AXIS_DEADZONE{10000}, TRIGGER_DEADZONE{100} {}

void XboxToSnesControllerConverter::convert(controller_t& input_controller, controller_t& output_controller, std::map<std::string, std::string> user_map)
{
        snes_controller_t& snes_controller = (snes_controller_t&) output_controller;
        xbox_controller_t& xbox_controller = (xbox_controller_t&) input_controller;

        //A, B, X, Y, START, SELECT
        snes_controller.button_states["B"] = compileButtonMappingsFor("B", user_map, xbox_controller);
        snes_controller.button_states["A"] = compileButtonMappingsFor("A", user_map, xbox_controller);
        snes_controller.button_states["X"] = compileButtonMappingsFor("X", user_map, xbox_controller);
        snes_controller.button_states["Y"] = compileButtonMappingsFor("Y", user_map, xbox_controller);
        snes_controller.button_states["START"] = compileButtonMappingsFor("START", user_map, xbox_controller);
        snes_controller.button_states["SELECT"] = compileButtonMappingsFor("SELECT", user_map, xbox_controller);

        //D-PAD
        snes_controller.button_states["D_UP"] = compileButtonMappingsFor("D_UP", user_map, xbox_controller);
        snes_controller.button_states["D_DOWN"] = compileButtonMappingsFor("D_DOWN", user_map, xbox_controller);
        snes_controller.button_states["D_RIGHT"] = compileButtonMappingsFor("D_RIGHT", user_map, xbox_controller);
        snes_controller.button_states["D_LEFT"] = compileButtonMappingsFor("D_LEFT", user_map, xbox_controller);

        //Triggers and bumpers
        snes_controller.button_states["LB"] = compileButtonMappingsFor("LB", user_map, xbox_controller);
        snes_controller.button_states["RB"] = compileButtonMappingsFor("RB", user_map, xbox_controller);
}

//user map will look like:
//      "RB": "R1 R2"
//      if both R1 and R2 on xbox controller should trigger the snes's RB
//this function makes sure multiple mappings on input controller are taken into account when producing output controllers state
//also handles deadzones
int XboxToSnesControllerConverter::compileButtonMappingsFor(std::string b, std::map<std::string, std::string> user_map, xbox_controller_t xbox) {
        std::string xboxButtons = user_map[b];

        //split user_map string by space
        size_t pos = 0;
        std::string token;

        while((pos = xboxButtons.find(" ")) != std::string::npos) {
                token = xboxButtons.substr(0, pos);

                int triggerValue, xboxValue;

                //handling for sticks is different for each direction, handling for triggers is unique, all other buttons captured by else
                if(token == "LS_LEFT") {
                        triggerValue = -std::stoi(user_map["STICK_DEADZONE"]);
                        xboxValue = xbox.button_states["LS_X"] - MAX_AXIS_VALUE / 2;
                } else if (token == "LS_RIGHT") {
                        triggerValue = std::stoi(user_map["STICK_DEADZONE"]);
                        xboxValue = xbox.button_states["LS_X"] - MAX_AXIS_VALUE / 2;
                } else if (token == "LS_UP") {
                        triggerValue = -std::stoi(user_map["STICK_DEADZONE"]);
                        xboxValue = xbox.button_states["LS_Y"] - MAX_AXIS_VALUE / 2;
                } else if (token == "LS_DOWN") {
                        triggerValue = std::stoi(user_map["STICK_DEADZONE"]);
                        xboxValue = xbox.button_states["LS_Y"] - MAX_AXIS_VALUE / 2;
                } else if (token == "RS_LEFT") {
                        triggerValue = -std::stoi(user_map["STICK_DEADZONE"]);
                        xboxValue = xbox.button_states["RS_X"] - MAX_AXIS_VALUE / 2;
                } else if (token == "RS_RIGHT") {
                        triggerValue = std::stoi(user_map["STICK_DEADZONE"]);
                        xboxValue = xbox.button_states["RS_X"] - MAX_AXIS_VALUE / 2;
                } else if (token == "RS_UP") {
                        triggerValue = -std::stoi(user_map["STICK_DEADZONE"]);
                        xboxValue = xbox.button_states["RS_Y"] - MAX_AXIS_VALUE / 2;
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