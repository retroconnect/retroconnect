#include <string>
#include <Controller.h>

#ifndef CONTROLLER_CONVERTER_H
#define CONTROLLER_CONVERTER_H

class ControllerConverter {
    public:
        virtual void convert(controller_t& input_controller, controller_t& output_controller) = 0;
};

#endif
