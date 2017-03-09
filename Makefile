CC = g++
FLAGS = -Wall -O3 -std=c++11 -I include/
HEADERS = AbilityType.hpp GameDynamicData.hpp Game.hpp  SaveFile.hpp Unit.hpp UnitType.hpp include/json.hpp
OBJ = AbilityType.o Game.o GameDynamicData.o SaveFile.o Unit.o UnitType.o main.o

%.o : %.cpp $(HEADERS)
	$(CC) $(FLAGS) -c -o $@ $<

dataGame : $(OBJ)
	g++ -o $@ $^ $(FLAGS)

clean:
	rm *.o
