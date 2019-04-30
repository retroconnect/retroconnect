#include <string>
#include <ControllerConverter.h>
#include <NesController.h>
#include <XboxController.h>
#include <XboxToNesControllerConverter.h>

XboxToNesControllerConverter::XboxToNesControllerConverter() :AXIS_DEADZONE{10000}, TRIGGER_DEADZONE{100} {}


void XboxToNesControllerConverter::convert(controller_t& input_controller, controller_t& output_controller, std::string user_config_path)
{
            nes_controller_t& nes_controller = (nes_controller_t&) output_controller;
            xbox_controller_t& xbox_controller = (xbox_controller_t&) input_controller;


            //A, B, X, Y, START, SELECT are all straight forward mappings
            nes_controller.B = xbox_controller.A || xbox_controller.X;
            nes_controller.A = xbox_controller.B || xbox_controller.Y;
            nes_controller.START = xbox_controller.START;
            nes_controller.SELECT = xbox_controller.SELECT;


            //D-PAD direction determined by xbox's d-pad in conjunciton with LS axis'
            nes_controller.D_UP = xbox_controller.D_UP || (xbox_controller.LS_Y - MAX_AXIS_VALUE / 2) < -AXIS_DEADZONE;
            nes_controller.D_DOWN = xbox_controller.D_DOWN || (xbox_controller.LS_Y - MAX_AXIS_VALUE / 2) > AXIS_DEADZONE;
            nes_controller.D_RIGHT = xbox_controller.D_RIGHT || (xbox_controller.LS_X - MAX_AXIS_VALUE / 2) > AXIS_DEADZONE;
            nes_controller.D_LEFT = xbox_controller.D_LEFT || (xbox_controller.LS_X - MAX_AXIS_VALUE / 2) < -AXIS_DEADZONE;


            //Optional mappings
            //nes_controller.B = xbox_controller.LB || xbox_controller.LT > TRIGGER_DEADZONE;
            //nes_controller.A = xbox_controller.RB || xbox_controller.RT > TRIGGER_DEADZONE;
}
