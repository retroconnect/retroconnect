class XboxToSnesControllerConverter: public ControllerConverter {
    private:
        int AXIS_DEADZONE = 100;
        int TRIGGER_DEADZONE = 100;

    public:
        snes_controller_t convert(controller_t input_controller, string user_config_path) {
            snes_controller_t converted = new snes_controller_t;

            //A, B, X, Y, START, SELECT are all straight forward mappings
            converted.A = input_controller.A;
            converted.B = input_controller.B;
            converted.X = input_controller.X;
            converted.Y = input_controller.Y;
            converted.START = input_controller.START
            converted.SELECT = input_controller.SELECT

            //D-PAD direction determined by xbox's d-pad in conjunciton with LS axis'
            converted.D_UP = input_controller.D_UP || input_controller.LS_Y > AXIS_DEADZONE;
            converted.D_DOWN = input_controller.D_DOWN || input_controller.LS_Y < -AXIS_DEADZONE;
            converted.D_RIGHT = input_controller.D_RIGHT || input_controller.LS_X > AXIS_DEADZONE;
            converted.D_LEFT = input_controller.D_LEFT || input_controller.LS_X < -AXIS_DEADZONE;

            //LB, RB, map to both the xboxs bumpers as well as the triggers
            converted.LB = input_controller.LB || input_controller.LT > TRIGGER_DEADZONE;
            converted.RB = input_controller.RB || input_controller.RT > TRIGGER_DEADZONE;

            return converted;
        }
};