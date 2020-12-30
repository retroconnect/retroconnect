set(srcs "esp_hid_host_main.cpp"
         "esp_hid_gap.c"
         "converter.cpp"
         "retroconnect.cpp")
         
set(include_dirs "."
                 "./include/"
                 "./ControllerModels/"
                 "./ControllerModels/Input"
                 "./ControllerModels/Output")

idf_component_register(SRCS "${srcs}"
                       INCLUDE_DIRS "${include_dirs}"
                       REQUIRES esp_hid)
