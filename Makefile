CXX = g++
CXXFLAGS = -Wall -std=c++11  -O3 -I /usr/include/lua5.1 -I include/ -I /usr/include/SDL2 -I /usr/include/GL -D_GNU_SOURCE=1 -D_REENTRANT  -DPRETTY_SAVE_FILES -g
LFLAGS = -lSDL2 -lSDL2_image -lSDL2_net -lGL -llua5.1-c++ -lgcov
HEADERS = AbilityType.hpp.gch GameDynamicData.hpp.gch Game.hpp.gch  SaveFile.hpp.gch Unit.hpp.gch UnitType.hpp.gch include/json.hpp.gch GlobalIncludes.hpp.gch UI.hpp.gch GlobalIncludes.hpp.gch LuaManager.hpp.gch Window.hpp.gch Image.hpp.gch
OBJ = AbilityType.o Game.o GameDynamicData.o SaveFile.o Unit.o UnitType.o Map.o UI.o LuaManager.o Window.o Image.o TerrainType.o
MAIN_ONLY = main.o
TEST_OBJ = test_main.o StaticDataTest.o LuaManagerTests.o DynamicDataTest.o

dataGame : $(OBJ) $(MAIN_ONLY)
	$(CXX) -o $@ $^ $(FLAGS) $(LFLAGS)

%.hpp.gch: %.hpp
	$(CXX) $(FLAGS) -c  $<

clean:
	rm -f *.o *.gch *.gcda *.gcno dataGame tests

tests: $(OBJ) $(TEST_OBJ)
	$(CXX) -o $@ $^ $(FLAGS) $(LFLAGS)

all: dataGame tests

