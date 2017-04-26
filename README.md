# DataStrategyGame

This is a data-driven strategy game engine, creating a lua API for games to be built on top of it.  Example games are included.

## Running the program

The program is invoked with two command line arguments, the first is the directory the game is in, the second is the map or save file to load.

## Building the program

Under linux, the program can be built with the included makefile, by simply running make.  It has the following build dependencies (under Ubuntu):  

    g++
    liblua5.1-0-dev
    libsdl2-dev
    libsdl2-image-dev
    libglew-dev
