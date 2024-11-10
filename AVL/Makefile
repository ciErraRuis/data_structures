CC = g++
CFLAG = -std=c++11 -Wall -O2

OBJS = test.o
TARGET = test
WINDOWS_EXEC_SUFFIX = .exe
LINUX_EXEC_SUFFIX = 
REPORT = report.log report.aux report.pdf

$(TARGET): $(OBJS)
	$(CC) $(CFLAG) $(OBJS) -o $@

.cpp.o:
	$(CC) $(CFLAG) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) $(REPORT)

win_run: $(TARGET)
	./$(addsuffix $(WINDOWS_EXEC_SUFFIX), $(TARGET))

run: $(TARGET) BST.h
	./$(addsuffix $(LINUX_EXEC_SUFFIX), $(TARGET))

report:
	xelatex report.tex