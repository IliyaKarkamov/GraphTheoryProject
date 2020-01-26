#include <catch2/catch.hpp>

#include <graph/adjacency_list.h>
#include <graph/csv_io.h>
#include <string>
#include <sstream>

TEST_CASE("CSV input basic test")
{
    using namespace graph;

    std::stringstream ss;
    ss << R"("","GOOGLE","MICROSOFT","IBM")" << '\n';
    ss << R"("GOOGLE","1.0","0.8","0.7")" << '\n';
    ss << R"("MICROSOFT","0.8","1.0","0.6")" << '\n';
    ss << R"("IBM","0.7","0.6","1.0")" << '\n';

    AdjacencyList<std::string, float> graph;
    ss >> graph;

    REQUIRE(graph.size() == 3u);

    REQUIRE(graph.size(0u) == 2u);
    REQUIRE(graph.size(1u) == 2u);
    REQUIRE(graph.size(2u) == 2u);

    REQUIRE(graph.getEdgeById(0u, 0u).first == 1u);
    REQUIRE(std::fabs(graph.getEdgeById(0u, 0u).second - 0.8f) < 0.0001f);
}