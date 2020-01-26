#ifndef GRAPH_THEORY_PROJECT_ADJACENCY_LIST_H
#define GRAPH_THEORY_PROJECT_ADJACENCY_LIST_H

#include <vector>
#include <utility>
#include <cassert>
#include <algorithm>
#include <cmath>

namespace graph
{
using VertexDescriptor = size_t;
using EdgeDescriptor = size_t;

template<typename TVertexData, typename TEdgeData>
class AdjacencyList
{
public:
    explicit AdjacencyList() noexcept = default;
    explicit AdjacencyList(size_t vertexCount) noexcept;

    void reserve(size_t vertexCount);
    void reserve(VertexDescriptor vertex, size_t edgeCount);

    [[nodiscard]] size_t size() const noexcept;
    [[nodiscard]] size_t size(VertexDescriptor vertex) const noexcept;
    [[nodiscard]] size_t sizeOfEdges() const noexcept;

    VertexDescriptor addVertex(TVertexData vertexData);
    VertexDescriptor addVertex(TVertexData vertexData, size_t edgeCount);

    EdgeDescriptor addEdge(VertexDescriptor src, VertexDescriptor dest, TEdgeData edgeData);

    TVertexData& getVertex(VertexDescriptor vertex);
    const TVertexData& getVertex(VertexDescriptor vertex) const;

    TEdgeData& getEdge(VertexDescriptor src, VertexDescriptor dest);
    const TEdgeData& getEdge(VertexDescriptor src, VertexDescriptor dest) const;

    std::pair<VertexDescriptor, TEdgeData> getEdgeById(VertexDescriptor vertex, EdgeDescriptor edge) const;

    std::vector<std::pair<std::pair<VertexDescriptor, VertexDescriptor>, TEdgeData>> getEdges() const;
    std::vector<std::pair<VertexDescriptor, TEdgeData>> getEdges(VertexDescriptor vertex) const;

    template<typename UnaryPredicate>
    void sortEdges(VertexDescriptor vertex, UnaryPredicate p);

    void clear();
    void clearEdges();

private:
    struct Edge
    {
        TEdgeData edgeData;
        VertexDescriptor vertex;

        Edge(TEdgeData edgeData, VertexDescriptor vertex) : edgeData(std::move(edgeData)), vertex(vertex) {}
    };

    struct Vertex
    {
        TVertexData vertexData;
        std::vector<Edge> edges;

        Vertex(TVertexData vertexData, std::vector<Edge> edges) : vertexData(std::move(vertexData)), edges(std::move(edges)) {}
    };

