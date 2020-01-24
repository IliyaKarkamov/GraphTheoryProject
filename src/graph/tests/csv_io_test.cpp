#include <catch2/catch.hpp>

#include <graph/adjacency_list.h>
#include <graph/csv_io.h>

TEST_CASE("koko")
{
    using namespace graph;

    AdjacencyList<std::string, float> graph(3);

    REQUIRE(1 == 1);
}