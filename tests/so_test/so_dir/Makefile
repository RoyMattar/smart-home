#	makefile	:	SmartHome - so: Cat

CC	= g++
CXX = $(CC)

CFLAGS = -ansi -pedantic -g -fPIC
CFLAGS += -Wall
CFLAGS += -Werror
CXXFLAGS = $(CFLAGS)
CXXFLAGS += -std=c++03 

CPPFLAGS = -I$(INC_DIR) -I$(IF_DIR)
CPPFLAGS += -MMD
LDFLAGS = -shared
LDLIBS =

INC_DIR = ../../../inc
IF_DIR = ..

TARGET = libCat.so

SOURCES = cat.cpp $(IF_DIR)/i_cat.cpp

OBJECTS = $(SOURCES:%.cpp=%.o)

DEPENDS = $(OBJECTS:%.o=%.d)
-include $(DEPENDS)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) -o $(TARGET) $(OBJECTS) 

clean:
	rm -f $(TARGET) $(OBJECTS) $(DEPENDS) $(INC_DIR)/*.gch $(IF_DIR)/*.gch

.PHONY: all clean