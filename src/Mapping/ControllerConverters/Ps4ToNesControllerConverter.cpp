#include <string>
#include <ControllerConverter.h>
#include <NesController.h>
#include <Ps4Controller.h>
#include <Ps4ToNesControllerConverter.h>

Ps4ToNesControllerConverter::Ps4ToNesControllerConverter() :AXIS_DEADZONE{50}, TRIGGER_DEADZONE{100} {}


void Ps4ToNesControllerConverter::convert(controller_t& input_controller, controller_t& output_controller, std::string user_config_path)
{
        nes_controller_t& nes_controller = (nes_controller_t&) output_controller;
        ps4_controller_t& ps4_controller = (ps4_controller_t&) input_controller;


        //X, CIRCLE, TRIANGLE, SQUARE, START, SELECT
        nes_controller.B = ps4_controller.X || ps4_controller.SQUARE;
        nes_controller.A = ps4_controller.CIRCLE || ps4_controller.TRIANGLE;
        nes_controller.START = ps4_controller.START;
        nes_controller.SELECT = ps4_controller.SELECT;


        //D-PAD
        nes_controller.D_UP = ps4_controller.D_UP || (ps4_controller.LS_Y - MAX_AXIS_VALUE / 2) < -AXIS_DEADZONE;
        nes_controller.D_DOWN = ps4_controller.D_DOWN || (ps4_controller.LS_Y - MAX_AXIS_VALUE / 2) > AXIS_DEADZONE;
        nes_controller.D_RIGHT= ps4_controller.D_RIGHT || (ps4_controller.LS_X - MAX_AXIS_VALUE / 2) > AXIS_DEADZONE;
        nes_controller.D_LEFT = ps4_controller.D_LEFT || (ps4_controller.LS_X - MAX_AXIS_VALUE / 2) < -AXIS_DEADZONE;


	//Optional mappings
	//nes_controller.B = ps4_controller.L1 || ps4_controller.L2 > TRIGGER_DEADZONE;
	//nes_controller.A = ps4_controller.R1 || ps4_controller.R2 > TRIGGER_DEADZONE;
}
