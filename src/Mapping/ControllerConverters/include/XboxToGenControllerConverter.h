#include <string>
#include <ControllerConverter.h>
#include <GenController.h>
#include <XboxController.h>

#ifndef XBOX_TO_GEN_CONTROLLER_CONVERTER_H
#define XBOX_TO_GEN_CONTROLLER_CONVERTER_H


class XboxToGenControllerConverter: public ControllerConverter {
    private:
        int AXIS_DEADZONE;
        int TRIGGER_DEADZONE;
	static const int MAX_AXIS_VALUE = 65535;
        std::map<std::string, std::string> user_map;
        int compileButtonMappingsFor(std::string b, xbox_controller_t xbox);

    public:
	XboxToGenControllerConverter(std::map<std::string, std::string> userMap);
        void convert(controller_t& input_controller, controller_t& output_controller);
};

#endif