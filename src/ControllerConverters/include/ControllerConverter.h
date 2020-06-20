#include <string>
#include <Controller.h>

#ifndef CONTROLLER_CONVERTER_H
#define CONTROLLER_CONVERTER_H

class ControllerConverter {
    public:
        std::map<std::string, std::string> user_map;
        virtual void convert(controller_t& input_controller, controller_t& output_controller) = 0;
};

#endif
