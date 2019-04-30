#include <string>
#include <ControllerConverter.h>
#include <NesController.h>
#include <Ps4Controller.h>

#ifndef PS4_TO_NES_CONTROLLER_CONVERTER_H
#define PS4_TO_NES_CONTROLLER_CONVERTER_H


class Ps4ToNesControllerConverter: public ControllerConverter {
    private:
        int AXIS_DEADZONE;
        int TRIGGER_DEADZONE;
    	static const int MAX_AXIS_VALUE = 255;

    public:
    	Ps4ToNesControllerConverter();
        void convert(controller_t& input_contrller, controller_t& output_controller, std::string user_config_path);
};

#endif
