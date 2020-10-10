CC 	=	gcc
CXX	=	g++
CFLAGS	=	-g	-Wall
TARGET	=	stack_trace
all: $(TARGET)

$(TARGET): $(TARGET).c
	g++ -g -Wall -m32 -rdynamic stack_trace.c -o stack_trace
clean:
	$(RM) $(TARGET) 
