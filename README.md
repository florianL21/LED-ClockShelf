# LED-ClockShelf

This is the software of a variation of the LED clock from [here.](https://www.instructables.com/id/How-to-Build-a-Giant-Hidden-Shelf-Edge-Clock/)
I have a seperate branch with a ready to use configuration which works on the original version of this clock out of the box [here](https://github.com/florianL21/LED-ClockShelf/tree/diy-machines-version)

I decided to code it completley from scratch at I wanted to use a ESP32 instead of the Arduino nano and RTC that is used in the original project.
This enables some cool features like smartphone app control, OTA updates and fetching of the time using the internet.

Additionally this has full support for animations. By default I provide all needed anmiations for a 12h clock to morph one digit into another soothly.
Further animations can be easily added and existing animation can be adjusted to your liking.

The whole codebase is highly modular and configurable and can be tweaked exactly to your liking.

Detailed documentation is avaliable on the [Wiki.](https://github.com/florianL21/LED-ClockShelf/wiki)

If you are interested in my variation of the design which uses a lot of wood instad of the 3D prints and is a bit bigger than the original you can find it on [thingiverse here](https://www.thingiverse.com/thing:4352352)

# Development Environment:

I am using VScode with PlatformIO.
VSCode can be downloaded from [here.](https://code.visualstudio.com/)
And PlatformIO is an extention that can easily be installed from inside of VSCode.

Via the platformio home the following libraries have to be installed:
 * "Blynk" by Volodymyr Shymanskyy
 * "FastLED" by Daniel Garcia
 * "LinkedList" by Ivan Seidel

# Important files for configuration:
Files that are important for configuration (sorted by importance):
 1. At the top of /include/Configuration.h -> Contains almost all important settings, like WIFI config, pin configurations etc.
 2. /src/DisplayManager/DisplayConfiguration.cpp -> Configuration of which leds belong to which segments and whioch segments belong to which display, the order of the segments and their animation directions *It is really important to get this one right!*
 3. /src/SevenSegment/SegmentTransitions.cpp -> Configuring the animations between the digits
 4. /src/DisplayManager/Animations.cpp -> configuration of anmimations like the loading animation
