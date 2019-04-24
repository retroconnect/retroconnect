#include <string>
#include <ControllerConverter.h>
#include <SnesController.h>
#include <Ps4Controller.h>
#include <Ps4ToSnesControllerConverter.h>



Ps4ToSnesControllerConverter::Ps4ToSnesControllerConverter() :AXIS_DEADZONE{50}, TRIGGER_DEADZONE{100} {}


bool Ps4ToSnesControllerConverter::convert(controller_t& input_controller, controller_t& output_controller, std::string user_config_path)
{
        snes_controller_t& snes_controller = (snes_controller_t&) output_controller;
        ps4_controller_t& ps4_controller = (ps4_controller_t&) input_controller;


        //X, CIRCLE, TRIANGLE, SQUARE, START, SELECT
        snes_controller.B = ps4_controller.X;
        snes_controller.A = ps4_controller.CIRCLE;
        snes_controller.Y = ps4_controller.SQUARE;
        snes_controller.X = ps4_controller.TRIANGLE;
        snes_controller.START = ps4_controller.START;
        snes_controller.SELECT = ps4_controller.SELECT;

        //D-PAD

        snes_controller.D_UP = ps4_controller.D_UP || (ps4_controller.LS_X - MAX_AXIS_VALUE / 2) < -AXIS_DEADZONE;
        snes_controller.D_DOWN = ps4_controller.D_DOWN || (ps4_controller.LS_X - MAX_AXIS_VALUE / 2) > AXIS_DEADZONE;
        snes_controller.D_RIGHT= ps4_controller.D_RIGHT || (ps4_controller.LS_Y - MAX_AXIS_VALUE / 2) > AXIS_DEADZONE;
        snes_controller.D_LEFT = ps4_controller.D_LEFT || (ps4_controller.LS_Y - MAX_AXIS_VALUE / 2) < -AXIS_DEADZONE;


        // Triggers and Bumpers

        snes_controller.LB = ps4_controller.L1 || ps4_controller.L2 > TRIGGER_DEADZONE;
        snes_controller.RB = ps4_controller.R1 || ps4_controller.R2 > TRIGGER_DEADZONE;

}
