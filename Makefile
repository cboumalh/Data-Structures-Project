# This is the Makefile for the CSE 20312 course Lecture 17

# G++ is for the GCC compiler for C++
PP := g++

# CXXFLAGS are the compiler flages for when we compile C++ code in this course
FLAGS := -O2 -g -Wall -Wextra -Wconversion -Wshadow -pedantic -Werror
CXXFLAGS := -m64 -std=c++11 -Weffc++ $(FLAGS)

# Variables for Folders
INC := inc
SRC := src
EXE := exe
OBJ := obj


# Command: make Dijkstra
# Initial Examples of Dijkstra
ProjectObjs := $(OBJ)/Project.o

Project: $(ProjectObjs)
	$(PP) $(CXXFLAGS) -o $(EXE)/Project $(ProjectObjs)

$(OBJ)/Project.o: $(SRC)/Project.cpp
	$(PP) $(CXXFLAGS) -c $(SRC)/Project.cpp -o $@

# make initialize
# Will be called by grader to initialize your objects and executables folders
initialize:
	mkdir $(OBJ) $(EXE)


# Make clean
clean :
	rm -rf $(OBJ)/* $(EXE)/*
