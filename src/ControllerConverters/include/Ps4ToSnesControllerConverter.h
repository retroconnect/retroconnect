#include <string>
#include <ControllerConverter.h>
#include <SnesController.h>
#include <Ps4Controller.h>

#ifndef PS4_TO_SNES_CONTROLLER_CONVERTER_H
#define PS4_TO_SNES_CONTROLLER_CONVERTER_H


class Ps4ToSnesControllerConverter: public ControllerConverter {
    private:
        int AXIS_DEADZONE;
        int TRIGGER_DEADZONE;
    	static const int MAX_AXIS_VALUE = 255;
        std::map<std::string, std::string> user_map;
        int compileButtonMappingsFor(std::string b, ps4_controller_t ps4);

    public:
    	Ps4ToSnesControllerConverter(std::map<std::string, std::string> userMap);
        void convert(controller_t& input_controller, controller_t& output_controller);
};

#endif