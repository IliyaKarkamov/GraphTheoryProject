#include <graph/adjacency_list.h>
#include <graph/csv_io.h>
#include <graph/xml_io.h>
#include <graph/algorithms.h>
#include <iostream>
#include <chrono>
#include <cmath>

int main()
{
    using namespace graph;

    AdjacencyList<std::string, float> graph;

    std::ifstream ifs(R"(D:\Projects\University\GraphTheoryProject\docs\mtx_correl_log_ret.csv)");
    ifs >> graph;
    ifs.close();

    auto begin = std::chrono::high_resolution_clock::now();

    removeEdgesKeepNIf(graph, 3, [](float lhs, float rhs) { return std::fabs(lhs) > std::fabs(rhs); });

    auto end = std::chrono::high_resolution_clock::now();
    auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);

    std::ofstream ofs(R"(D:\Projects\University\GraphTheoryProject\docs\output.gexf)");
    ofs << graph;
    ofs.close();

    std::cout << microseconds.count() << " microseconds" << std::endl;

    return 0;
}