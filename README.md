# LED-Pixel-Clock
<p align="center">
  <img src="https://github.com/florianL21/LED-ClockShelf/blob/master/doc/images/Animation.gif?raw=true" alt="Animation example"/>
</p>

------------------

ATTENTION: You are looking at version 2.0 of the project. Documentation for this version is still a Work In Progress!
For Version 1.0 take a look at [this snapshot branch](https://github.com/florianL21/LED-ClockShelf/tree/Snapshot-v1)
You wil also find the original version of the documentation there.

Please note that updating from version 1 to version 2 via OTA update might not work correctly.

------------------

This is the software of a variation of the LED clock from [DIY Machines](https://www.instructables.com/id/How-to-Build-a-Giant-Hidden-Shelf-Edge-Clock/)
A configuration which works on the original version of the clock is also part of the source code.

I decided to code it completely from scratch at I wanted to use a ESP32 instead of the Arduino nano and RTC that is used in the original project.
This enables some cool features like smartphone app control, OTA updates and fetching of the time using the internet.

Additionally this has full support for animations. By default I provide all needed animations for a 12h clock to morph one digit into another soothly.
Further animations can be easily added and existing animation can be adjusted to your liking.

The whole codebase is highly modular and configurable and can be tweaked exactly to your preferences.

Detailed documentation is available on [read the docs.](https://giant-led-clock.readthedocs.io/)

If you are interested in my variation of the design which uses a lot of wood instead of the 3D prints and is a bit bigger than the original you can find it on [thingiverse here](https://www.thingiverse.com/thing:4352352)

## Development Environment:

I am using VScode with PlatformIO.
VSCode can be downloaded from [here.](https://code.visualstudio.com/)
And PlatformIO is an extension that can easily be installed from inside of VSCode.

Via the PlatformIO home the following libraries have to be installed:
 * "Blynk" by Volodymyr Shymanskyy
 * "FastLED" by Daniel Garcia
 * "LinkedList" by Ivan Seidel

## Getting started
To get started with setting everything up take a look at the [Wiki.](https://giant-led-clock.readthedocs.io/)