#include <catch2/catch.hpp>

#include <graph/adjacency_list.h>
#include <graph/csv_io.h>
#include <graph/algorithms.h>
#include <string>
#include <sstream>

struct Comparator
{
    float value;
    explicit Comparator(float value) : value(value) {}
    bool operator()(const std::pair<graph::VertexDescriptor, float>& edge) { return std::fabs(edge.second - value) < 0.0001f; }
};

TEST_CASE("sieveEdgesIf basic test")
{
    using namespace graph;

    std::stringstream ss;

    ss << R"("","A","B","C","D","E")" << '\n';
    ss << R"("A","1.0","0.1","0.3","0.8","0.6")" << '\n';
    ss << R"("B","0.1","1.0","0.6","0.5","0.9")" << '\n';
    ss << R"("C","0.3","0.6","1.0","0.2","0.1")" << '\n';
    ss << R"("D","0.8","0.5","0.2","1.0","0.3")" << '\n';
    ss << R"("E","0.6","0.9","0.1","0.3","1.0")";

    AdjacencyList<std::string, float> graph;
    ss >> graph;

    sieveEdgesIf(graph, 3, [](float lhs, float rhs) { return lhs > rhs; });

    REQUIRE(graph.size(0u) == 3u);
    REQUIRE(graph.size(1u) == 3u);
    REQUIRE(graph.size(2u) == 3u);
    REQUIRE(graph.size(3u) == 4u);
    REQUIRE(graph.size(4u) == 3u);

    auto edgesOfA = graph.getEdges(0u);

    REQUIRE(std::find_if(std::begin(edgesOfA), std::end(edgesOfA), Comparator(0.8f)) != std::end(edgesOfA));
    REQUIRE(std::find_if(std::begin(edgesOfA), std::end(edgesOfA), Comparator(0.6f)) != std::end(edgesOfA));
    REQUIRE(std::find_if(std::begin(edgesOfA), std::end(edgesOfA), Comparator(0.3f)) != std::end(edgesOfA));

    auto edgesOfB = graph.getEdges(1u);

    REQUIRE(std::find_if(std::begin(edgesOfB), std::end(edgesOfB), Comparator(0.9f)) != std::end(edgesOfB));
    REQUIRE(std::find_if(std::begin(edgesOfB), std::end(edgesOfB), Comparator(0.6f)) != std::end(edgesOfB));
    REQUIRE(std::find_if(std::begin(edgesOfB), std::end(edgesOfB), Comparator(0.5f)) != std::end(edgesOfB));

    auto edgesOfC = graph.getEdges(2u);

    REQUIRE(std::find_if(std::begin(edgesOfC), std::end(edgesOfC), Comparator(0.6f)) != std::end(edgesOfC));
    REQUIRE(std::find_if(std::begin(edgesOfC), std::end(edgesOfC), Comparator(0.3f)) != std::end(edgesOfC));
    REQUIRE(std::find_if(std::begin(edgesOfC), std::end(edgesOfC), Comparator(0.2f)) != std::end(edgesOfC));

    auto edgesOfD = graph.getEdges(3u);

    REQUIRE(std::find_if(std::begin(edgesOfD), std::end(edgesOfD), Comparator(0.8f)) != std::end(edgesOfD));
    REQUIRE(std::find_if(std::begin(edgesOfD), std::end(edgesOfD), Comparator(0.5f)) != std::end(edgesOfD));
    REQUIRE(std::find_if(std::begin(edgesOfD), std::end(edgesOfD), Comparator(0.3f)) != std::end(edgesOfD));
    REQUIRE(std::find_if(std::begin(edgesOfD), std::end(edgesOfD), Comparator(0.2f)) != std::end(edgesOfD));

    auto edgesOfE = graph.getEdges(4u);

    REQUIRE(std::find_if(std::begin(edgesOfE), std::end(edgesOfE), Comparator(0.9f)) != std::end(edgesOfE));
    REQUIRE(std::find_if(std::begin(edgesOfE), std::end(edgesOfE), Comparator(0.6f)) != std::end(edgesOfE));
    REQUIRE(std::find_if(std::begin(edgesOfE), std::end(edgesOfE), Comparator(0.3f)) != std::end(edgesOfE));
}

TEST_CASE("kruskalSpanningTree basic test")
{
    using namespace graph;

    std::stringstream ss;

    ss << R"("","A","B","C")" << '\n';
    ss << R"("A","1.0","0.5","0.1")" << '\n';
    ss << R"("B","0.5","1.0","0.6")" << '\n';
    ss << R"("C","0.1","0.6","1.0")";

    AdjacencyList<std::string, float> graph;
    ss >> graph;

    kruskalSpanningTree(graph, [](const auto& lhs, const auto& rhs) { return lhs.second > rhs.second; });

    REQUIRE(graph.size(0u) == 1);
    REQUIRE(graph.size(1u) == 2);
    REQUIRE(graph.size(0u) == 1);

    auto edgesOfA = graph.getEdges(0u);
    REQUIRE(std::find_if(std::begin(edgesOfA), std::end(edgesOfA), Comparator(0.5f)) != std::end(edgesOfA));

    auto edgesOfB = graph.getEdges(1u);
    REQUIRE(std::find_if(std::begin(edgesOfB), std::end(edgesOfB), Comparator(0.5f)) != std::end(edgesOfB));
    REQUIRE(std::find_if(std::begin(edgesOfB), std::end(edgesOfB), Comparator(0.6f)) != std::end(edgesOfB));

    auto edgesOfC = graph.getEdges(2u);
    REQUIRE(std::find_if(std::begin(edgesOfC), std::end(edgesOfC), Comparator(0.6f)) != std::end(edgesOfC));
}