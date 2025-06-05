# Makefile for Mario-SDL-2 project (Windows, MinGW 64-bit)

# Compiler and flags
CXX = C:\mingw_dev_lib\mingw\mingw64\bin\g++.exe
CXXFLAGS = -g -Wall -I./include/SDL2
LDFLAGS = -L./lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

# Source and target
SOURCES = $(wildcard *.cpp)
TARGET = Game.exe

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET) $(LDFLAGS)

clean:
	del /Q *.o *.exe 2>nul || exit 0

.PHONY: all clean
