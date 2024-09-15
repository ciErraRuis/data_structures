CC = g++
CFLAG = -std=c++11 -Wall -O2
SRC = src
INC = -I$(SRC)
OBJS = $(SRC)/hello.o
TARGET = hello

$(TARGET): $(OBJS)
	$(CC) $(CFLAG) $(OBJS) -o $@

.cpp.o:
	$(CC) $(CLAG) $(INC) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
