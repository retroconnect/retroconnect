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
        int compileButtonMappingsFor(std::string b, std::map<std::string, std::string> user_map, xbox_controller_t xbox);

    public:
	    XboxToSnesControllerConverter();
        void convert(controller_t& input_controller, controller_t& output_controller, std::map<std::string, std::string> user_map);
};

#endif
