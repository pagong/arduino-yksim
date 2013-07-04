arduino-yksim
=============

Simulate Yubikey with Arduino Leonardo


How-to use
----------

Merge the libraries and examples directories with your arduino-1.0.x installation.

Start the Ardunio GUI (e.g. arduino-1.0.4/arduino) and open one of the yksEEinit files (in File --> Examples --> YKS).
Change the AES-128 key, the public and private ids and the static password to your personal likings (and keep them private).
Upload the code to your Arduino Leonardo. This needs to be done only once.

Then open the file yksTouch1 (also in File --> Examples --> YKS) and upload this code to your Leonardo.
Then stick an ordinary paper clip into pin D7 and connect the Leonardo to an USB port of your computer.
This will turn your Leonardo into an USB keyboard that emits keyboard scan codes whenever you touch the paper clip.
Every time you touch the paper clip for a short time, a unique new Yubikey compatible OTP will be 'typed' by the Leonardo.
If you press the paper clip for a longer time, the static, secret password will by 'typed' by the Leonardo.


Advanced usage
--------------

If you're owning one of the "LCD + keypad" shields for the Arduino you can also try the example in yksLCD1:
Whenever the Enter key is pressed a new code is generated (Yubico-OTP or the static password)
and 'typed' by the Leonardo (acting as an USB keyboard).
The Down and Up buttons let you scroll thru the codes on the 2x16 liquid crystal display.
The Right and Left buttons select the mode of operation.


Have Fun !
----------


Caveat
------

I'm using this Arduino code with Linux systems only. 
I've no idea whether this stuff works with Macintosh or Windows systems.
