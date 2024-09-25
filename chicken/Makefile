CC = g++
CFLAG = -std=c++11 -Wall -O2
SRC = src
INC = -I$(SRC)
OBJS = $(SRC)/chicken.o
TARGET = ikun
WINDOWS_EXEC_SUFFIX = .exe
LINUX_EXEC_SUFFIX = 

$(TARGET): $(OBJS)
	$(CC) $(CFLAG) $(OBJS) -o $@

.cpp.o:
	$(CC) $(CFLAG) $(INC) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

win_run: $(TARGET)
	./$(addsuffix $(WINDOWS_EXEC_SUFFIX), $(TARGET))

linux_run: $(TARGET)
	./$(addsuffix $(LINUX_EXEC_SUFFIX), $(TARGET))
