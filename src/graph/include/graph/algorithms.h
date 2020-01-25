#ifndef GRAPH_THEORY_PROJECT_ALGORITHMS_H
#define GRAPH_THEORY_PROJECT_ALGORITHMS_H

#include <graph/adjacency_list.h>
#include <graph/disjoint_set.h>

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

template<typename TVertexData, typename TEdgeData, typename UnaryPredicate>
void kruskalSpanningTree(AdjacencyList<TVertexData, TEdgeData>& graph, UnaryPredicate p)
{
    auto edges = graph.getEdges();

    std::sort(edges.begin(), edges.end(), p);

    decltype(edges) spanningTree;

    const auto verticesCount = graph.size();
    spanningTree.reserve(verticesCount - 1);

    DisjointSet<VertexDescriptor> disjointSet(verticesCount);

    for (auto&& [v, w] : edges)
    {
        if (spanningTree.size() == verticesCount - 1)
            break;

        const auto x = disjointSet.find(v.first);
        const auto y = disjointSet.find(v.second);

        if (x != y)
        {
            spanningTree.emplace_back(v, w);
            disjointSet.merge(x, y);
        }
    }

    graph.clearEdges();

    for (auto&& [v, w] : spanningTree)
        graph.addEdge(v.first, v.second, w);
}

}  // namespace graph

#endif  // GRAPH_THEORY_PROJECT_ALGORITHMS_H
