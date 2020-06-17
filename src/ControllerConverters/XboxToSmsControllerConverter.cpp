#include <string>
#include <ControllerConverter.h>
#include <SmsController.h>
#include <XboxController.h>
#include <XboxToSmsControllerConverter.h>

XboxToSmsControllerConverter::XboxToSmsControllerConverter(std::map<std::string, std::string> userMap) :AXIS_DEADZONE{10000}, TRIGGER_DEADZONE{100} {
        user_map = userMap;
}

void XboxToSmsControllerConverter::convert(controller_t& input_controller, controller_t& output_controller)
{
        sms_controller_t& sms_controller = (sms_controller_t&) output_controller;
        xbox_controller_t& xbox_controller = (xbox_controller_t&) input_controller;

        //1, 2
        sms_controller.button_states["1"] = compileButtonMappingsFor("1", xbox_controller);
	sms_controller.button_states["2"] = compileButtonMappingsFor("2", xbox_controller);
	
        //D-PAD, Pause (mod)
        sms_controller.button_states["D_UP"] = compileButtonMappingsFor("D_UP", xbox_controller) || compileButtonMappingsFor("PAUSE", xbox_controller);
        sms_controller.button_states["D_DOWN"] = compileButtonMappingsFor("D_DOWN", xbox_controller) || compileButtonMappingsFor("PAUSE", xbox_controller);
        sms_controller.button_states["D_RIGHT"] = compileButtonMappingsFor("D_RIGHT", xbox_controller) || compileButtonMappingsFor("PAUSE", xbox_controller);
        sms_controller.button_states["D_LEFT"] = compileButtonMappingsFor("D_LEFT", xbox_controller) || compileButtonMappingsFor("PAUSE", xbox_controller);

}

int XboxToSmsControllerConverter::compileButtonMappingsFor(std::string b, xbox_controller_t xbox) {
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
