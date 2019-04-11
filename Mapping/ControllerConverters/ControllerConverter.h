#include "../ControllerModels/Controller.h"
#include "../ControllerModels/XboxController.h"
#include "../ControllerModels/SnesController.h"

class ControllerConverter {
    public:
        virtual contoller_t convert(contoller_t input_controller, string user_config_path);
};