#include <string>
#include <ControllerConverter.h>
#include <NesController.h>
#include <XboxController.h>

#ifndef XBOX_TO_NES_CONTROLLER_CONVERTER_H
#define XBOX_TO_NES_CONTROLLER_CONVERTER_H

class XboxToNesControllerConverter: public ControllerConverter {
    private:
        int AXIS_DEADZONE;
        int TRIGGER_DEADZONE;
	static const int MAX_AXIS_VALUE = 65535;

    public:
	XboxToNesControllerConverter();
        void convert(controller_t& input_controller, controller_t& output_controller, std::string user_config_path);
};

#endif
