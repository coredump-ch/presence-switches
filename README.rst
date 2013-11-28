Presence Switches
=================

These are our *presence switches* to denote how many people are in the
hackerspace at the moment.

The code is written for the Arduino Mega 2560 with the Ethernet shield.

Building
--------

Requirements (on ArchLinux)::

    # Needed for the arduino
    $ sudo pacman -S avrdude avr-gcc avr-binutils avr-libc
    $ yaourt -S arduino

    # Needed for the Makefile
    $ sudo pacman -S make perl-device-serialport perl-yaml

Clone and initialize submodules::

    $ git clone https://github.com/coredump-ch/presence-switches
    $ cd presence-switches
    $ git submodule init
    $ git submodule update

Adjust the IP in ``src/main.ino``::

    IPAddress ip(192, 168, 2, 222)

Build and upload::

    $ make upload

Running
-------

The display should reflect the switches automatically.

To get the current status via network, send a HTTP request to
``http://[ip]:1337/`` and you will get back a JSON object::

    $ curl -i http://192.168.2.222:1337/
    HTTP/1.1 200 OK
    Content-Type: application/json
    Connection: close

    {"open": true, "people": 3}

Parts
-----

- Arduino Mega 2560
- Arduino Ethernet Shield
- Catalex TM1637 4-Digit Display Module
  (http://dx.com/p/0-36-led-4-digit-display-module-for-arduino-black-blue-works-with-official-arduino-boards-254978)
- Sparkfun PCF8575 I2C Breakout Board
  (http://www.play-zone.ch/de/sparkfun-pcf8775c-i2c-io-expander-breakout.html)
- Sparkfun Toggle Switch (8x)
  (http://www.play-zone.ch/de/sparkfun-raketen-schalter.html)
- 10kΩ Resistors (8x)

License
-------

MIT license, see ``LICENSE.rst``.
