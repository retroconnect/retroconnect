#include "ControllerConverter.h"

class ControllerConverterFactory
{
 public:
  static ControllerConverter createConverter(controller_t input_controller, controller_t output_controller);
};