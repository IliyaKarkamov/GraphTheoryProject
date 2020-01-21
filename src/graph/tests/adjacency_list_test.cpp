#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <graph/adjacency_list.h>
#include <string>

TEST_CASE("simple")
{
    using namespace graph;
    using namespace std::string_literals;

    AdjacencyList<std::string, float> graph(3);

    const auto googleDescriptor = graph.addVertex("Google"s, 1);
    const auto ibmDescriptor = graph.addVertex("IBM"s, 1);

    REQUIRE(graph.size() == 2);

    REQUIRE(graph.getVertex(googleDescriptor) == "Google"s);
    REQUIRE(graph.getVertex(ibmDescriptor) == "IBM"s);

    REQUIRE(graph.size(googleDescriptor) == 0);
    REQUIRE(graph.size(ibmDescriptor) == 0);

    const auto googleIbmEdge = graph.addEdge(googleDescriptor, ibmDescriptor, 5.f);

    REQUIRE(graph.size(googleDescriptor) == 1);
    REQUIRE(graph.size(ibmDescriptor) == 1);

    REQUIRE(std::fabs(graph.getEdge(googleDescriptor, googleIbmEdge) - 5.f) < 0.0001);

    const auto microsoftDescriptor = graph.addVertex("Microsoft"s, 2);

    REQUIRE(graph.size() == 3);

    graph.addEdge(microsoftDescriptor, googleDescriptor, 30.f);

    REQUIRE(graph.size(googleDescriptor) == 2);
    REQUIRE(graph.size(microsoftDescriptor) == 1);
    REQUIRE(graph.size(ibmDescriptor) == 1);

    graph.addEdge(microsoftDescriptor, ibmDescriptor, 25.f);

    REQUIRE(graph.size(googleDescriptor) == 2);
    REQUIRE(graph.size(microsoftDescriptor) == 2);
    REQUIRE(graph.size(ibmDescriptor) == 2);
}