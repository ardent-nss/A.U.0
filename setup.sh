#!/bin/bash
#setup.sh: clones and sets up RPi Pico SDK

# I think you could use your own SDK version from elsewhere on your disk, but
# use this if that doesn't work out.

git submodule update --init --recursive
cd pico-sdk
cmake .
make -j$(nproc --all) # Use multithreading for max speed
