# Productivity Tracker - Makefile
# Usage: make        → builds the app
#        make clean  → removes compiled files

CXX     = g++
CXXFLAGS = -std=c++17 -Wall
LIBS    = -lsqlite3
TARGET  = productivity_tracker

all: $(TARGET)

$(TARGET): main.cpp functions1.h functions2.h functions3.h database.h
	$(CXX) $(CXXFLAGS) main.cpp -o $(TARGET) $(LIBS)
	@echo "Build successful! Run with: ./$(TARGET)"

clean:
	rm -f $(TARGET) productivity.db
