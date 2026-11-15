#define BOOST_TEST_MODULE test_ip_filter

#include "ip_filter.h"

#include "boost/test/unit_test.hpp"

#include <vector>

BOOST_AUTO_TEST_SUITE(test_filter)

BOOST_AUTO_TEST_CASE(test_filter_by_first_byte) {
    std::vector<IPv4Addr> ip_pool = {
        { 186, 46, 222, 194 },
        { 222, 130, 177, 64 },
        { 192, 168, 0, 1 },
        { 10, 0, 0, 1 }
    };

    auto result = filter(ip_pool, 10);
    BOOST_TEST(result.size() == 1);
    BOOST_TEST(result[0][0] == 10);
}

BOOST_AUTO_TEST_CASE(test_filter_by_first_and_second_byte) {
    std::vector<IPv4Addr> ip_pool = {
        { 186, 46, 222, 194 },
        { 186, 130, 177, 64 },
        { 192, 168, 0, 1 },
        { 10, 0, 0, 1 }
    };

    auto result = filter(ip_pool, 186, 130);
    BOOST_TEST(result.size() == 1);
    BOOST_TEST(result[0][0] == 186);
    BOOST_TEST(result[0][1] == 130);
}

BOOST_AUTO_TEST_CASE(test_filter_no_match) {
    std::vector<IPv4Addr> ip_pool = {
        { 186, 46, 222, 194 },
        { 186, 130, 177, 64 },
        { 192, 168, 0, 1 },
        { 10, 0, 0, 1 }
    };

    auto result = filter(ip_pool, 42);
    BOOST_TEST(result.size() == 0);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(test_filter_any)

BOOST_AUTO_TEST_CASE(test_filter_by_any_byte) {
    std::vector<IPv4Addr> ip_pool = {
        { 186, 46, 222, 194 },
        { 186, 180, 130, 64 },
        { 192, 130, 0, 1 },
        { 10, 0, 0, 1 }
    };

    uint8_t byte = 130;
    auto result = filter_any(ip_pool, byte);
    BOOST_TEST(result.size() == 2);
    BOOST_TEST(result[0][2] == byte);
    BOOST_TEST(result[1][1] == byte);
}

BOOST_AUTO_TEST_CASE(test_filter_no_match) {
    std::vector<IPv4Addr> ip_pool = {
        { 186, 46, 222, 194 },
        { 186, 180, 130, 64 },
        { 192, 130, 0, 1 },
        { 10, 0, 0, 1 }
    };

    uint8_t byte = 42;
    auto result = filter_any(ip_pool, byte);
    BOOST_TEST(result.size() == 0);
}

BOOST_AUTO_TEST_SUITE_END()