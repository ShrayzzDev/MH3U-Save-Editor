CXX = g++

CPPFLAGS =  -Wall -std=c++17

all: exe

clean:
	rm -f *.o exe 

exe: main.o chargement.o edition.o sauvegarde.cpp
	$(CXX) $(CPPFLAGS) $+ -o $@

%.o: %.cpp
	$(CXX) $(CPPFLAGS) -c $<

main.o: main.cpp saveEditor.hpp

chargement.o: chargement.cpp saveEditor.hpp

edition.o: edition.cpp saveEditor.hpp

sauvegarde.o: sauvegarde.cpp saveEditor.hpp
