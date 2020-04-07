#include "mu_test.h"

#include "common_utils.hpp"
#include "event.hpp"
#include "event_bus.hpp"
#include "test_sensor_agent.hpp"
#include "test_event_hub.hpp"
#include "test_controller_agent.hpp"

using namespace advcpp;
using smart_home::Event;
using smart_home::EventBus;
using test_smart_home::TestSensorAgent;
using test_smart_home::TestEventHub;
using test_smart_home::TestControllerAgent;

UNIT(mvp)
    Event::Type tempChange = "TEMP_CHANGE";
    //Event::Type smokeDetected = "SMOKE";

    SharedPtr<EventBus> bus(new EventBus(5));
    TestEventHub hub(bus);

    /*TestSensorAgent tempSensor(bus, eventX, 100);
    TestSensorAgent smokeSensor(bus, eventLight, 100);

    TestControllerAgent ctlSmoke("Smoke");
    TestControllerAgent ctlDoor("DoorOPen", "DoorClose");
    TestControllerAgent ctlSmoke3("Smoke", locF04R101);*/

    TestSensorAgent tempSensor(bus);
    TestControllerAgent tempController;
    
    hub.Subscribe(tempController);
    /*HUb::subscribe(Controler* c){
        for(auto e : c->getEventTypesOfIntreset()){
            m_dl.add(c, e);
        }
    }

    hub.Connect(controller);
    Hub::Connect(Controller& c)
    {
        m_vector.push_back(c);
        c.subscribeThySelf(m_dl);   
        
        Controller::subscribeThySelf(dl){  m_dl= dl;dl.add(this, "Ev3"); dl.add(m_eventXHandler, "Ex6"); }
    }*/

// setup is done, lets test behavior
    Event e1(tempChange, "06/04/20 12:12", "+5C", "B-1-3");
    ASSERT_EQUAL(bus->NumOfElems(), 0);
    tempSensor.PublishEvent(e1);
    Event e2(tempChange, "06/04/20 15:58", "-2C", "B-1-3");
    tempSensor.PublishEvent(e2);
    ASSERT_EQUAL(bus->NumOfElems(), 2);
    hub.DistributeEvent();

// lets assert and verify
    Event eout = tempController.GetEvent();
    //ASSERT_EQUAL(eout, e1);
    ASSERT_EQUAL(bus->NumOfElems(), 1);
END_UNIT

TEST_SUITE(mvptest)
    TEST(mvp)
END_SUITE