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

    Ant::Ant(Ant const& ant)
    {
        this->m_distributionSize = ant.m_distributionSize;
        this->m_distribution = ant.m_distribution;
        this->m_visited = ant.m_visited;
        this->m_dna = ant.m_dna;
        this->m_graph = ant.m_graph;
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
            double lhs = rhs;
            rhs += ComputeNumerator(edge);
            auto& [a, b, c] = *distIt;
            a = lhs; b = rhs; c = edge;
            distIt++;
        }

        for(std::size_t i = 0; i < m_distributionSize; i++)
        {
            auto& [first, second, edge] = m_distribution[i];
            first /= rhs;
            second /= rhs;
        }
        if(m_distributionSize == 0)
        {
            std::cout << "";
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
        m_dna = std::move(firstOligonucleotide);
        while (m_dna.size() < m_graph->GetDnaSize())
        {
            m_visited[position] = true;
            FillDistribution(position);
            auto edge {DrawNextEdge()};
            UpdatePheromones(edge);
            std::string diff(m_graph->GetEdge(edge).GetName());
            m_dna += std::move(diff);
            m_count++;
            position = m_graph->GetTargetVertex(edge);
        }
    }

    std::string Ant::GetGeneratedDna() const
    {
        return m_dna;
    }

    std::size_t Ant::GetCount() const
    {
        return m_count;
    }

    void Ant::ResetCounter()
    {
        m_count = 1;
    }
}