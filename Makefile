CC = g++
FLAGS = -Wall -O3 -std=c++11 -I /usr/include/lua5.1 -I include/ -I /usr/include/SDL2 -I /usr/include/GL -D_GNU_SOURCE=1 -D_REENTRANT 
LFLAGS = -lSDL2 -lSDL2_image -lSDL2_net -lGL -llua5.1-c++
HEADERS = AbilityType.hpp GameDynamicData.hpp Game.hpp  SaveFile.hpp Unit.hpp UnitType.hpp include/json.hpp GlobalIncludes.hpp UI.hpp GlobalIncludes.hpp LuaManager.hpp Window.hpp Image.hpp
OBJ = AbilityType.o Game.o GameDynamicData.o SaveFile.o Unit.o UnitType.o main.o Map.o UI.o LuaManager.o Window.o Image.o

%.o : %.cpp $(HEADERS)
	$(CC) $(FLAGS) -c -o $@ $<

dataGame : $(OBJ)
	g++ -o $@ $^ $(FLAGS) $(LFLAGS)

clean:
	rm *.o *.gch dataGame
