CC 	=	gcc
CXX	=	g++
CFLAGS	=	-g	-Wall
TARGET	=	stack_trace
all: $(TARGET)

$(TARGET): $(TARGET).cpp
	g++ -g -Wall -m32 -rdynamic stack_trace.cpp -o stack_trace
clean:
	$(RM) $(TARGET) 
