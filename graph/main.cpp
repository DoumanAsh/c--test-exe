#include <iostream>
#include "graph.hpp"

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <limits>

TEST_CASE("Dijkstra 1") {
    Graph<int, 6> graph;

    graph.add_path(0, 1, 7, tags::both);
    graph.add_path(0, 2, 9, tags::both);
    graph.add_path(0, 5, 14, tags::both);

    graph.add_path(1, 2, 10, tags::both);
    graph.add_path(1, 3, 15, tags::both);

    graph.add_path(2, 3, 11, tags::both);
    graph.add_path(2, 5, 2, tags::both);

    graph.add_path(3, 4, 6, tags::both);

    graph.add_path(4, 5, 9, tags::both);

    const auto result_to4 = graph.shortest_path(0, 4);
    REQUIRE(result_to4.first == 20);
    REQUIRE(result_to4.second == std::vector{0, 2, 5, 4});

    const auto result_to5 = graph.shortest_path(0, 5);
    REQUIRE(result_to5.first == 11);
    REQUIRE(result_to5.second == std::vector{0, 2, 5});

    const auto result_to3 = graph.shortest_path(0, 3);
    REQUIRE(result_to3.first == 20);
    REQUIRE(result_to3.second == std::vector{0, 2, 3});

    const auto result_to2 = graph.shortest_path(0, 2);
    REQUIRE(result_to2.first == 9);
    REQUIRE(result_to2.second == std::vector{0, 2});

    const auto result_to1 = graph.shortest_path(0, 1);
    REQUIRE(result_to1.first == 7);
    REQUIRE(result_to1.second == std::vector{0, 1});

    const auto result_to0 = graph.shortest_path(0, 0);
    REQUIRE(result_to0.first == 0);
    REQUIRE(result_to0.second == std::vector{0});
}

TEST_CASE("Dijkstra 2") {
    Graph<int, 4> graph;

    graph.add_path(0, 1, 7, tags::both);
    graph.add_path(0, 2, 9, tags::both);

    graph.add_path(1, 3, 4, tags::both);
    graph.add_path(2, 3, 1, tags::both);

    const auto result = graph.shortest_path(0, 3);
    REQUIRE(result.first == 10);
}
