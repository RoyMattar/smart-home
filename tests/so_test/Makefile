#	makefile	:	SmartHome - complete_test

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
LDLIBS = -ldl

INC_DIR = ../../inc
SRC_DIR = ../../src
SO_PATH = ./so_dir

TARGET = so_test

SOURCES = main.cpp i_cat.cpp $(SRC_DIR)/so_lib_handler.cpp

OBJECTS = $(SOURCES:%.cpp=%.o)

DEPENDS = $(OBJECTS:%.o=%.d)
-include $(DEPENDS)

all: $(TARGET)

$(TARGET): $(SO_PATH)/libCat.so $(OBJECTS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) -o $(TARGET) $(OBJECTS) $(LDLIBS)

$(SO_PATH)/libCat.so:
	$(MAKE) -C $(SO_PATH) all

check: $(TARGET) 
	./$(TARGET) -v

clean: clean_main clean_so
clean_main:
	rm -f $(TARGET) $(OBJECTS) $(DEPENDS) $(INC_DIR)/*.gch
clean_so:
	$(MAKE) -C so_dir clean

debug: $(TARGET)
	gdb -q ./$(TARGET)

valgrind: $(TARGET)
	valgrind --leak-check=full ./$(TARGET)

.PHONY: all check clean clean_main clean_so debug valgrind