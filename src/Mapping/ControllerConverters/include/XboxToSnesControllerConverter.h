#include <string>
#include <ControllerConverter.h>
#include <SnesController.h>
#include <XboxController.h>

#ifndef XBOX_TO_SNES_CONTROLLER_CONVERTER_H
#define XBOX_TO_SNES_CONTROLLER_CONVERTER_H

class XboxToSnesControllerConverter: public ControllerConverter {
    private:
        int AXIS_DEADZONE;
        int TRIGGER_DEADZONE;
	static const int MAX_AXIS_VALUE = 65535;

    public:
	XboxToSnesControllerConverter();
        bool convert(controller_t& input_controller, controller_t& output_controller, std::string user_config_path);
};

#endif
