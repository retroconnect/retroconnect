#include <typeinfo>
#include <string>
#include <Controller.h>
#include <ControllerConverter.h>
#include <XboxToSnesControllerConverter.h>
//#include <Ps4ToSnesControllerConverter.h>

#ifndef CONTROLLER_CONVERTER_FACTORY_H
#define CONTROLLER_CONVERTER_FACTORY_H

class ControllerConverterFactory
{
	public:
		static ControllerConverter* createConverter(controller_t& input_controller, controller_t& output_controller)
	{
		
		//list of supported input/output combinations currently supported
		if(input_controller.type == XB1) {
			if (output_controller.type == SNES) { //XBOX -> SNES
				return new XboxToSnesControllerConverter();
			} 
		}
	
		if(input_controller.type == PS4) {
			if (output_controller.type == SNES) { //PS4 -> SNES
				return new Ps4ToSnesControllerConverter();
			}
		}
		        
		printf("ERROR: Controller combination not supported\n");
       		exit(EXIT_FAILURE);
	}

	private:
		ControllerConverterFactory() {};

};

#endif
