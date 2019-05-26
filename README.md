# RetroConnect
##### *Giving modern gamers a link to the past*

### **Sections**

- [Project Summary](#project-summary)
- [Project Goals](#project-goals)
- [File  Organization](#file-organization)
- [Useful Links](#useful-links)

## **Project Summary**

* **The problem:**

    Retro game collectors worldwide often stumble across an issue with their collections: controllers. They take up a lot of space, the cords tangle up, and they often break down and need replacements which are usually pricey.

* **Our solution:**

    Our solution is a Bluetooth dongle which can wirelessly connect to a modern bluetooth controller of the user's choosing.The dongle can then be plugged in using a unique connector for each game console to adapt the Bluetooth dongle’s inputs to correct controller outputs for the target console. Suddenly, the great pile of old controllers is reduced to a single favorite controller.
    
    

## **Project Goals**

#### Completed Features:
- Supported input devices: Xbox One / PlayStation 4
- Supported output devices: Nintendo / Super Nintendo
- Uses Raspberry Pi Zero W and Teensy 3.2
- Less than 1 frame of input lag
- Electronic safety with proper voltage handling

#### Future Features:

- Single MCU instead of Raspberry Pi and Teensy
- Manufactured console adapters with standard USB-C plug
- 3D printed case
- Support for input devices: Switch Joycons, DualShock 3 / SixAxis, Wii, third party controllers
- Support for output devices: Genesis, Saturn, Dreamcast, Nintendo 64, PlayStation 1, Atari 2600, and more
- A web app UI for customizing the controller mappings


## **File Organization**

The following outlines the basic structure of our ```root``` folder and git repository
```
root/
    src/
      Bluetooth/
      Mapping/
        ControllerModels/
          Controller.cpp
          XboxController.cpp
          SnesController.cpp
          ...
        ControllerConverters/
          ControllerConverter.cpp
          ControllerConverterFactory.cpp
          XboxToSnesControllerConverter.cpp
          ...
      Backend/
        Backend.cpp
        SNESBackend.cpp
        ...
    build/
    configs/
    NES_SNES.ino
    Readme.md
    LICENSE
    .gitignore
```

### **```root/```**
The ```root/``` directory contains the following components:
- ```src/``` is meant to hold all our source code
- ```build/``` is meant to hold the compiled and built code ready to run retroconnect
- ```configs/``` is meant to hold user-configurable mapping config files
- ```configs/``` is the Arduino code to be flashed to a Teensy 3.2 or other MCU
- ```Readme.md``` is the file you are reading
- ```LICENSE``` is a text file describing our code's legal licensing

### **```src/```**
The ```src/``` directory is divided into the logical components that makeup the dataflow of our program
- ```Mapping/``` handles converting one controllers state to another's
    - ```ControllerModels/``` holds all the classes that define a controller's inputs and states, as well as the abstract Controller class that they all inherit from
    - ```ControllerConverters/``` holds all the classes that  have methods for converting one controller model to another, as well as the interface all controller converters will implement.
- ```Backend/``` holds all the classes that have methods for writing a controllers state to its corresponding console, as well as the interface all backends will implement.



## **Useful Links**

- [SNES Protocol Reference](https://gamefaqs.gamespot.com/snes/916396-super-nintendo/faqs/5395)
- [Controlling Arduino with Xbox Controller (guide + pics)](https://www.instructables.com/id/Controlling-Arduino-with-Gamepad/)


Like it? Give us a tip on PayPal! 

[![paypal](https://www.paypalobjects.com/en_US/i/btn/btn_donateCC_LG.gif)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=MBDA5CZQHXUU6)
