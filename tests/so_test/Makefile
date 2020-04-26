#	makefile	:	SmartHome - so: main

CC	= g++
CXX = $(CC)

CFLAGS = -ansi -pedantic -g
CFLAGS += -Wall
CFLAGS += -Werror
CXXFLAGS = $(CFLAGS)
CXXFLAGS += -std=c++03 

CPPFLAGS = -I$(INC_DIR) -I$(IF_DIR)
CPPFLAGS += -MMD
LDFLAGS = -Wl,-rpath $(SO_PATH) -L$(SO_PATH)
LDLIBS = -lCat -ldl

INC_DIR = ../../inc
SO_PATH = ./so_dir

TARGET = so_test

SOURCES = main.cpp

OBJECTS = $(SOURCES:%.cpp=%.o)

DEPENDS = $(OBJECTS:%.o=%.d)
-include $(DEPENDS)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) -o $(TARGET) $(OBJECTS) $(LDLIBS)

check: $(TARGET) 
	./$(TARGET) -v

clean:
	rm -f $(TARGET) $(OBJECTS) $(DEPENDS) $(INC_DIR)/*.gch

debug: $(TARGET)
	gdb -q ./$(TARGET)

valgrind: $(TARGET)
	valgrind --leak-check=full ./$(TARGET)

.PHONY: all check clean debug valgrind