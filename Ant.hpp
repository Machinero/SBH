#ifndef ANT_HPP
#define ANT_HPP
#include <memory>
#include <deque>
#include <mutex>

#include "DnaGraph.hpp"

namespace SBH
{
    class Ant
    {
        public:
            explicit Ant(std::shared_ptr<DnaGraph>& graph);
            void FindPath();
        private:
            using Distribution = std::vector<std::tuple<double, double, DnaGraph::ed>>;
            DnaGraph::ed m_lastVisitedVertex;
            std::size_t m_distributionSize;
            std::vector<bool> m_visited;
            Dna dna;
            Distribution m_distribution;
            std::shared_ptr<DnaGraph> m_graph;
            std::mutex m_mutex;

            DnaGraph::vd NextVertex(DnaGraph::vd position);
            void UpdatePheromones(DnaGraph::ed edge);
            double ComputeNumerator(DnaGraph::ed const& edge);
            void FillDistribution(DnaGraph::vd position);
            DnaGraph::ed DrawNextEdge();

    };
}

#endif /* ANT_HPP */