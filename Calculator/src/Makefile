CXX = g++
INCLUDE = includes
CXXFLAGS = -std=c++11 -O2 -I$(INCLUDE)
OBJ = main.o
TEST_OBJ = test.o
TARGET = ../calculator
TEST = ../test

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

$(TEST): $(TEST_OBJ)
	$(CXX) $(TEST_OBJ) -o $(TEST)

test: $(TEST)
	$(TEST)

clean:
	rm -f $(OBJ) $(TARGET) $(TEST) $(TEST_OBJ)

.PHONY: clean