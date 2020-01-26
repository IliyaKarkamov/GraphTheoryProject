#include <graph/graph.h>
#include <iostream>
#include <chrono>
#include <cmath>
#include <future>

using namespace graph;

AdjacencyList<std::string, float> processData(const std::string& inputFile, const std::string& outputFile)
{
    AdjacencyList<std::string, float> graph;

    std::ifstream ifs(inputFile);
    ifs >> graph;
    ifs.close();

    sieveEdgesIf(graph, 3, [](float lhs, float rhs) { return std::fabs(lhs) > std::fabs(rhs); });

    std::ofstream ofs(outputFile);
    ofs << graph;
    ofs.close();

    return std::move(graph);
}

void processGraph(AdjacencyList<std::string, float>& graph, const std::string& outputFile)
{
    kruskalSpanningTree(graph, [](const auto& lhs, const auto& rhs) { return lhs.second > rhs.second; });

    std::ofstream ofs(outputFile);
    ofs << graph;
    ofs.close();
}

int main()
{
    const auto begin = std::chrono::high_resolution_clock::now();

    auto future = std::async(std::launch::async, []() {
        auto graph = processData("mtx_correl_log_ret.csv", "log_returns_with_max_weight.gexf");
        processGraph(graph, "log_returns_maximum_spanning_tree.gexf");
    });

    auto graph = processData("mtx_correl_ewm_vol.csv", "vol_with_max_weight.gexf");
    processGraph(graph, "vol_maximum_spanning_tree.gexf");

    future.get();

    const auto end = std::chrono::high_resolution_clock::now();
    const auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

    std::cout << milliseconds.count() << " milliseconds" << std::endl;
    std::cin.get();

    return 0;
}