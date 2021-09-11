# LED-Pixel-Clock

<p align="center">
  <img src="https://github.com/florianL21/LED-ClockShelf/blob/master/doc/images/Animation.gif?raw=true" alt="Animation example"/>
</p>

This is the software of a variation of the LED clock from [DIY Machines](https://www.instructables.com/id/How-to-Build-a-Giant-Hidden-Shelf-Edge-Clock/)
A configuration which works on the original version of the clock is also part of the source code.

I decided to code it completely from scratch at I wanted to use a ESP32 instead of the Arduino nano and RTC that is used in the original project.
This enables some cool features like smartphone app control, OTA updates and fetching of the time using the internet.

Additionally this has full support for animations. By default I provide all needed animations for a 12h clock to morph one digit into another soothly.
Further animations can be easily added and existing animation can be adjusted to your liking.

The whole codebase is highly modular and configurable and can be tweaked exactly to your preferences.

Detailed documentation is available on [read the docs.](https://giant-led-clock.readthedocs.io/)

If you are interested in my variation of the design which uses a lot of wood instead of the 3D prints and is a bit bigger than the original you can find it on [thingiverse here](https://www.thingiverse.com/thing:4352352)

## Development Environment

I am using VScode with PlatformIO.
VSCode can be downloaded from [here.](https://code.visualstudio.com/)
And PlatformIO is an extension that can easily be installed from inside of VSCode.

Via the PlatformIO home the following libraries have to be installed:

* "Blynk" by Volodymyr Shymanskyy
* "FastLED" by Daniel Garcia
* "LinkedList" by Ivan Seidel

## Getting started

A quick list of things that have to be done to get this project up and running:

1. Make sure you have VS Code and the PlatformIO extension installed
2. Download the source either via the releases tab or by downloading or cloning this git repository
3. Go to lib/LED_clock and choose one of the library_*.json files and rename it to library.json
4. Check that you have all the above mentioned Platform IO libraries installed either system wide or in the project itself.
5. If you want to modify any of the configuration options you can do so by editing the files in `lib/LED_clock/Config/Setup/<chosen_version>`
6. Build and upload

If you want a more detailed walk through of the installation process take a look at the [setup wiki page.](https://giant-led-clock.readthedocs.io/en/latest/sites/Setup.html)

## Support

First of all thanks to DIY machines for the awesome idea!

Also thank you to the great people who developed the libraries that I am using for this project:

* Volodymyr Shymanskyy for the Blynk library
* Daniel Garcia for the FastLED library
* Ivan Seidel for his LinkedList implementation
* Andy Brown for the Easings library that I modified a bit to suit my needs better

If you would like to say thank you:
[![donate](https://img.shields.io/badge/send%20me%20a%20small%20gift-paypal-blue.svg?style=flat-square)](https://paypal.me/FlorianLaschober)
