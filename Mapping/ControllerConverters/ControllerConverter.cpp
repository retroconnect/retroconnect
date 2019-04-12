class ControllerConverter {
    public:
        virtual controller_t convert(controller_t input_controller, string user_config_path) = 0;
};