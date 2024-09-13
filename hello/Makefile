CC = g++
CFLAG = -std=c++17 -Wall -O2
SRC = src
INC = -I$(SRC)
OBJS = $(SRC)/hello.o
TARGET = hello

hello: $(OBJS)
	$(CC) $(CFLAG) $(OBJS) -o $@

.cpp.o:
	$(CC) $(CLAG) $(INC) -c $< -o $@

clean:
	rm -f $(EXE_WINDOWS) $(TARGET)