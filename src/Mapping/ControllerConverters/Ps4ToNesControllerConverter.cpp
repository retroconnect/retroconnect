#include <string>
#include <ControllerConverter.h>
#include <NesController.h>
#include <Ps4Controller.h>
#include <Ps4ToNesControllerConverter.h>

Ps4ToNesControllerConverter::Ps4ToNesControllerConverter() :AXIS_DEADZONE{50}, TRIGGER_DEADZONE{100} {}


// void Ps4ToNesControllerConverter::convert(controller_t& input_controller, controller_t& output_controller, std::string user_config_path)
// {
//         nes_controller_t& nes_controller = (nes_controller_t&) output_controller;
//         ps4_controller_t& ps4_controller = (ps4_controller_t&) input_controller;


//         //X, CIRCLE, TRIANGLE, SQUARE, START, SELECT
//         nes_controller.B = ps4_controller.X || ps4_controller.SQUARE;
//         nes_controller.A = ps4_controller.CIRCLE || ps4_controller.TRIANGLE;
//         nes_controller.START = ps4_controller.START;
//         nes_controller.SELECT = ps4_controller.SELECT;


//         //D-PAD
//         nes_controller.D_UP = ps4_controller.D_UP || (ps4_controller.LS_Y - MAX_AXIS_VALUE / 2) < -AXIS_DEADZONE;
//         nes_controller.D_DOWN = ps4_controller.D_DOWN || (ps4_controller.LS_Y - MAX_AXIS_VALUE / 2) > AXIS_DEADZONE;
//         nes_controller.D_RIGHT= ps4_controller.D_RIGHT || (ps4_controller.LS_X - MAX_AXIS_VALUE / 2) > AXIS_DEADZONE;
//         nes_controller.D_LEFT = ps4_controller.D_LEFT || (ps4_controller.LS_X - MAX_AXIS_VALUE / 2) < -AXIS_DEADZONE;


// 	//Optional mappings
// 	//nes_controller.B = ps4_controller.L1 || ps4_controller.L2 > TRIGGER_DEADZONE;
// 	//nes_controller.A = ps4_controller.R1 || ps4_controller.R2 > TRIGGER_DEADZONE;
// }

void Ps4ToNesControllerConverter::convert(controller_t& input_controller, controller_t& output_controller, std::map<std::string, std::string> user_map)
{
        nes_controller_t& nes_controller = (nes_controller_t&) output_controller;
        ps4_controller_t& ps4_controller = (ps4_controller_t&) input_controller;

        //A, B, X, Y, START, SELECT
        nes_controller.button_states["B"] = compileButtonMappingsFor("B", user_map, ps4_controller);
        nes_controller.button_states["A"] = compileButtonMappingsFor("A", user_map, ps4_controller);
        nes_controller.button_states["START"] = compileButtonMappingsFor("START", user_map, ps4_controller);
        nes_controller.button_states["SELECT"] = compileButtonMappingsFor("SELECT", user_map, ps4_controller);

        //D-PAD
        nes_controller.button_states["D_UP"] = compileButtonMappingsFor("D_UP", user_map, ps4_controller);
        nes_controller.button_states["D_DOWN"] = compileButtonMappingsFor("D_DOWN", user_map, ps4_controller);
        nes_controller.button_states["D_RIGHT"] = compileButtonMappingsFor("D_RIGHT", user_map, ps4_controller);
        nes_controller.button_states["D_LEFT"] = compileButtonMappingsFor("D_LEFT", user_map, ps4_controller);
}

//user map will look like:
//      "RB": "R1 R2"
//      if both R1 and R2 on ps4 controller should trigger the snes's RB
//this function makes sure multiple mappings on input controller are taken into account when producing output controllers state
//also handles deadzones
int Ps4ToNesControllerConverter::compileButtonMappingsFor(std::string b, std::map<std::string, std::string> user_map, ps4_controller_t ps4) {
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
