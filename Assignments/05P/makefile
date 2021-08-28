CXX=g++

all: mapTest broken1 broken2 broken3 broken4 broken5

#map.o: map.cpp map.h
#	$(CXX) -c map.cpp

mapTest: mapTest.cpp map.o map.h
	$(CXX) mapTest.cpp map.o -lgtest -lpthread -o mapTest

broken1: mapTest.cpp map_broken1.o map.h
	$(CXX) mapTest.cpp map_broken1.o -lgtest -lpthread -o broken1

broken2: mapTest.cpp map_broken2.o map.h
	$(CXX) mapTest.cpp map_broken2.o -lgtest -lpthread -o broken2

broken3: mapTest.cpp map_broken3.o map.h
	$(CXX) mapTest.cpp map_broken3.o -lgtest -lpthread -o broken3

broken4: mapTest.cpp map_broken4.o map.h
	$(CXX) mapTest.cpp map_broken4.o -lgtest -lpthread -o broken4

broken5: mapTest.cpp map_broken5.o map.h
	$(CXX) mapTest.cpp map_broken5.o -lgtest -lpthread -o broken5

clean:
	rm -f mapTest broken1 broken2 broken3 broken4 broken5

