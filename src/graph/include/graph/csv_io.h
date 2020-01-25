#ifndef GRAPH_THEORY_PROJECT_CSV_IO_H
#define GRAPH_THEORY_PROJECT_CSV_IO_H

#include <graph/adjacency_list.h>
#include <csv-parser/parser.hpp>
#include <istream>
#include <sstream>

namespace graph
{
namespace detail
{
template<typename T>
T lexical_cast(const std::string& s)
{
    std::stringstream ss(s);

    T value;
    ss >> value;

    return std::move(value);
}
}  // namespace detail

template<typename TVertexData, typename TEdgeData>
std::istream& operator>>(std::istream& is, AdjacencyList<TVertexData, TEdgeData>& graph)
{
    using namespace aria::csv;

    CsvParser parser(is);

    auto&& rowIt = parser.begin();

    const auto size = rowIt->size() - 1;

    graph.reserve(size);

    for (auto&& fieldIt = rowIt->begin() + 1; fieldIt != rowIt->end(); ++fieldIt)
        graph.addVertex(detail::lexical_cast<TVertexData>(*fieldIt), size);

    ++rowIt;

    for (auto i = 0u; rowIt != parser.end(); ++rowIt, ++i)
    {
        auto&& row = *rowIt;
        auto j = i + 1;

        for (auto&& fieldIt = row.begin() + i + 2u; fieldIt != row.end(); ++fieldIt, ++j)
        {
            const auto weight = detail::lexical_cast<TEdgeData>(*fieldIt);

            if (weight < 0.0001f)
                continue;

            graph.addEdge(i, j, weight);
        }
    }

    return is;
}

}  // namespace graph

#endif  // GRAPH_THEORY_PROJECT_CSV_IO_H
