#include "mu_test.h"

#include "common_utils.hpp"
#include "event.hpp"
#include "test_consumer.hpp"
#include "consumer_map.hpp"

using namespace advcpp;
using namespace smart_home;

UNIT(listing)
    SharedPtr<TestConsumer> consumer(new TestConsumer("type_fire"));
    SharedPtr<ConsumerMap<> > map (new ConsumerMap<>());

END_UNIT

TEST_SUITE(listing)

END_SUITE