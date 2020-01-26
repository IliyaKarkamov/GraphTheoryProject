#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <graph/adjacency_list.h>
#include <string>

TEST_CASE("Adjacency list basic test")
{
    using namespace graph;
    using namespace std::string_literals;

    AdjacencyList<std::string, float> graph(3);
    const AdjacencyList<std::string, float>& constGraph = graph;

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

    REQUIRE(std::fabs(graph.getEdgeById(googleDescriptor, googleIbmEdge).second - 5.f) < 0.0001f);

    const auto microsoftDescriptor = graph.addVertex("Microsoft"s, 2);

    REQUIRE(graph.size() == 3);
    REQUIRE(graph.size() == constGraph.size());

    graph.addEdge(microsoftDescriptor, googleDescriptor, 30.f);

    REQUIRE(graph.size(googleDescriptor) == 2);
    REQUIRE(graph.size(microsoftDescriptor) == 1);
    REQUIRE(graph.size(ibmDescriptor) == 1);

    graph.addEdge(microsoftDescriptor, ibmDescriptor, 25.f);

    REQUIRE(graph.size(googleDescriptor) == 2);
    REQUIRE(graph.size(microsoftDescriptor) == 2);
    REQUIRE(graph.size(ibmDescriptor) == 2);

    REQUIRE(graph.size(googleDescriptor) == constGraph.size(googleDescriptor));
    REQUIRE(graph.size(microsoftDescriptor) == constGraph.size(microsoftDescriptor));
    REQUIRE(graph.size(ibmDescriptor) == constGraph.size(ibmDescriptor));

    auto&& googleIbmEdgeWeight = graph.getEdge(googleDescriptor, ibmDescriptor);
    auto&& constGoogleIbmEdgeWeight = constGraph.getEdge(googleDescriptor, ibmDescriptor);

    REQUIRE(std::fabs(googleIbmEdgeWeight - constGoogleIbmEdgeWeight) < 0.0001f);
    REQUIRE(std::fabs(graph.getEdgeById(googleDescriptor, googleIbmEdge).second - googleIbmEdgeWeight) < 0.0001f);

    graph.sortEdges(googleDescriptor, [](float lhs, float rhs) { return lhs > rhs; });

    for (auto i = 1u; i < graph.size(googleDescriptor); ++i)
    {
        const auto weight1 = graph.getEdgeById(googleDescriptor, i - 1).second;
        const auto weight2 = graph.getEdgeById(googleDescriptor, i).second;

        REQUIRE(weight1 > weight2);
    }

    graph.clearEdges();

    for (auto i = 0u; i < graph.size(); ++i)
        REQUIRE(graph.size(i) == 0u);

    graph.clear();

    REQUIRE(graph.size() == 0);
}