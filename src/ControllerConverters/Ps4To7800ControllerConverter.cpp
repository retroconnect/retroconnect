#include <string>
#include <ControllerConverter.h>
#include <Atari7800Controller.h>
#include <Ps4Controller.h>
#include <Ps4To7800ControllerConverter.h>

Ps4To7800ControllerConverter::Ps4To7800ControllerConverter(std::map<std::string, std::string> userMap) :AXIS_DEADZONE{50}, TRIGGER_DEADZONE{100} {
        user_map = userMap;
}


void Ps4To7800ControllerConverter::convert(controller_t& input_controller, controller_t& output_controller)
{
        atari_7800_controller_t& atari_7800_controller = (atari_7800_controller_t&) output_controller;
        ps4_controller_t& ps4_controller = (ps4_controller_t&) input_controller;

        //BUTTON
        atari_7800_controller.button_states["BUTTON"] = compileButtonMappingsFor("BUTTON", ps4_controller);
	atari_7800_controller.button_states["BUTTON_LEFT"] = compileButtonMappingsFor("BUTTON", ps4_controller);
	atari_7800_controller.button_states["BUTTON_RIGHT"] = compileButtonMappingsFor("BUTTON_RIGHT", ps4_controller);

        //D-PAD
        atari_7800_controller.button_states["D_UP"] = compileButtonMappingsFor("D_UP", ps4_controller);
        atari_7800_controller.button_states["D_DOWN"] = compileButtonMappingsFor("D_DOWN", ps4_controller);
        atari_7800_controller.button_states["D_RIGHT"] = compileButtonMappingsFor("D_RIGHT", ps4_controller);
        atari_7800_controller.button_states["D_LEFT"] = compileButtonMappingsFor("D_LEFT", ps4_controller);

}

int Ps4To7800ControllerConverter::compileButtonMappingsFor(std::string b, ps4_controller_t ps4) {
        std::string ps4Buttons = user_map[b];

        //split user_map string by space
        size_t pos = 0;
        std::string token;

        while((pos = ps4Buttons.find(" ")) != std::string::npos) {
                token = ps4Buttons.substr(0, pos);

                int triggerValue, ps4Value;

                //handling for sticks is different for each direction, handling for triggers is unique, all other buttons captured by else
                if(token == "LS_LEFT") {
                        triggerValue = std::stoi(user_map["STICK_DEADZONE"]);
                        ps4Value = -(ps4.button_states["LS_X"] - MAX_AXIS_VALUE / 2);
                } else if (token == "LS_RIGHT") {
                        triggerValue = std::stoi(user_map["STICK_DEADZONE"]);
                        ps4Value = ps4.button_states["LS_X"] - MAX_AXIS_VALUE / 2;
                } else if (token == "LS_UP") {
                        triggerValue = std::stoi(user_map["STICK_DEADZONE"]);
                        ps4Value = -(ps4.button_states["LS_Y"] - MAX_AXIS_VALUE / 2);
                } else if (token == "LS_DOWN") {
                        triggerValue = std::stoi(user_map["STICK_DEADZONE"]);
                        ps4Value = ps4.button_states["LS_Y"] - MAX_AXIS_VALUE / 2;
                } else if (token == "RS_LEFT") {
                        triggerValue = std::stoi(user_map["STICK_DEADZONE"]);
                        ps4Value = -(ps4.button_states["RS_X"] - MAX_AXIS_VALUE / 2);
                } else if (token == "RS_RIGHT") {
                        triggerValue = std::stoi(user_map["STICK_DEADZONE"]);
                        ps4Value = ps4.button_states["RS_X"] - MAX_AXIS_VALUE / 2;
                } else if (token == "RS_UP") {
                        triggerValue = std::stoi(user_map["STICK_DEADZONE"]);
                        ps4Value = -(ps4.button_states["RS_Y"] - MAX_AXIS_VALUE / 2);
                } else if (token == "RS_DOWN") {
                        triggerValue = std::stoi(user_map["STICK_DEADZONE"]);
                        ps4Value = ps4.button_states["RS_Y"] - MAX_AXIS_VALUE / 2;
                } else if (token == "L2" || token == "R2") {
                        triggerValue = std::stoi(user_map["TRIGGER_DEADZONE"]);
                        ps4Value = ps4.button_states[token];
                } else {
                        triggerValue = 1;
                        ps4Value = ps4.button_states[token];
                }

                if(ps4Value >= triggerValue) {
                        //if any of the buttons are pressed, we're ready to return. 
                        //note, this assumes all buttons on output controller are not analog
                        return 1;
                }

                ps4Buttons.erase(0, pos + 1);
        }

        return 0;
}
