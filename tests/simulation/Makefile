#	makefile	:	SmartHome - simulation

CC	= g++
CXX = $(CC)

CFLAGS = -ansi -pedantic -g
CFLAGS += -Wall
CFLAGS += -Werror
CXXFLAGS = $(CFLAGS)
CXXFLAGS += -std=c++03 

CPPFLAGS = -I$(INC_DIR)
CPPFLAGS += -MMD
LDFLAGS = -Wl,-rpath $(SO_PATH) -L$(SO_PATH)
LDLIBS = -ldl -lpthread

INC_DIR = ../../inc
SRC_DIR = ../../src

EXE = simulation

SOURCES = $(EXE).cpp
SOURCES += $(SRC_DIR)/server.cpp
SOURCES += $(SRC_DIR)/event.cpp $(SRC_DIR)/event_topic.cpp
SOURCES += $(SRC_DIR)/event_bus.cpp $(SRC_DIR)/event_middleware.cpp
SOURCES += $(SRC_DIR)/consumer_list_tagged_mt.cpp $(SRC_DIR)/cyclic_tag.cpp
SOURCES += $(SRC_DIR)/event_distributor.cpp $(SRC_DIR)/tagged_distribution_channel.cpp
SOURCES += $(SRC_DIR)/event_courier.cpp $(SRC_DIR)/event_delivery_factory.cpp $(SRC_DIR)/toxic_agent.cpp
SOURCES += $(SRC_DIR)/thread.cpp $(SRC_DIR)/atomic_flag.cpp
SOURCES += $(SRC_DIR)/mutex.cpp $(SRC_DIR)/lock_guard.cpp $(SRC_DIR)/condvar.cpp
SOURCES += $(SRC_DIR)/so_lib_handler.cpp $(SRC_DIR)/agent_info.cpp

OBJECTS = $(SOURCES:%.cpp=%.o)

DEPENDS = $(OBJECTS:%.o=%.d)
-include $(DEPENDS)

SO_PATH = ../so
SO_SENSOR = $(SO_PATH)/libTestSensor.so
SO_CONTROLLER = $(SO_PATH)/libTestController.so
SO_HYBRID = $(SO_PATH)/libTestHybrid.so

TARGETS = $(SO_SENSOR)
TARGETS += $(SO_CONTROLLER)
TARGETS += $(SO_HYBRID)
TARGETS += $(EXE)

all: $(TARGETS)

$(EXE): $(OBJECTS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) -o $(EXE) $(OBJECTS) $(LDLIBS)

$(SO_SENSOR):
	$(MAKE) -C $(SO_PATH)/test_sensor all
$(SO_CONTROLLER):
	$(MAKE) -C $(SO_PATH)/test_controller all
$(SO_HYBRID):
	$(MAKE) -C $(SO_PATH)/test_hybrid all

check: $(EXE) 
	./$(EXE) -v

clean: clean_main clean_sensor clean_controller clean_hybrid
clean_main:
	rm -f $(EXE) $(OBJECTS) $(DEPENDS) $(INC_DIR)/*.gch
clean_sensor:
	$(MAKE) -C $(SO_PATH)/test_sensor clean
clean_controller:
	$(MAKE) -C $(SO_PATH)/test_controller clean
clean_hybrid:
	$(MAKE) -C $(SO_PATH)/test_hybrid clean

debug: $(EXE)
	gdb -q ./$(EXE)

valgrind: $(EXE)
	valgrind --leak-check=full ./$(EXE)

.PHONY: all check clean clean_main clean_sensor clean_controller clean_hybrid debug valgrind