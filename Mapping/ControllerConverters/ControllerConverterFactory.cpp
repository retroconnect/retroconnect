//#include "XboxToSnesControllerConverter.cpp"

class ControllerConverterFactory
{
 public:
  static ControllerConverter* createConverter(controller_t input_controller, controller_t output_controller) {
    string input_type = typeid(input_controller).name();
    string output_type = typeid(output_controller).name();

    //list of supported input/output combinations currently supported
    if(input_type == "XboxController" && output_type == "SnesController") { //XBOX -> SNES
        return new XboxToSnesControllerConverter();
    } else {
        //print("error: no conversion logic implemented for the controller combination: input: %s, output: %s\n", input_type, output_type)
    }
  }

 private:
  // Disallow creating an instance of this object
  ControllerConverterFactory() {}
};