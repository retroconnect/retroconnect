#include <string>
#include <ControllerConverter.h>
#include <SnesController.h>
#include <XboxController.h>
#include <XboxToSnesControllerConverter.h>

XboxToSnesControllerConverter::XboxToSnesControllerConverter() :AXIS_DEADZONE{10000}, TRIGGER_DEADZONE{100} {}


void XboxToSnesControllerConverter::convert(controller_t& input_controller, controller_t& output_controller, std::string user_config_path)
{
            snes_controller_t& snes_controller = (snes_controller_t&) output_controller;
            xbox_controller_t& xbox_controller = (xbox_controller_t&) input_controller;


            //A, B, X, Y, START, SELECT are all straight forward mappings
            snes_controller.B = xbox_controller.A;
            snes_controller.A = xbox_controller.B;
            snes_controller.Y = xbox_controller.X;
            snes_controller.X = xbox_controller.Y;
            snes_controller.START = xbox_controller.START;
            snes_controller.SELECT = xbox_controller.SELECT;


            //D-PAD direction determined by xbox's d-pad in conjunciton with LS axis'
            snes_controller.D_UP = xbox_controller.D_UP || (xbox_controller.LS_Y - MAX_AXIS_VALUE / 2) < -AXIS_DEADZONE;
            snes_controller.D_DOWN = xbox_controller.D_DOWN || (xbox_controller.LS_Y - MAX_AXIS_VALUE / 2) > AXIS_DEADZONE;
            snes_controller.D_RIGHT = xbox_controller.D_RIGHT || (xbox_controller.LS_X - MAX_AXIS_VALUE / 2) > AXIS_DEADZONE;
            snes_controller.D_LEFT = xbox_controller.D_LEFT || (xbox_controller.LS_X - MAX_AXIS_VALUE / 2) < -AXIS_DEADZONE;


            //LB, RB, map to both the xboxs bumpers as well as the triggers
            snes_controller.LB = xbox_controller.LB || xbox_controller.LT > TRIGGER_DEADZONE;
            snes_controller.RB = xbox_controller.RB || xbox_controller.RT > TRIGGER_DEADZONE;
}
