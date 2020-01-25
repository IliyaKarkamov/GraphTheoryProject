#ifndef GRAPH_THEORY_PROJECT_DISJOINT_SET_H
#define GRAPH_THEORY_PROJECT_DISJOINT_SET_H

#include <vector>

namespace graph
{
template<typename T>
class DisjointSet
{
public:
    explicit DisjointSet(size_t size);

    T find(T element);

    void merge(T a, T b);

private:
    std::vector<T> m_parent;
    std::vector<T> m_rank;
};

template<typename T>
DisjointSet<T>::DisjointSet(size_t size) : m_parent(size), m_rank(size, 0)
{
    for (auto i = 0; i < size; ++i)
        m_parent[i] = i;
}

template<typename T>
T DisjointSet<T>::find(T element)
{
    if (m_parent[element] == element)
        return element;

    m_parent[element] = find(m_parent[element]);

    return m_parent[element];
}

template<typename T>
void DisjointSet<T>::merge(T a, T b)
{
    if (m_parent[a] == m_parent[b])
        return;

    const auto fa = find(a);
    const auto fb = find(b);

    if (m_rank[fa] < m_rank[fb])
        m_parent[fa] = fb;
    else
    {
        m_parent[fb] = fa;

        if (m_rank[fa] == m_rank[fb])
            ++m_rank[fa];
    }
}

}  // namespace graph

#endif  // GRAPH_THEORY_PROJECT_DISJOINT_SET_H
