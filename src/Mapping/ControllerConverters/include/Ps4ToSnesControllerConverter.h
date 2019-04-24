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
    static const int MAX_AXIS_VALUE = 65535;

    public:
    Ps4ToSnesControllerConverter();
        bool convert(controller_t& input_contrller, controller_t& output_controller, std::string user_config_path);



};

#endif
