#ifndef GRAPH_THEORY_PROJECT_ALGORITHMS_H
#define GRAPH_THEORY_PROJECT_ALGORITHMS_H

#include <graph/adjacency_list.h>

namespace graph
{
template<typename TVertexData, typename TEdgeData, typename UnaryPredicate>
void removeEdgesKeepNIf(AdjacencyList<TVertexData, TEdgeData>& graph, size_t keep, UnaryPredicate p)
{
    std::vector<std::pair<std::pair<VertexDescriptor, VertexDescriptor>, TEdgeData>> whiteList;

    whiteList.reserve(graph.size() * keep);

    for (auto i = 0u; i < graph.size(); ++i)
    {
        graph.sortEdges(i, p);

        const auto edges = graph.size(i);

        for (auto j = 0u; j < (keep > edges ? edges : keep); ++j)
        {
            auto&& edge = graph.getEdgeById(i, j);
            whiteList.emplace_back(std::make_pair(i, edge.first), std::move(edge.second));
        }
    }

    graph.clearEdges();

    for (auto&& edge : whiteList)
        graph.addEdge(edge.first.first, edge.first.second, std::move(edge.second));
}

}  // namespace graph

#endif  // GRAPH_THEORY_PROJECT_ALGORITHMS_H
