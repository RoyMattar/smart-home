#	makefile	:	SmartHome - mvptest

CC	= g++
CXX = $(CC)

CFLAGS = -ansi -pedantic -g
CFLAGS += -Wall
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
#SOURCES = $(TARGET).cpp $(SRC_DIR)/Event.cpp $(TEST_SRC_DIR)/TestSensorAgent.cpp $(TEST_SRC_DIR)/TestEventHub.cpp $(TEST_SRC_DIR)/TestControllerAgent.cpp $(SRC_DIR)/AtomicFlag.cpp $(SRC_DIR)/Mutex.cpp $(SRC_DIR)/LockGuard.cpp $(SRC_DIR)/CondVar.cpp
OBJS = $(TARGET).o $(SRC_DIR)/Event.o $(TEST_SRC_DIR)/TestSensorAgent.o $(TEST_SRC_DIR)/TestEventHub.o $(TEST_SRC_DIR)/TestControllerAgent.o $(SRC_DIR)/AtomicFlag.o $(SRC_DIR)/Mutex.o $(SRC_DIR)/LockGuard.o $(SRC_DIR)/CondVar.o

all: $(TARGET)

check: $(TARGET) 
	./$(TARGET) -v

$(TARGET): $(OBJS)

$(TARGET).o: $(INC_DIR)/mu_test.h 
$(SRC_DIR)/Event.o: $(INC_DIR)/Event.hpp $(INC_DIR)/common_utils.hpp
$(TEST_SRC_DIR)/TestSensorAgent.o: $(TEST_INC_DIR)/TestSensorAgent.hpp $(INC_DIR)/common_utils.hpp $(INC_DIR)/iEnqueueableQueue.hpp $(INC_DIR)/Event.hpp
$(TEST_SRC_DIR)/TestEventHub.o: $(TEST_INC_DIR)/TestEventHub.hpp $(INC_DIR)/common_utils.hpp $(INC_DIR)/iDequeueableQueue.hpp $(INC_DIR)/Event.hpp $(TEST_INC_DIR)/TestControllerAgent.hpp
$(TEST_SRC_DIR)/TestControllerAgent.o: $(TEST_INC_DIR)/TestControllerAgent.hpp $(INC_DIR)/Event.hpp
$(SRC_DIR)/AtomicFlag.o: $(INC_DIR)/AtomicFlag.hpp
$(SRC_DIR)/Mutex.o: $(INC_DIR)/Mutex.hpp
$(SRC_DIR)/LockGuard.o: $(INC_DIR)/LockGuard.hpp
$(SRC_DIR)/CondVar.o: $(INC_DIR)/CondVar.hpp

valgrind: $(TARGET)
	valgrind ./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS) *.gch


.PHONY: clean valgrind check