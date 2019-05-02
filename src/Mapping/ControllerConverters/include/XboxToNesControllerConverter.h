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
        int compileButtonMappingsFor(std::string b, std::map<std::string, std::string> user_map, xbox_controller_t xbox);

    public:
	XboxToNesControllerConverter();
        void convert(controller_t& input_controller, controller_t& output_controller, std::map<std::string, std::string> user_map);
};

#endif
