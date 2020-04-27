#	makefile	:	SmartHome - so: TestHybrid

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
LDLIBS =

INC_DIR = ../../../../inc
TEST_INC_DIR = ../../inc
SRC_DIR = ../../../../src
TEST_SRC_DIR = ../../src

TARGET = libTestHybrid.so

SOURCES = $(TEST_SRC_DIR)/test_hybrid.cpp
SOURCES += $(SRC_DIR)/agent_info.cpp $(SRC_DIR)/event.cpp $(SRC_DIR)/event_topic.cpp
SOURCES += $(SRC_DIR)/mutex.cpp $(SRC_DIR)/lock_guard.cpp

OBJECTS = $(SOURCES:%.cpp=%.o)

DEPENDS = $(OBJECTS:%.o=%.d)
-include $(DEPENDS)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) -o $(TARGET) $(OBJECTS) 

clean:
	rm -f $(TARGET) $(OBJECTS) $(DEPENDS) $(INC_DIR)/*.gch $(TEST_INC_DIR)/*.gch

.PHONY: all clean