#	makefile	:	SmartHome - Registration Test

CC	= g++
CXX = $(CC)

CFLAGS = -ansi -pedantic -g
CFLAGS += -Wall #-Wno-newline-eof
#CFLAGS += -Werror
CXXFLAGS = $(CFLAGS) -std=c++03 

CPPFLAGS = -I$(INC_DIR) -I$(TEST_INC_DIR)
LDFLAGS = 
LDLIBS =

INC_DIR = ../../inc
SRC_DIR = ../../src
TEST_INC_DIR = ../common/inc
TEST_SRC_DIR = ../common/src

TARGET = registration_test
#SOURCES = $(TARGET).cpp $(SRC_DIR)/event.cpp $(TEST_SRC_DIR)/test_consumer.cpp
OBJS = $(TARGET).o $(SRC_DIR)/event.o $(TEST_SRC_DIR)/test_consumer.o

all: $(TARGET)

check: $(TARGET) 
	./$(TARGET) -v

$(TARGET): $(OBJS)

$(TARGET).o: $(INC_DIR)/mu_test.h $(INC_DIR)/common_utils.hpp $(INC_DIR)/event.hpp $(INC_DIR)/i_consumer_registrar.hpp $(TEST_INC_DIR)/test_consumer.hpp
$(SRC_DIR)/event.o: $(INC_DIR)/event.hpp $(INC_DIR)/common_utils.hpp
$(TEST_SRC_DIR)/test_consumer.o: $(TEST_INC_DIR)/test_consumer.hpp $(INC_DIR)/i_event_consumer.hpp $(INC_DIR)/i_event_subscriber.hpp

valgrind: $(TARGET)
	valgrind ./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS) *.gch


.PHONY: clean valgrind check