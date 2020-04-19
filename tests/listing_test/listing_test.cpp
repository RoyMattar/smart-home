#include "mu_test.h"

#include <vector>
#include <cstddef> // size_t 
#include "common_utils.hpp"
#include "event.hpp"
#include "test_consumer.hpp"
#include "consumer_map.hpp"
#include "distribution_list.hpp"

using namespace advcpp;
using namespace smart_home;

UNIT(listing)
    size_t fireConsumersSize = 5;
    Event::Type fireType("type_fire");

    std::vector<SharedPtr<TestConsumer> > fireConsumers;
    for (size_t i = 0 ; i < fireConsumersSize; ++i)
    {
        fireConsumers.push_back(SharedPtr<TestConsumer>(new TestConsumer(fireType)));
    }

    SharedPtr<ConsumerMap<> > map(new ConsumerMap<>());

    for (size_t i = 0; i < fireConsumers.size(); ++i)
    {
        fireConsumers[i]->Subscribe(map);
    }

    DistributionList dlist = *map->List(fireType);

    ASSERT_EQUAL(dlist.size(), fireConsumers.size());

    for (size_t i = 0; i < dlist.size(); ++i)
    {
        //Event::Type currentType = std::tr1::static_pointer_cast<TestConsumer>(dlist[i])->GetType();
        //ASSERT_EQUAL(currentType, fireType);
    }

END_UNIT

TEST_SUITE(listing)
    TEST(listing)
END_SUITE