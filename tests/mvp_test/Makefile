#	makefile	:	SmartHome - mvptest

CC	= g++
CXX = $(CC)

CFLAGS = -ansi -pedantic -g
CFLAGS += -Wall -Wno-newline-eof
#CFLAGS += -Werror
CXXFLAGS = $(CFLAGS) -std=c++03 

CPPFLAGS = -I$(INC_DIR) -I$(TEST_INC_DIR)
LDFLAGS = 
LDLIBS =

INC_DIR = ../../inc
SRC_DIR = ../../src
TEST_INC_DIR = ../common/inc
TEST_SRC_DIR = ../common/src

TARGET = mvptest
#SOURCES = $(TARGET).cpp $(SRC_DIR)/event.cpp $(TEST_SRC_DIR)/test_sensor_agent.cpp $(TEST_SRC_DIR)/test_event_hub.cpp $(TEST_SRC_DIR)/test_controller_agent.cpp $(SRC_DIR)/atomic_flag.cpp $(SRC_DIR)/mutex.cpp $(SRC_DIR)/lock_guard.cpp $(SRC_DIR)/condvar.cpp
OBJS = $(TARGET).o $(SRC_DIR)/event.o $(TEST_SRC_DIR)/test_sensor_agent.o $(TEST_SRC_DIR)/test_event_hub.o $(TEST_SRC_DIR)/test_controller_agent.o $(SRC_DIR)/atomic_flag.o $(SRC_DIR)/mutex.o $(SRC_DIR)/lock_guard.o $(SRC_DIR)/condvar.o

all: $(TARGET)

check: $(TARGET) 
	./$(TARGET) -v

$(TARGET): $(OBJS)

$(TARGET).o: $(INC_DIR)/mu_test.h 
$(SRC_DIR)/event.o: $(INC_DIR)/event.hpp $(INC_DIR)/common_utils.hpp
$(TEST_SRC_DIR)/test_sensor_agent.o: $(TEST_INC_DIR)/test_sensor_agent.hpp $(INC_DIR)/common_utils.hpp $(INC_DIR)/i_push_event_bus.hpp $(INC_DIR)/event.hpp
$(TEST_SRC_DIR)/test_event_hub.o: $(TEST_INC_DIR)/test_event_hub.hpp $(INC_DIR)/common_utils.hpp $(INC_DIR)/i_pull_event_bus.hpp $(INC_DIR)/event.hpp $(TEST_INC_DIR)/test_controller_agent.hpp
$(TEST_SRC_DIR)/test_controller_agent.o: $(TEST_INC_DIR)/test_controller_agent.hpp $(INC_DIR)/event.hpp
$(SRC_DIR)/atomic_flag.o: $(INC_DIR)/atomic_flag.hpp
$(SRC_DIR)/mutex.o: $(INC_DIR)/mutex.hpp
$(SRC_DIR)/lock_guard.o: $(INC_DIR)/lock_guard.hpp
$(SRC_DIR)/condvar.o: $(INC_DIR)/condvar.hpp

valgrind: $(TARGET)
	valgrind ./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS) *.gch


.PHONY: clean valgrind check