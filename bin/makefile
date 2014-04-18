APPNAME = myorg
SRCDIR = ../src
BINDIR = bin
CXX = g++
CXXFLAGS = -std=c++11 -march=native -g -Wall
INCLUDES = $(shell pkg-config --cflags gtkmm-3.0)
LIBS = $(shell pkg-config --libs gtkmm-3.0)
BIN = $(APPNAME)
SRC = $(wildcard $(SRCDIR)/*.cpp)
OBJ = $(SRC:$(SRCDIR)/%.cpp=%.o)
DEPENDFILE = .depend

all: depend $(BIN)

$(BIN): $(OBJ)
	@echo Linking object files
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(BIN) $(OBJ) $(LIBS)
	@echo Build complete.

%.o: $(SRCDIR)/%.cpp
	@echo Compiling $<
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

depend: $(SRC) $(wildcard $(SRCDIR)/*.h)
	@rm -f $(DEPENDFILE)
	@$(CXX) $(CXXFLAGS) -MM $(SRC) > $(DEPENDFILE)

-include $(DEPENDFILE)

clean:
	@rm -rf $(BIN) $(OBJ) $(DEPENDFILE)

force: | clean all

run: $(BIN)
	@./$(BIN)

debug: $(BIN)
	@gdb $(BIN)

.PHONY: all depend clean run debug
