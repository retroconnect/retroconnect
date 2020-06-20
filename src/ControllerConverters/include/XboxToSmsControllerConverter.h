#include <string>
#include <ControllerConverter.h>
#include <SmsController.h>
#include <XboxController.h>

#ifndef XBOX_TO_SMS_CONTROLLER_CONVERTER_H
#define XBOX_TO_SMS_CONTROLLER_CONVERTER_H


class XboxToSmsControllerConverter: public ControllerConverter {
    private:
        int AXIS_DEADZONE;
        int TRIGGER_DEADZONE;
	static const int MAX_AXIS_VALUE = 65535;
        int compileButtonMappingsFor(std::string b, xbox_controller_t xbox);

    public:
	XboxToSmsControllerConverter(std::map<std::string, std::string> userMap);
        void convert(controller_t& input_controller, controller_t& output_controller);
};

#endif
