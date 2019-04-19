#include <typeinfo>
#include <string>
#include <Controller.h>
#include <ControllerConverter.h>
#include <XboxToSnesControllerConverter.h>

#ifndef CONTROLLER_CONVERTER_FACTORY_H
#define CONTROLLER_CONVERTER_FACTORY_H

class ControllerConverterFactory
{
public:
	static ControllerConverter* createConverter(controller_t& input_controller, controller_t& output_controller)
{
//    std::string input_type = typeid(input_controller).name();
//    std::string output_type = typeid(output_controller).name();

    //list of supported input/output combinations currently supported
    if(1){//input_type == "XboxController" && output_type == "SnesController") { //XBOX -> SNES
        return new XboxToSnesControllerConverter();
    } else {
        printf("error: no conversion logic implemented\n");
        return NULL;
    }
}

private:
	ControllerConverterFactory() {};

};

#endif
