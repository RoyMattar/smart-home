#	makefile	:	SmartHome - so: TestSensor

CC	= g++
CXX = $(CC)

CFLAGS = -ansi -pedantic -g -fPIC
CFLAGS += -Wall
CFLAGS += -Werror
CXXFLAGS = $(CFLAGS)
CXXFLAGS += -std=c++03 

CPPFLAGS = -I$(INC_DIR)
CPPFLAGS += -MMD
LDFLAGS = -shared
LDLIBS = -lpthread

INC_DIR = ../../../inc
SRC_DIR = ../../../src

TARGET_PATH = ..
TARGET = $(TARGET_PATH)/libTestSensor.so

SOURCES = test_sensor.cpp
SOURCES += $(SRC_DIR)/event.cpp $(SRC_DIR)/agent_info.cpp
SOURCES += $(SRC_DIR)/thread.cpp $(SRC_DIR)/atomic_flag.cpp

OBJECTS = $(SOURCES:%.cpp=%.o)

DEPENDS = $(OBJECTS:%.o=%.d)
-include $(DEPENDS)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) -o $(TARGET) $(OBJECTS) $(LDLIBS)

clean:
	rm -f $(TARGET) $(OBJECTS) $(DEPENDS) $(INC_DIR)/*.gch

.PHONY: all clean