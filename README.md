# DataStrategyGame

This is a data-driven strategy game engine, creating a lua API for games to be built on top of it.  Example games are included.

## Running the program

The program is invoked with two command line arguments, the first is the directory the game is in, the second is the map or save file to load. Two examples are 
    dataGame /games/chessClone normalChessBoard.txt
    dataGame /games/tactics deathmatch2.txt

## Building the program

Under linux, the program can be built with the included makefile, by simply running make.  It has the following build dependencies (under Ubuntu):  

    g++
    liblua5.1-0-dev
    libsdl2-dev
    libsdl2-image-dev
    libglew-dev

## Creating a game
### JSON
This is where the raw data is defined. At the top level you must have a gridSize value (in pixels), luaFiles (a list of lua code that is used), terrainData, abilityData, and unitData

Also in the top level you may define images for action icons, movement icons, health points, and some values to adjust the displayed locations of these items. Look at the tactics.json file for an example.

terrainData is a list terrain values containing the following data:

id: a single character identifier

Image: an image file for the terrain. It will automatically be resized to fit the grid.

abilityData defines the abilities that a unit may have. The lua functions are names of functions defined in the loaded lua files, explained in more detail in the "lua" section below.

Required:

id: This is a string which identifies the ability  
Image: an image to show the ability on the bottom of the screen  
selection: true if the user must select a square for the ability to be used, false if the ability should activate immediately upon being clicked (while available)  
availableFn: lua function which returns if the ability can be activated  
actionFn: lua function  
allowedLocationsFn: Required only if selection is true. lua function which returns a list of x and y values which are allowed target locations for the ability  

Optional:

turnStartFn: lua function run at the start of the unit's owner's turn  
turnEndFn: lua function run at the end of the unit's owner's turn  
unitCreatedFn: lua function run right after the unit is created  
unitDiedFn: lua function run as the unit is dying  

### lua
Documentation for lua in general is available at https://www.lua.org/manual/5.3/ 

Errors from the lua code will be printed on the console, so make sure to pay attention to it.

All lua functions used directly by the abilities must take the following form:
availableFn(unitID) returns a boolean  
actionFn(unitID) returns nothing, used in non-selection abilities  
actionFn(unitID, x, y) returns nothing, used in selection abilities  
allowedLocationsFn(unitID) returns a table/array of values, with odd values as y and even values as x (note that lua arrays start at 1), used in selection abilities  
all other functions take a unitID and return nothing.

x, y, and unitID are integers  
abilityID, terrainID, and unitTypeID are strings.  
The following functions are exposed to the lua code:  
boolean isAlive(unitID)  
integer getOwner(unitID) (returns 0 or 1)  
integer getValue(unitID, string)  
setValue(unitID, string, integer)  
addValue(unitID, string, integer)  

integers x, y getPos(unitID)  
setPos(unitID, x, y)  

addAbility(unitID, abilityID)  
boolean hasAbility(unitID, abilityID)  
removeAbility(unitID, abilityID)  

unitID createUnit(unitTypeID, x, y)  
unitID unitAt(x, y)  

boolean withinBounds(x, y)  
list of unitIDs getAllUnits()  

terrainID getTerrain(x, y)  

To kill a unit, use setValue to set its "hp" value to 0. Also exposed is the special unitID value NO_UNIT.


### maps
The first line is width, height, then the json file for the game

Then is the unit map, which consists of all the unitTypeID values on the map. Use a space to represent no unit.

This is followed by a blank line, then the terrain map. The terrain map is similar to the unit map but uses the terrainID values instead, and there is no 'blank' terrain allowed.

## Credits
Chess images by jurgenwesterhof (adapted from work of Cburnett)