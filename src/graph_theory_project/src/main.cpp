#include <graph/adjacency_list.h>
#include <graph/csv_io.h>
#include <graph/xml_io.h>
#include <graph/algorithms.h>
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

    removeEdgesKeepNIf(graph, 3, [](float lhs, float rhs) { return std::fabs(lhs) > std::fabs(rhs); });

    std::ofstream ofs(outputFile);
    ofs << graph;
    ofs.close();

    return std::move(graph);
}

int main()
{
    const auto begin = std::chrono::high_resolution_clock::now();

    auto future = std::async(std::launch::async, []() {
        auto graph = processData("mtx_correl_log_ret.csv", "log_returns_with_max_weight.gexf");
        //
    });

    auto graph = processData("mtx_correl_ewm_vol.csv", "vol_with_max_weight.gexf");

    future.get();

    const auto end = std::chrono::high_resolution_clock::now();
    const auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);

    std::cout << microseconds.count() << " microseconds" << std::endl;

    return 0;
}