    std::vector<Vertex> m_vertices;
};

template<typename TVertexData, typename TEdgeData>
AdjacencyList<TVertexData, TEdgeData>::AdjacencyList(size_t vertexCount) noexcept
{
    m_vertices.reserve(vertexCount);
}

template<typename TVertexData, typename TEdgeData>
void AdjacencyList<TVertexData, TEdgeData>::reserve(size_t vertexCount)
{
    m_vertices.reserve(vertexCount);
}

template<typename TVertexData, typename TEdgeData>
void AdjacencyList<TVertexData, TEdgeData>::reserve(VertexDescriptor vertex, size_t edgeCount)
{
    assert(vertex >= 0 && vertex < m_vertices.size());
    m_vertices[vertex].reserve(edgeCount);
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
    return m_vertices[vertex].edges.size();
}

template<typename TVertexData, typename TEdgeData>
size_t AdjacencyList<TVertexData, TEdgeData>::sizeOfEdges() const noexcept
{
    size_t size = 0u;

    for (auto&& vertex : m_vertices)
        size += vertex.edges.size();

    return size;
}

template<typename TVertexData, typename TEdgeData>
VertexDescriptor AdjacencyList<TVertexData, TEdgeData>::addVertex(TVertexData vertexData, size_t edgeCount)
{
    auto& vertex = m_vertices.emplace_back(std::move(vertexData), std::vector<Edge>());
    vertex.edges.reserve(edgeCount);

    return m_vertices.size() - 1;
}

template<typename TVertexData, typename TEdgeData>
VertexDescriptor AdjacencyList<TVertexData, TEdgeData>::addVertex(TVertexData vertexData)
{
    m_vertices.emplace_back(std::move(vertexData), std::vector<Edge>());
    return m_vertices.size() - 1;
}

template<typename TVertexData, typename TEdgeData>
EdgeDescriptor AdjacencyList<TVertexData, TEdgeData>::addEdge(VertexDescriptor src, VertexDescriptor dest, TEdgeData edgeData)
{
    assert(src >= 0 && src < m_vertices.size());
    assert(dest >= 0 && dest < m_vertices.size());

    m_vertices[src].edges.emplace_back(edgeData, dest);
    m_vertices[dest].edges.emplace_back(std::move(edgeData), src);

    return m_vertices[src].edges.size() - 1;
}

template<typename TVertexData, typename TEdgeData>
TVertexData& AdjacencyList<TVertexData, TEdgeData>::getVertex(VertexDescriptor vertex)
{
    assert(vertex >= 0 && vertex < m_vertices.size());
    return m_vertices[vertex].vertexData;
}

template<typename TVertexData, typename TEdgeData>
const TVertexData& AdjacencyList<TVertexData, TEdgeData>::getVertex(VertexDescriptor vertex) const
{
    assert(vertex >= 0 && vertex < m_vertices.size());
    return m_vertices[vertex].vertexData;
}

template<typename TVertexData, typename TEdgeData>
TEdgeData& AdjacencyList<TVertexData, TEdgeData>::getEdge(VertexDescriptor src, VertexDescriptor dest)
{
    assert(src >= 0 && src < m_vertices.size());
    assert(dest >= 0 && dest < m_vertices.size());

    auto& edges = m_vertices[src].edges;
    const auto it = std::find_if(std::begin(edges), std::end(edges), [dest](const Edge& edge) { return edge.vertex == dest; });

    assert(it != edges.end());

    return (*it).edgeData;
}

template<typename TVertexData, typename TEdgeData>
const TEdgeData& AdjacencyList<TVertexData, TEdgeData>::getEdge(VertexDescriptor src, VertexDescriptor dest) const
{
    assert(src >= 0 && src < m_vertices.size());
    assert(dest >= 0 && dest < m_vertices.size());

    const auto& edges = m_vertices[src].edges;
    const auto it = std::find_if(std::cbegin(edges), std::cend(edges), [dest](const Edge& edge) { return edge.vertex == dest; });

    assert(it != edges.end());

    return (*it).edgeData;
}

template<typename TVertexData, typename TEdgeData>
std::pair<VertexDescriptor, TEdgeData> AdjacencyList<TVertexData, TEdgeData>::getEdgeById(VertexDescriptor vertex,
                                                                                          EdgeDescriptor edge) const
{
    assert(vertex >= 0 && vertex < m_vertices.size());
    assert(edge >= 0 && edge < m_vertices[vertex].edges.size());

    const auto& e = m_vertices[vertex].edges[edge];

    return std::make_pair(e.vertex, e.edgeData);
}

template<typename TVertexData, typename TEdgeData>
std::vector<std::pair<std::pair<VertexDescriptor, VertexDescriptor>, TEdgeData>> AdjacencyList<TVertexData, TEdgeData>::getEdges()
    const
{
    std::vector<std::pair<std::pair<VertexDescriptor, VertexDescriptor>, TEdgeData>> allEdges;
    allEdges.reserve(m_vertices.size() * m_vertices.size());

    for (auto i = 0u; i < m_vertices.size(); ++i)
    {
        const auto& edges = m_vertices[i].edges;

        for (auto j = 0u; j < edges.size(); ++j)
            allEdges.emplace_back(std::make_pair(i, edges[j].vertex), edges[j].edgeData);
    }

    return std::move(allEdges);
}

template<typename TVertexData, typename TEdgeData>
std::vector<std::pair<VertexDescriptor, TEdgeData>> AdjacencyList<TVertexData, TEdgeData>::getEdges(VertexDescriptor vertex) const
{
    assert(vertex >= 0 && vertex < m_vertices.size());

    const auto& edges = m_vertices[vertex].edges;

    std::vector<std::pair<VertexDescriptor, TEdgeData>> resultEdges;
    resultEdges.reserve(edges.size());

    std::for_each(
        std::begin(edges), std::end(edges), [&resultEdges](const auto& e) { resultEdges.emplace_back(e.vertex, e.edgeData); });

    return std::move(resultEdges);
}

template<typename TVertexData, typename TEdgeData>
template<typename UnaryPredicate>
void AdjacencyList<TVertexData, TEdgeData>::sortEdges(VertexDescriptor vertex, UnaryPredicate p)
{
    assert(vertex >= 0 && vertex < m_vertices.size());

    auto& edges = m_vertices[vertex].edges;

    std::sort(
        std::begin(edges), std::end(edges), [&p](const Edge& lhs, const Edge& rhs) { return p(lhs.edgeData, rhs.edgeData); });
}

template<typename TVertexData, typename TEdgeData>
void AdjacencyList<TVertexData, TEdgeData>::clear()
{
    m_vertices.clear();
}

template<typename TVertexData, typename TEdgeData>
void AdjacencyList<TVertexData, TEdgeData>::clearEdges()
{
    std::for_each(std::begin(m_vertices), std::end(m_vertices), [](Vertex& vertex) { vertex.edges.clear(); });
}

template<typename TEdgeData>
class EdgeComparator
{
    VertexDescriptor v1, v2;
    TEdgeData w;

public:
    EdgeComparator(VertexDescriptor v1, VertexDescriptor v2, TEdgeData w) : v1(v1), v2(v2), w(std::move(w)) {}

    bool operator()(const std::pair<std::pair<VertexDescriptor, VertexDescriptor>, TEdgeData>& edge)
    {
        return (edge.first.first + edge.first.second == v1 + v2) && (std::fabs(edge.second - w) < 0.0001f);
    }
};

}  // namespace graph

#endif  // GRAPH_THEORY_PROJECT_ADJACENCY_LIST_H