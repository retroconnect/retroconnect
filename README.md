# RetroConnect
##### *One controller to rule them all*

### **Sections**

- [Overview](#project-summary)
- [Goals](#project-goals)
- [Usage](#usage)
- [File  Organization](#file-organization)
- [Useful Links](#useful-links)

## **Overview**
RetroConnect is a project that allows you to use wireless Bluetooth controllers on retro game consoles. The end goal is a single module that can be plugged into any console using a console-specific cable. Suddenly, the great pile of old controllers is reduced to a single favorite controller.   
    

## **Goals**

#### Completed Features:
- Supported input devices: 
  - Xbox One (XB1)
  - PlayStation 4 (PS4)
- Supported output devices:
  - Nintendo Entertainment System (NES)
  - Super Nintendo Entertainment System (SNES)
  - Sega Genesis (GEN)
  - Sega Master System (SMS)
  - Atari 2600 (2600)
  - Atari 7800 (7800)
- Analog sticks map to D-pads
- Button combos to change output console
- Custom button remapping via text files
- Less than 1 frame of input lag at 60 FPS

#### Future Features:

- Use ESP32 with Bluetooth instead of using a Raspberry Pi middleman (in progress)
- Manufactured console adapters with standard USB-C plug (SNES cables created)
- 3D printed case
- Support for input devices: Switch Joycons, DualShock 3 / SixAxis, Wii, generic controllers
- Support for output devices: Saturn, Dreamcast, Nintendo 64, PlayStation 1/2, GameCube, Xbox, and more
- A web app UI for customizing the controller mappings

## **Usage**

#### Requirements
- Teensy 3.2 or ESP32 (or other compatible microcontroller)
- Raspberry Pi Zero W (or similar)
- Console-specific adapters that connect to Teensy/ESP32 pin headers
- Wires to connect the Teensy/ESP32 to the Raspberry Pi

#### Microcontroller Setup
Locate the desired `.ino` file within the `arduino` directory and open it using the Arduino IDE and upload it to your microcontroller. See readme in the arduino directory for IDE configuration specific to each console.

#### Raspberry Pi Setup
1. Pull the git repo, compile with `make`.
2. Modify configs found in the `configs/` folder to suit your preferences
3. Run `sudo retroconnect`. Sudo is necessary on the very first run to disable the Raspberry Pi's Enhanced Retransmission Mode (ERTM) which breaks certain functionality of the Xbox One and PlayStation 4 controllers.

#### Wiring
1. Teensy 3.2 wiring is noted at the top of each Arduino file.
    
2. Wire the RX0 line from the Teensy to the TX line of the Raspberry Pi. Wire the TX0 line from the Teensy to the RX line of the Raspberry Pi. 

#### Execution
Execute the `retroconnect` program. If a compatible Bluetooth controller is not detected, it will automatically scan for supported devices in sync mode. Once a suitable controller is connected, it will display your button inputs in the terminal and button inputs will be converted and forwarded to the target console.

#### Button Combos
- HOME + South Button = SNES mode (default)
- HOME + East Button = NES mode
- HOME + West Button = Sega Genesis mode
- HOME + Left Button = Atari 2600 mode
- HOME + Right Button = Atari 7800 mode
- HOME + DPAD-UP = Sega Master System mode

## **File Organization**

The following outlines the basic structure of our ```root``` folder and git repository
```
root/
    arduino/
      <.ino files>
    configs/
      <.txt files>
    src/
      main.cpp
      converter.cpp
      include/
        Constants.h
        Converter.h
        ConverterFactory.h
      ControllerModels/
        Controller.cpp
        Input/
          XboxController.cpp
          ...
        Output/
          SnesController.cpp
          ...
```

### **```root/```**
The ```root/``` directory contains the following components:
- ```src/``` contains all Raspberry Pi source code.
  - ```ControllerModels/``` defines a controller's inputs/outputs and supported buttons and the abstract Controller class.
  - ```include/``` function definitions for converting one controller's model to another.
- ```configs/``` contains user-configurable mapping config files.
- ```arduino/``` contains the Arduino code to be flashed to a Teensy 3.2 or other MCU.

## **Credits**

- [SNES Signal Reference](https://gamefaqs.gamespot.com/snes/916396-super-nintendo/faqs/5395)
- [NES Signal Reference](https://wiki.nesdev.com/w/index.php/Standard_controller)
- [Genesis Signal Reference](https://www.raspberryfield.life/2019/03/25/sega-mega-drive-genesis-6-button-xyz-controller/)
- [Atari / SMS Signal Reference](http://wiki.icomp.de/w/index.php?title=DB9-Joystick&oldid=3915)
- Scholars-Mate, DerfJagged, BenThrasher5, BigScooter, and TheCoolMichael for initial project creation (XB1/PS4 to NES/SNES)
- Thanks to [Pavel Glushkov (pashutk)](http://github.com/pashutk) for help with ESP32 Bluetooth handling
- Thanks to [Ownasaurus](https://github.com/Ownasaurus) for massive help fixing Genesis 6 Button Mode on Teensy 


Like it? Give us a tip on PayPal! 

[![paypal](https://www.paypalobjects.com/en_US/i/btn/btn_donateCC_LG.gif)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=MBDA5CZQHXUU6)
