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
            Ant(Ant const& ant);
            Ant(Ant &&) = default;
            void FindPath();
            std::string GetGeneratedDna() const;
            std::size_t GetCount() const;
            void ResetCounter();

        private:
            using Distribution = std::vector<std::tuple<double, double, DnaGraph::ed>>;
            std::size_t m_distributionSize;
            std::vector<bool> m_visited;
            std::string m_dna;
            Distribution m_distribution;
            std::shared_ptr<DnaGraph> m_graph;
            std::mutex m_mutex;
            std::size_t m_count = 1;

            DnaGraph::vd NextVertex(DnaGraph::vd position);
            void UpdatePheromones(DnaGraph::ed edge);
            double ComputeNumerator(DnaGraph::ed const& edge);
            void FillDistribution(DnaGraph::vd position);
            DnaGraph::ed DrawNextEdge();

    };
}

#endif /* ANT_HPP */