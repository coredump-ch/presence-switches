Presence Switches
=================

These are our "presence switches" to denote how many people are in the
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

License
-------

MIT license, see `LICENSE.rst`.
