#	makefile	:	SmartHome - so: TestSensor

CC	= g++
CXX = $(CC)

CFLAGS = -ansi -pedantic -g -fPIC
CFLAGS += -Wall
CFLAGS += -Werror
CXXFLAGS = $(CFLAGS)
CXXFLAGS += -std=c++03 

CPPFLAGS = -I$(INC_DIR) -I$(TEST_INC_DIR)
CPPFLAGS += -MMD
LDFLAGS = -shared
LDLIBS = -lpthread

INC_DIR = ../../../../inc
TEST_INC_DIR = ../../inc
SRC_DIR = ../../../../src
TEST_SRC_DIR = ../../src

TARGET = libTestSensor.so

SOURCES = $(TEST_SRC_DIR)/test_sensor.cpp $(SRC_DIR)/agent_info.cpp $(SRC_DIR)/thread.cpp $(SRC_DIR)/event.cpp

OBJECTS = $(SOURCES:%.cpp=%.o)

DEPENDS = $(OBJECTS:%.o=%.d)
-include $(DEPENDS)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) -o $(TARGET) $(OBJECTS) 

clean:
	rm -f $(TARGET) $(OBJECTS) $(DEPENDS) $(INC_DIR)/*.gch $(TEST_INC_DIR)/*.gch

.PHONY: all clean