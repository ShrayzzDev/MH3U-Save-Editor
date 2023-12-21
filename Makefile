CXX = g++

CPPFLAGS = -Wall -std=c++17

SRCDIR = src/

OBJDIR = obj

OBJS := $(addprefix $(OBJDIR)/, main.o chargement.o edition.o sauvegarde.o)

SRCS := $(addprefix $(SRCDIR)/, main.cpp chargement.cpp edition.cpp sauvegarde.cpp)

all: exe

$(OBJDIR):
	mkdir $(OBJDIR)

clean:
	rm -f $(OBJDIR) exe

exe: $(OBJS)
	$(CXX) $(CPPFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)%.cpp | $(OBJDIR)
	$(CXX) $(CPPFLAGS) -c $< -o $@

$(OBJDIR)/main.o: $(SRCDIR)main.cpp $(SRCDIR)saveEditor.hpp

$(OBJDIR)/chargement.o: $(SRCDIR)chargement.cpp $(SRCDIR)saveEditor.hpp

$(OBJDIR)/edition.o: $(SRCDIR)edition.cpp $(SRCDIR)saveEditor.hpp

$(OBJDIR)/sauvegarde.o: $(SRCDIR)sauvegarde.cpp $(SRCDIR)saveEditor.hpp