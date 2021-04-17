.. _Home:

# Getting started

This is the software of a variation of the LED clock from [here.](https://www.instructables.com/id/How-to-Build-a-Giant-Hidden-Shelf-Edge-Clock/)
You can find the code ready for download [here](https://github.com/florianL21/LED-ClockShelf/releases/tag/v1.0.0)
You can also find a pre configured version that should work pretty much out of the box on the original version from DIY-Machines [in this release](https://github.com/florianL21/LED-ClockShelf/releases/tag/1.0.0). Thanks to DIY-Machines for testing my code on the one and only original.

I decided to code it completely from scratch as I wanted to use an ESP32 instead of the Arduino Nano and RTC that is used in the original project.
This enables some cool features like smartphone app control, OTA updates and fetching of the time using the internet.

Additionally this has full support for animations. By default I provide all needed animations for a 12h clock to morph one digit into another smoothly.
Further animations can be easily added and existing animation can be adjusted to your liking.

The whole codebase is highly modular and configurable and can be tweaked exactly to your liking.

1. :doc:`Wiring <Wiring>`
2. :doc:`Install the development environment and all needed libraries <Setup>`

## Starting points for Version 2.0:
Take a look at the [latest version of this documentation](https://giant-led-clock.readthedocs.io/en/latest/)

## Starting points for Version 1.0 of this project:
3. :doc:`Configure the code to fit your needs <Basic-config>`
4. :doc:`Understanding, modifying and crating Animations <Advanced-config>`