CXX = g++

CPPFLAGS =  -Wall -std=c++17

all: exe

clean:
	rm -f *.o exe 

exe: main.o item.o
	$(CXX) $(CPPFLAGS) $+ -o $@

%.o: %.cpp
	$(CXX) $(CPPFLAGS) -c $<

main.o: main.cpp item.hpp

item.o: item.cpp item.hpp
