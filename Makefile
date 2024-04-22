CXX ?=g++
CXXFLAGS ?= -std=c++20
CPPFLAGS ?= -O3 -Wall -I. -I/mnt/c/Users/Cosimo\ Solidoro/Desktop/PACS/Esempi/pacs-examples/Examples/src/Utilities
SRC=main.cpp 
OBJ=main.o
EXEC=main

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) $(CPPFLAGS) -o $(EXEC)	
$(OBJ): 
	$(CXX) $(CXXFLAGS) $(SRC) $(CPPFLAGS) -o $(OBJ) -c 
clean:
	rm $(OBJ)
distclean:
	rm $(OBJ) $(EXEC) 