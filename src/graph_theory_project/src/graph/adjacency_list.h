#ifndef GRAPH_THEORY_PROJECT_ADJACENCY_LIST_H
#define GRAPH_THEORY_PROJECT_ADJACENCY_LIST_H

#include <vector>
#include <utility>
#include <cassert>

namespace graph
{
using VertexDescriptor = size_t;
using EdgeDescriptor = size_t;

template<typename TVertexData, typename TEdgeData>
class AdjacencyList
{
public:
    explicit AdjacencyList(size_t vertexCount) noexcept;

    VertexDescriptor addVertex(TVertexData&& vertexData, size_t edgeCount);
    EdgeDescriptor addEdge(VertexDescriptor vertex, TEdgeData&& edgeData);

    TVertexData& getVertex(VertexDescriptor vertex);
    const TVertexData& getVertex(VertexDescriptor vertex) const;

    TEdgeData& getEdge(VertexDescriptor vertex, EdgeDescriptor edge);
    const TEdgeData& getEdge(VertexDescriptor vertex, EdgeDescriptor edge) const;

    [[nodiscard]] size_t size() const noexcept;
    [[nodiscard]] size_t size(VertexDescriptor vertex) const noexcept;

private:
    std::vector<std::pair<TVertexData, std::vector<TEdgeData>>> m_vertices;
};

template<typename TVertexData, typename TEdgeData>
AdjacencyList<TVertexData, TEdgeData>::AdjacencyList(size_t vertexCount) noexcept
{
    m_vertices.reserve(vertexCount);
}

template<typename TVertexData, typename TEdgeData>
VertexDescriptor AdjacencyList<TVertexData, TEdgeData>::addVertex(TVertexData&& vertexData, size_t edgeCount)
{
    auto&& vertex = m_vertices.emplace_back(std::move(vertexData), {});
    vertex.second.reserve(edgeCount);

    return m_vertices.size() - 1;
}

template<typename TVertexData, typename TEdgeData>
EdgeDescriptor AdjacencyList<TVertexData, TEdgeData>::addEdge(VertexDescriptor vertex, TEdgeData&& edgeData)
{
    assert(vertex >= 0 && vertex < m_vertices.size());
    m_vertices[vertex].second.emplace_back(std::move(edgeData));

    return m_vertices[vertex].second.size() - 1;
}

template<typename TVertexData, typename TEdgeData>
TVertexData& AdjacencyList<TVertexData, TEdgeData>::getVertex(VertexDescriptor vertex)
{
    assert(vertex >= 0 && vertex < m_vertices.size());
    return m_vertices[vertex].first;
}

template<typename TVertexData, typename TEdgeData>
const TVertexData& AdjacencyList<TVertexData, TEdgeData>::getVertex(VertexDescriptor vertex) const
{
    assert(vertex >= 0 && vertex < m_vertices.size());
    return m_vertices[vertex].first;
}

template<typename TVertexData, typename TEdgeData>
TEdgeData& AdjacencyList<TVertexData, TEdgeData>::getEdge(VertexDescriptor vertex, EdgeDescriptor edge)
{
    assert(vertex >= 0 && vertex < m_vertices.size());
    assert(edge >= 0 && edge < m_vertices[vertex].second.size());

    return m_vertices[vertex].second[edge];
}

template<typename TVertexData, typename TEdgeData>
const TEdgeData& AdjacencyList<TVertexData, TEdgeData>::getEdge(VertexDescriptor vertex, EdgeDescriptor edge) const
{
    assert(vertex >= 0 && vertex < m_vertices.size());
    assert(edge >= 0 && edge < m_vertices[vertex].second.size());

    return m_vertices[vertex].second[edge];
}

template<typename TVertexData, typename TEdgeData>
size_t AdjacencyList<TVertexData, TEdgeData>::size() const noexcept
{
    return m_vertices.size();
}

template<typename TVertexData, typename TEdgeData>
size_t AdjacencyList<TVertexData, TEdgeData>::size(VertexDescriptor vertex) const noexcept
{
    assert(vertex >= 0 && vertex < m_vertices.size());
    return m_vertices[vertex].second.size();
}

}  // namespace graph

#endif  // GRAPH_THEORY_PROJECT_ADJACENCY_LIST_H
