CC = g++
FLAGS = -Wall -O3 -std=c++11 -I /usr/include/lua5.1 -I include/ -I /usr/include/SDL2 -I /usr/include/GL -D_GNU_SOURCE=1 -D_REENTRANT 
LFLAGS = -lSDL2 -lSDL2_image -lSDL2_net -lGL -llua5.1-c++
HEADERS = AbilityType.hpp.gch GameDynamicData.hpp.gch Game.hpp.gch  SaveFile.hpp.gch Unit.hpp.gch UnitType.hpp.gch include/json.hpp.gch GlobalIncludes.hpp.gch UI.hpp.gch GlobalIncludes.hpp.gch LuaManager.hpp.gch Window.hpp.gch Image.hpp.gch
OBJ = AbilityType.o Game.o GameDynamicData.o SaveFile.o Unit.o UnitType.o main.o Map.o UI.o LuaManager.o Window.o Image.o

%.o : %.cpp 
	$(CC) $(FLAGS) -c -o $@ $<

%.hpp.gch: %.hpp
	$(CC) $(FLAGS) -o $@ $<

dataGame : $(OBJ)
	g++ -o $@ $^ $(FLAGS) $(LFLAGS)

clean:
	rm *.o *.gch dataGame

