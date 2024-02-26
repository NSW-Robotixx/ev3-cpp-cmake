# Ev3 Pathfinder Project

## Why and What?

The purpose of this directory is to make a Lego Ev3 pathfind over a arbituary field of lines and solve tasks in the Progress. This code is supposed to be used for the FLL after it is finished, or at least near finished.

## Compiling?

CMake on a linux machine, WSL also supported. The `arm-linux-gnueabi-gcc` packet has to be installed for the programm to cross compile. It will statically link all reqired libraries. 
Otherwise the executable will not work on the Ev3. The linux machine has to have a working internet connection to download g-test. This is used for the normal unit-tests. 
These can easily be invoked by using `ctest`
