#	makefile	:	SmartHome - distribution_test

CC	= g++
CXX = $(CC)

CFLAGS = -ansi -pedantic -g
CFLAGS += -Wall #-Wno-newline-eof
#CFLAGS += -Werror
CXXFLAGS = $(CFLAGS)
CXXFLAGS += -std=c++03 

CPPFLAGS = -I$(INC_DIR) -I$(TEST_INC_DIR)
CPPFLAGS += -MMD
LDFLAGS = -pthread
LDLIBS =

INC_DIR = ../../inc
TEST_INC_DIR = ../common/inc

SRC_DIR = ../../src
TEST_SRC_DIR = ../common/src

TARGET = distribution_test

SOURCES = $(TARGET).cpp
SOURCES += $(SRC_DIR)/event.cpp $(SRC_DIR)/event_topic.cpp
SOURCES += $(SRC_DIR)/consumer_list_tagged_mt.cpp $(SRC_DIR)/cyclic_tag.cpp
SOURCES += $(SRC_DIR)/event_distributor.cpp $(SRC_DIR)/tagged_distribution_channel.cpp
SOURCES += $(SRC_DIR)/event_courier.cpp $(SRC_DIR)/event_delivery_factory.cpp $(SRC_DIR)/toxic_agent.cpp
SOURCES += $(SRC_DIR)/thread.cpp $(SRC_DIR)/atomic_flag.cpp
SOURCES += $(SRC_DIR)/mutex.cpp $(SRC_DIR)/lock_guard.cpp $(SRC_DIR)/condvar.cpp
SOURCES += $(TEST_SRC_DIR)/test_consumer.cpp
SOURCES += $(TEST_SRC_DIR)/test_registration_bundle.cpp $(TEST_SRC_DIR)/test_distribution_bundle.cpp

OBJECTS = $(SOURCES:%.cpp=%.o)

DEPENDS = $(OBJECTS:%.o=%.d)
-include $(DEPENDS)

all: $(TARGET)

check: $(TARGET) 
	./$(TARGET) -v

$(TARGET): $(OBJECTS)

clean:
	rm -f $(TARGET) $(OBJECTS) $(DEPENDS) $(INC_DIR)/*.gch $(TEST_INC_DIR)/*.gch

debug: $(TARGET)
	gdb -q ./$(TARGET)

valgrind: $(TARGET)
	valgrind --leak-check=full ./$(TARGET)

.PHONY: all check clean debug valgrind