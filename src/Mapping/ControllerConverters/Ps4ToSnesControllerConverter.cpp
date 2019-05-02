#include <string>
#include <ControllerConverter.h>
#include <SnesController.h>
#include <Ps4Controller.h>
#include <Ps4ToSnesControllerConverter.h>

Ps4ToSnesControllerConverter::Ps4ToSnesControllerConverter() :AXIS_DEADZONE{50}, TRIGGER_DEADZONE{100} {}


void Ps4ToSnesControllerConverter::convert(controller_t& input_controller, controller_t& output_controller, std::map<std::string, std::string> user_map)
{
        snes_controller_t& snes_controller = (snes_controller_t&) output_controller;
        ps4_controller_t& ps4_controller = (ps4_controller_t&) input_controller;


        // //X, CIRCLE, TRIANGLE, SQUARE, START, SELECT
        // snes_controller.B = ps4_controller.X;
        // snes_controller.A = ps4_controller.CIRCLE;
        // snes_controller.Y = ps4_controller.SQUARE;
        // snes_controller.X = ps4_controller.TRIANGLE;
        // snes_controller.START = ps4_controller.START;
        // snes_controller.SELECT = ps4_controller.SELECT;


        // //D-PAD
        // snes_controller.D_UP = ps4_controller.D_UP || (ps4_controller.LS_Y - MAX_AXIS_VALUE / 2) < -AXIS_DEADZONE;
        // snes_controller.D_DOWN = ps4_controller.D_DOWN || (ps4_controller.LS_Y - MAX_AXIS_VALUE / 2) > AXIS_DEADZONE;
        // snes_controller.D_RIGHT= ps4_controller.D_RIGHT || (ps4_controller.LS_X - MAX_AXIS_VALUE / 2) > AXIS_DEADZONE;
        // snes_controller.D_LEFT = ps4_controller.D_LEFT || (ps4_controller.LS_X - MAX_AXIS_VALUE / 2) < -AXIS_DEADZONE;


        // // Triggers and Bumpers
        // snes_controller.LB = ps4_controller.L1 || ps4_controller.L2 > TRIGGER_DEADZONE;
        // snes_controller.RB = ps4_controller.R1 || ps4_controller.R2 > TRIGGER_DEADZONE;



        //user map will be reverse of whats in file: file goes input->output
        //but map goes output->input: what button on ps4 aligns with needed button for snes? snes->ps4 map
        //NOTE: Find a way to handle multiple buttons mapping to one. (i.e. triggers and bumpers on ps4 -> bumper on snes)

        //A, B, X, Y, START, SELECT
        snes_controller.button_states["B"] = compileButtonMappingsFor("B", user_map, ps4_controller);
        snes_controller.button_states["A"] = compileButtonMappingsFor("A", user_map, ps4_controller);
        snes_controller.button_states["X"] = compileButtonMappingsFor("X", user_map, ps4_controller);
        snes_controller.button_states["Y"] = compileButtonMappingsFor("Y", user_map, ps4_controller);
        snes_controller.button_states["START"] = compileButtonMappingsFor("START", user_map, ps4_controller);
        snes_controller.button_states["SELECT"] = compileButtonMappingsFor("SELECT", user_map, ps4_controller);

        //D-PAD
        snes_controller.button_states["D_UP"] = compileButtonMappingsFor("D_UP", user_map, ps4_controller);
        snes_controller.button_states["D_DOWN"] = compileButtonMappingsFor("D_DOWN", user_map, ps4_controller);
        snes_controller.button_states["D_RIGHT"] = compileButtonMappingsFor("D_RIGHT", user_map, ps4_controller);
        snes_controller.button_states["D_LEFT"] = compileButtonMappingsFor("D_LEFT", user_map, ps4_controller);

        //Triggers and bumpers
        snes_controller.button_states["LB"] = compileButtonMappingsFor("LB", user_map, ps4_controller);
        snes_controller.button_states["RB"] = compileButtonMappingsFor("RB", user_map, ps4_controller);
}

//user map will look like:
//      "RB": "R1 R2"
//      if both R1 and R2 on ps4 controller should trigger the snes's RB
//this function makes sure multiple mappings on input controller are taken into account when producing output controllers state
//also handles deadzones
int Ps4ToSnesControllerConverter::compileButtonMappingsFor(std::string b, std::map<std::string, std::string> user_map, ps4_controller_t ps4) {
        std::string ps4Buttons = user_map[b];

        //split user_map string by space
        size_t pos = 0;
        std::string token;

        while((pos = ps4Buttons.find(" ")) != std::string::npos) {
                token = ps4Buttons.substr(0, pos);

                int triggerValue, ps4Value;

                //handling for sticks is different for each direction, handling for triggers is unique, all other buttons captured by else
                if(token == "LS_LEFT") {
                        triggerValue = -std::stoi(user_map["STICK_DEADZONE"]);
                        ps4Value = ps4.button_states["LS_X"] - MAX_AXIS_VALUE / 2;
                } else if (token == "LS_RIGHT") {
                        triggerValue = std::stoi(user_map["STICK_DEADZONE"]);
                        ps4Value = ps4.button_states["LS_X"] - MAX_AXIS_VALUE / 2;
                } else if (token == "LS_UP") {
                        triggerValue = -std::stoi(user_map["STICK_DEADZONE"]);
                        ps4Value = ps4.button_states["LS_Y"] - MAX_AXIS_VALUE / 2;
                } else if (token == "LS_DOWN") {
                        triggerValue = std::stoi(user_map["STICK_DEADZONE"]);
                        ps4Value = ps4.button_states["LS_Y"] - MAX_AXIS_VALUE / 2;
                } else if (token == "RS_LEFT") {
                        triggerValue = -std::stoi(user_map["STICK_DEADZONE"]);
                        ps4Value = ps4.button_states["RS_X"] - MAX_AXIS_VALUE / 2;
                } else if (token == "RS_RIGHT") {
                        triggerValue = std::stoi(user_map["STICK_DEADZONE"]);
                        ps4Value = ps4.button_states["RS_X"] - MAX_AXIS_VALUE / 2;
                } else if (token == "RS_UP") {
                        triggerValue = -std::stoi(user_map["STICK_DEADZONE"]);
                        ps4Value = ps4.button_states["RS_Y"] - MAX_AXIS_VALUE / 2;
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
