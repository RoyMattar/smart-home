#include "mu_test.h"

#include <string>
#include <cstddef> // size_t
#include <unistd.h> // sleep()

#include "server.hpp"

UNIT(sim)
    const std::string configFile = "config.ini";
    const size_t parallelFactor = 2;
    const size_t publicationBandwidth = 10;
    const size_t distributionBandwidth = 10;

    smart_home::Server s(configFile, parallelFactor, publicationBandwidth, distributionBandwidth);

    s.Start();
    sleep(3);
    s.Stop();
    ASSERT_PASS();
END_UNIT

TEST_SUITE(sim)
    TEST(sim)
END_SUITE
