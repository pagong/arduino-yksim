examples
========


yksEEinit#
----------

Change the AES-128 key, the public and private ids and the static password to your personal likings (and keep them private).
Upload the code to your Arduino Leonardo to initialize the EEPROM. This needs to be done only once.


yksTouch1
---------

Upload the code into your Arduino Leonardo and stick an ordinary paper clip into pin D7.
This will turn your Leonardo into an USB keyboard that emits keyboard scan codes whenever you touch the paper clip.
Every time you touch the paper clip for a short time, a unique new Yubikey compatible OTP will be 'typed' by the Leonardo.
If you press the paper clip for a longer time, the static, secret password will by 'typed' by the Leonardo.


yksLCD1
-------

Upload this code into your Leonardo and stack a "LCD + keypad" shield onto the Arduino.
Besides working as an USB keyboard the display allows for an offline mode of operation.
This might be useful with systems that don't have any usable USB ports ...

