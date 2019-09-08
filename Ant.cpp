#include "Ant.hpp"
#include "Helper.hpp"

#include <deque>
#include <numeric>

namespace SBH
{
    Ant::Ant(std::shared_ptr<DnaGraph>& graph)
        : m_graph(graph)
    {
        m_visited.resize(m_graph->GetGraphSize());
        auto [vBegin, vEnd] {m_graph->GetVertexIterators()};
        auto maxElement = std::max_element(vBegin, vEnd, [&](auto a, auto b)
        {
            return (m_graph->GetAmountOfOutEdges(a) < m_graph->GetAmountOfOutEdges(b));
        });
        m_distribution.resize(m_graph->GetAmountOfOutEdges(*maxElement));
    }

    double Ant::ComputeNumerator(DnaGraph::ed const& edge)
    {
        auto pheromoneLevel = m_graph->GetEdge(edge).GetPheromoneLevel();
        auto weight = m_graph->GetEdge(edge).GetWeight();
        double numerator = std::pow(pheromoneLevel, settings::ALPHA) * 
            std::pow(weight, settings::BETA);
        return m_visited[m_graph->GetSourceVertex(edge)] ? 
            numerator * settings::VISITED_MULTIPLY : numerator;
    }

    void Ant::FillDistribution(DnaGraph::vd position)
    {
        double rhs {0.0};
        Distribution::iterator distIt = m_distribution.begin();
        auto edgesIterators = m_graph->GetOutEdges(position);
        m_distributionSize = m_graph->GetAmountOfOutEdges(position);
        for(auto const& edge : boost::make_iterator_range(edgesIterators))
        {
            double lhs {rhs};
            rhs += ComputeNumerator(edge);
            auto distElement = std::make_tuple(lhs, rhs, edge);
            *distIt = distElement;
            distIt++;
        }

        for(std::size_t i = 0; i < m_distributionSize; i++)
        {
            auto& [first, second, edge] = m_distribution[i];
            first /= rhs;
            second /= rhs;
        }
    }

    DnaGraph::ed Ant::DrawNextEdge()
    {
        std::size_t lower {0};
        std::size_t upper {m_distributionSize - 1};
        auto generatedNumber {helper::GenerateRandomNumber<double>(0,1)};

        while(true)
        {
            std::size_t mid = lower + (upper - lower) / 2;
            auto& [lhs, rhs, edge] = m_distribution[mid];
            if(lhs < generatedNumber)
            {
                lower = mid + 1;
            }

            if(lhs > generatedNumber)
            {
                upper = mid - 1;
            }

            if(lhs < generatedNumber && generatedNumber <= rhs)
            {
                return edge;
            }
        }
    }

    void Ant::UpdatePheromones(DnaGraph::ed edge)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        (*m_graph)[edge].UpdatePheromones(settings::Q);
    }

    void Ant::FindPath()
    {
        auto position = m_graph->GetFirstOligonucleotide();
        std::string firstOligonucleotide = std::string((*m_graph)[position]);
        dna.Append(std::move(firstOligonucleotide));
        while (dna.GetDnaSize() < m_graph->GetDnaSize())
        {
            m_visited[position] = true;
            FillDistribution(position);
            auto edge {DrawNextEdge()};
            UpdatePheromones(edge);
            dna.Append(std::move(std::string((*m_graph)[edge].GetName())));
            position = m_graph->GetTargetVertex(edge);
        }
        std::cout << dna;
        std::cout << "\n";
    }
}