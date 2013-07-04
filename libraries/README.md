libraries
=========


YkCore
------

The core cryptographic functions for the Yubikey simulator have been taken
from open source code written by [Yubico](http://www.yubico.com/).
YkSim is using the [libyubikey](https://github.com/Yubico/yubico-c) and
[yubikey-personalization](https://github.com/Yubico/yubico-c) libraries.


SoftTimer
------

This is a clever new timer library for the Arduino which can be downloaded
from [here](http://code.google.com/p/arduino-softtimer/).
I've only included those parts that are needed by the Yubikey simulator.


Yksim
------

These are the glue functions that make the Yubikey simulator work.
They're used by the example files which can be found in the examples/YKS directory.
They've been written and released with a GNU license by [pagong](email://pa90n9@gmail.com).


LiquidCrystal
-------------

These are just a few convenience header files which abstract the differences in
'key codes' of those "LCD + keypad" shields that I could test myself.

