#include <graph/adjacency_list.h>
#include <graph/csv_io.h>
#include <graph/xml_io.h>
#include <iostream>
#include <chrono>

int main()
{
    using namespace graph;

    AdjacencyList<std::string, float> graph;

    auto begin = std::chrono::high_resolution_clock::now();

    std::ifstream ifs(R"(D:\Projects\University\GraphTheoryProject\docs\mtx_correl_log_ret.csv)");
    ifs >> graph;

    auto end = std::chrono::high_resolution_clock::now();
    auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);

    std::ofstream ofs(R"(D:\Projects\University\GraphTheoryProject\docs\output.gexf)");
    ofs << graph;
    ofs.close();

    std::cout << microseconds.count() << " microseconds" << std::endl;

    return 0;
}