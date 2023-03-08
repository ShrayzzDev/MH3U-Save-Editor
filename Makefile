CXX = g++

CPPFLAGS =  -Wall -std=c++17

all: exe

clean:
	rm -f *.o exe 

exe: main.o chargement.o edition.o
	$(CXX) $(CPPFLAGS) $+ -o $@

%.o: %.cpp
	$(CXX) $(CPPFLAGS) -c $<

main.o: main.cpp saveEditior.hpp

chargement.o: chargement.cpp saveEditior.hpp

edition.o: edition.cpp saveEditior.hpp
