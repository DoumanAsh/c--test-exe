#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <iostream>

#include "interval_map.hpp"

TEST_CASE("wrong usage") {
    interval_map<int, char> map('A');

    map.assign(10, 9, 'B');
    map.assign(1, 1, 'C');

    REQUIRE(map.m_map.count(10) == 0);
    REQUIRE(map.m_map.count(9) == 0);
    REQUIRE(map.m_map.count(1) == 0);
}

TEST_CASE("bad assign") {
    interval_map<int, char> map('A');

    REQUIRE_THROWS(map.assign(1, 2, 'A'));
    REQUIRE_NOTHROW(map.assign(1, 2, 'B'));
    REQUIRE_NOTHROW(map.assign(5, 8, 'A'));
    REQUIRE_NOTHROW(map.assign(5, 10, 'C'));
    REQUIRE_THROWS(map.assign(3, 4, 'C'));
    REQUIRE_NOTHROW(map.assign(3, 5, 'C'));
}

TEST_CASE("try") {
    interval_map<unsigned int, char> map('A');

    map.assign(5, 7, 'B');
    map.assign(9, 10, 'C');
    map.assign(15, 19, 'A');
    map.assign(10, 20, 'D');
    for (auto const& pair : map.m_map) {
        std::cout << pair.first << "=>" << pair.second << "\n";
    }

    REQUIRE(map[4] == 'A');
    REQUIRE(map[5] == 'B');
    REQUIRE(map[6] == 'B');
    REQUIRE(map[7] == 'B');
    REQUIRE(map[9] == 'C');
    REQUIRE(map[10] == 'D');
    REQUIRE(map[15] == 'D');
    REQUIRE(map[20] == 'D');
    REQUIRE(map[50] == 'D');
}
