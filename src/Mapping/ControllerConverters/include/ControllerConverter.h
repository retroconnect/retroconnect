#include <string>
#include <Controller.h>

#ifndef CONTROLLER_CONVERTER_H
#define CONTROLLER_CONVERTER_H

class ControllerConverter {
    public:
        virtual bool convert(controller_t& input_controller, controller_t& output_controller, std::string user_config_path) = 0;
};

#endif
