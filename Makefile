CXX ?= g++
CXXFLAGS ?= -std=c++20
CPPFLAGS ?= -O3 -Wall -I. -I./include
SRC = main.cpp Matrix.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = main

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OBJ) -o $(EXEC)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< $(CPPFLAGS) -o $@

clean:
	rm -f $(OBJ)

distclean:
	rm -f $(OBJ) $(EXEC)
