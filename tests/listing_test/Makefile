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

TARGET = listing_test
#SOURCES = $(TARGET).cpp $(SRC_DIR)/event.cpp $(SRC_DIR)/consumer_list_mt.cpp $(SRC_DIR)/mutex.cpp $(SRC_DIR)/lock_guard.cpp $(TEST_SRC_DIR)/test_consumer.cpp
OBJS = $(TARGET).o $(SRC_DIR)/event.o $(SRC_DIR)/consumer_list_mt.o $(SRC_DIR)/mutex.o $(SRC_DIR)/lock_guard.o $(TEST_SRC_DIR)/test_consumer.o

all: $(TARGET)

check: $(TARGET) 
	./$(TARGET) -v

$(TARGET): $(OBJS)

$(TARGET).o: $(INC_DIR)/mu_test.h $(INC_DIR)/common_utils.hpp $(INC_DIR)/event.hpp $(INC_DIR)/consumer_map.hpp $(INC_DIR)/inl/consumer_map.hxx $(TEST_INC_DIR)/test_consumer.hpp
$(SRC_DIR)/event.o: $(INC_DIR)/event.hpp $(INC_DIR)/common_utils.hpp
$(SRC_DIR)/consumer_list_mt.o: $(INC_DIR)/consumer_list_mt.hpp $(INC_DIR)/common_utils.hpp  \
	 $(INC_DIR)/i_event_consumer.hpp $(INC_DIR)/event.hpp $(INC_DIR)/mutex.hpp
$(SRC_DIR)/mutex.o: $(INC_DIR)/mutex.hpp $(INC_DIR)/common_utils.hpp
$(SRC_DIR)/lock_guard.o: $(INC_DIR)/lock_guard.hpp $(INC_DIR)/mutex.hpp $(INC_DIR)/common_utils.hpp
$(TEST_SRC_DIR)/test_consumer.o: $(TEST_INC_DIR)/test_consumer.hpp $(INC_DIR)/i_event_consumer.hpp $(INC_DIR)/i_event_subscriber.hpp
$(INC_DIR)/consumer_map.hpp: $(INC_DIR)/inl/consumer_map.hxx $(INC_DIR)/i_consumer_registrar.hpp $(INC_DIR)/i_consumer_lister.hpp

valgrind: $(TARGET)
	valgrind ./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS) *.gch


.PHONY: clean valgrind check