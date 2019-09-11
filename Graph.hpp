#ifndef DNAGRAPH_H
#define DNAGRAPH_H

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/profile.hpp>

namespace SBH
{
    template <
        typename VertexType, 
        typename EdgeType,
        typename EdgeContainer = boost::vecS, 
        typename VertexContainer = boost::vecS, 
        typename GraphType = boost::directedS>
    class Graph
    {
        public:
            using GraphStructure =   boost::adjacency_list<
                            EdgeContainer,
                            VertexContainer,
                            GraphType,
                            VertexType,
                            EdgeType>;
            using vd = typename boost::graph_traits<GraphStructure>::vertex_descriptor;
            using ed = typename boost::graph_traits<GraphStructure>::edge_descriptor;
            using vi = typename boost::graph_traits<GraphStructure>::vertex_iterator;
            using ei = typename boost::graph_traits<GraphStructure>::edge_iterator;

            Graph() = default;
            EdgeType GetEdge(ed index) const
            {
                return m_graph[index];
            }
            VertexType GetVertex(vd index) const
            {
                return m_graph[index];
            }

            auto GetOutEdges(vd index) const 
            {
                return out_edges(index, m_graph);
            }
            
            auto GetVertexIterators() const
            {
                return vertices(m_graph);
            }

            auto GetAmountOfOutEdges(vd index) const
            {
                return boost::out_degree(index, m_graph);
            }
            auto GetGraphSize() const
            {
                return boost::num_vertices(m_graph);
            }

            auto GetAdjacentVertices(vd index) const
            {
                return boost::adjacent_vertices(index, m_graph);
            }

            auto GetSourceVertex(ed index) const
            {
                return source(index, m_graph);
            }

            auto GetTargetVertex(ed index) const
            {
                return target(index, m_graph);
            }

            auto GetEdgesIterators()
            {
                return edges(m_graph);
            }

            EdgeType & operator [] (ed const& index)
            {
                return m_graph[index];
            }

            VertexType & operator [] (vd const& index)
            {
                return m_graph[index];
            }

            auto AddEdge(vd firstVertex, vd secondVertex, EdgeType&& edge)
            {
                return boost::add_edge(firstVertex, secondVertex, std::forward<EdgeType>(edge), m_graph);
            }

            auto AddVertex(VertexType&& vertex)
            {
                return boost::add_vertex(std::forward<VertexType>(vertex), m_graph);
            }

        protected:
            GraphStructure m_graph;
    };
} // namespace SBH

#endif /* DNAGRAPH_H */