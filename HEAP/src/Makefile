CXX = g++
INCLUDE = include
CXXFLAGS = -Wall -std=c++11 -O2 -I$(INCLUDE)
OBJ = test.o
TARGET = ../test

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: clean
