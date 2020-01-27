#ifndef GRAPH_THEORY_PROJECT_XML_IO_H
#define GRAPH_THEORY_PROJECT_XML_IO_H

#include <graph/adjacency_list.h>
#include <tinyxml2/tinyxml2.h>
#include <ostream>

namespace graph
{
template<typename TVertexData, typename TEdgeData>
std::ostream& operator<<(std::ostream& os, const AdjacencyList<TVertexData, TEdgeData>& graph)
{
    using namespace tinyxml2;

    XMLDocument doc;

    doc.InsertFirstChild(doc.NewElement("gexf"));

    auto root = doc.RootElement();

    root->SetAttribute("xmlns", "http://www.gexf.net/1.3");
    root->SetAttribute("version", "1.3");
    root->SetAttribute("xmlns:viz", "http://www.gexf.net/1.3/viz");
    root->SetAttribute("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
    root->SetAttribute("xsi:schemaLocation", "http://www.gexf.net/1.3http://www.gexf.net/1.3/gexf.xsd");

    auto graphElement = doc.NewElement("graph");
    root->InsertFirstChild(graphElement);

    graphElement->SetAttribute("defaultedgetype", "undirected");
    graphElement->SetAttribute("mode", "static");

    auto nodesElement = doc.NewElement("nodes");
    graphElement->InsertFirstChild(nodesElement);

    for (auto i = 0; i < graph.size(); ++i)
    {
        auto nodeElement = doc.NewElement("node");
        nodesElement->InsertEndChild(nodeElement);

        nodeElement->SetAttribute("id", i);
        nodeElement->SetAttribute("label", graph.getVertex(i).c_str());  // todo this may not be std::string!
    }

    auto edgesElement = doc.NewElement("edges");
    graphElement->InsertEndChild(edgesElement);

    auto id = 0u;

    std::vector<std::pair<std::pair<VertexDescriptor, VertexDescriptor>, TEdgeData>> exported;
    exported.reserve(graph.sizeOfEdges());

    for (auto i = 0u; i < graph.size(); ++i)
    {
        for (auto j = 0u; j < graph.size(i); ++j)
        {
            auto&& [v, w] = graph.getEdgeById(i, j);

            if (std::find_if(std::begin(exported), std::end(exported), EdgeComparator<TEdgeData>(i, v)) != std::end(exported))
                continue;

            exported.emplace_back(std::make_pair(i, v), w);

            auto edgeElement = doc.NewElement("edge");
            edgesElement->InsertEndChild(edgeElement);

            const auto strId = std::to_string(id++);
            const auto strSource = std::to_string(i);
            const auto strTarget = std::to_string(v);
            const auto strWeight = std::to_string(w);

            edgeElement->SetAttribute("id", strId.c_str());
            edgeElement->SetAttribute("source", strSource.c_str());
            edgeElement->SetAttribute("target", strTarget.c_str());
            edgeElement->SetAttribute("weight", strWeight.c_str());
        }
    }

    XMLPrinter printer;
    doc.Print(&printer);

    os << printer.CStr();

    return os;
}

}  // namespace graph

#endif  // GRAPH_THEORY_PROJECT_XML_IO_H
