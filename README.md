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

    The proposed solution is a single Bluetooth dongle which can wirelessly connect to a modern bluetooth controller of the user's choosing.The dongle can then be plugged in using a unique connector for each game console to adapt the Bluetooth dongle’s outputs to correct controller outputs for the target console. Suddenly, the great pile of old controllers is reduced to a single favorite controller. (With a dongle of course)


    

## **Project Goals**

#### Main goals:
- Ability to sync Bluetooth controller with device
- Use a second generation XBox One controller to control a SNES
- Minimal input latency (< 16.6 ms estimated)
- Electronic safety with proper voltage handling

#### Stretch goals:

- 3D printed case
- Out-of-the-box support additional target consoles
- Out-of-the-box support for additional wireless controllers
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
    Readme.md
    LICENSE
    .gitignore
```

### **```root/```**
The ```root/``` directory contains the following components:
- ```src/``` is meant to hold all our source code
- ```build/``` is meant to hold the compiled and built code ready to run retroconnect
- ```Readme.md``` is the file you are reading
- ```LICENSE``` is a text file describing our code's legal licensing

### **```src/```**
The ```src/``` directory is divided into the logical components that makeup the dataflow of our program
- ```Bluetooth``` covers connecting and pairing
- ```Mapping/``` handles converting one controllers state to another's
    - ```ControllerModels/``` holds all the classes that define a controller's inputs and states, as well as the abstract Controller class that they all inherit from
    - ```ControllerConverters/``` holds all the classes that  have methods for converting one controller model to another, as well as the interface all controller converters will implement.
- ```Backend/``` holds all the classes that have methods for writing a controllers state to its corresponding console, as well as the interface all backends will implement.
## **Useful Links**

- [Trello Board](https://trello.com/b/ROS3Fkvu/retroconnect)
- [Full Project Documentation (Drive)](https://docs.google.com/document/d/1mEBRCkgICx4aQAnAozwCzarPqw2R9PdMzJhonUkf57s/edit)
- [SNES Protocol Reference](https://gamefaqs.gamespot.com/snes/916396-super-nintendo/faqs/5395)
- [Controlling Arduino with Xbox Controller (guide + pics)](https://www.instructables.com/id/Controlling-Arduino-with-Gamepad/)
