Presence Switches
=================

These are our "presence switches" to denote how many people are in the
hackerspace at the moment.

The code is written for the Arduino Mega 2560 with the Ethernet shield.

Building
--------

Requirements (on ArchLinux)::

    # Needed for the arduino
    sudo pacman -S avrdude avr-gcc avr-binutils avr-libc
    yaourt -S arduino

    # Needed for the Makefile
    sudo pacman -S make perl-device-serialport perl-yaml

Clone and initialize submodules::

    git clone https://github.com/coredump-ch/presence-switches
    cd presence-switches
    git submodule init
    git submodule update

Build and upload::

    make upload

License
-------

MIT license, see `LICENSE.rst`.
