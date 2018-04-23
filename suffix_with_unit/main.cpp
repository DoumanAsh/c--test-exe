#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <iostream>
#include <limits>
#include "suffix_with_unit.hpp"

//suffixWithUnit(123) => 123
//suffixWithUnit(1234) => 1.234 Kilo
//suffixWithUnit(12345) => 12.345 Kilo
//suffixWithUnit(1234567) => 1.234567 Mega
//suffixWithUnit(12345678) => 12.345678 Mega

TEST_CASE("test zero") {
    REQUIRE(suffixWithUnit(0) == "0");
    REQUIRE(suffixWithUnit(0L) == "0");
}

TEST_CASE("test max") {
    REQUIRE(suffixWithUnit(std::numeric_limits<int>::max()) == "2.147483647 Giga");
    REQUIRE(suffixWithUnit(std::numeric_limits<uint64_t>::max()) == "18.446744073709551615 Exa");
}

TEST_CASE("test int") {
    REQUIRE(suffixWithUnit(10) == "10");
    REQUIRE(suffixWithUnit(1000) == "1 Kilo");
    REQUIRE(suffixWithUnit(1001) == "1.001 Kilo");
    REQUIRE(suffixWithUnit(1021) == "1.021 Kilo");
    REQUIRE(suffixWithUnit(1252) == "1.252 Kilo");
    REQUIRE(suffixWithUnit(123) == "123");
    REQUIRE(suffixWithUnit(1234) == "1.234 Kilo");
    REQUIRE(suffixWithUnit(12345) == "12.345 Kilo");
    REQUIRE(suffixWithUnit(1234567) == "1.234567 Mega");
    REQUIRE(suffixWithUnit(12345678) == "12.345678 Mega");
    REQUIRE(suffixWithUnit(10000008) == "10.000008 Mega");

    REQUIRE(suffixWithUnit(-1000) == "-1 Kilo");
    REQUIRE(suffixWithUnit(-1252) == "-1.252 Kilo");
    REQUIRE(suffixWithUnit(-123) == "-123");
    REQUIRE(suffixWithUnit(-1234) == "-1.234 Kilo");
    REQUIRE(suffixWithUnit(-12345) == "-12.345 Kilo");
    REQUIRE(suffixWithUnit(-1234567) == "-1.234567 Mega");
}

TEST_CASE("test double") {
    REQUIRE(suffixWithUnit(10L) == "10");
    REQUIRE(suffixWithUnit(1000L) == "1 Kilo");
    REQUIRE(suffixWithUnit(1001L) == "1.001 Kilo");
    REQUIRE(suffixWithUnit(1021L) == "1.021 Kilo");
    REQUIRE(suffixWithUnit(1252L) == "1.252 Kilo");
    REQUIRE(suffixWithUnit(123L) == "123");
    REQUIRE(suffixWithUnit(1234L) == "1.234 Kilo");
    REQUIRE(suffixWithUnit(12345L) == "12.345 Kilo");
    REQUIRE(suffixWithUnit(1234567L) == "1.234567 Mega");
    REQUIRE(suffixWithUnit(12345678L) == "12.345678 Mega");
}

TEST_CASE("test char") {
    REQUIRE(suffixWithUnit('a') == "97");
}
