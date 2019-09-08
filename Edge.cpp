#include "Edge.hpp"

#include <tuple>

namespace SBH 
{
    Edge::Edge(std::string_view name)
        : m_name(std::move(name))
    {
        m_weight = m_name.size();
    }

    std::ostream& operator << (std::ostream& stream, Edge const& edge)
    {
        stream << edge.m_name << ' ' << edge.m_weight << ' ' << edge.m_pheromoneLevel;
        return stream;
    }

    bool operator == (Edge const& rhs, Edge const& lhs)
    {
        return std::tie(rhs.m_weight, rhs.m_pheromoneLevel)
                == std::tie(lhs.m_weight, lhs.m_pheromoneLevel);
    }
    bool operator != (Edge const& rhs, Edge const& lhs)
    {
        return std::tie(rhs.m_weight, rhs.m_pheromoneLevel)
                != std::tie(lhs.m_weight, lhs.m_pheromoneLevel);
    }

    uint16_t const& Edge::GetWeight() const
    {
        return m_weight;
    }

    double const& Edge::GetPheromoneLevel() const
    {
        return m_pheromoneLevel;
    }

    std::string_view const& Edge::GetName() const
    {
        return m_name;
    }

    void Edge::SetWeight(int weight)
    {
        m_weight = weight;
    }

    void Edge::SetPheromoneLevel(double pheromoneLevel)
    {
        m_pheromoneLevel = pheromoneLevel;
    }

    void Edge::SetName(std::string name)
    {
        m_name = std::move(name);
    }

    void Edge::UpdatePheromones(double pheromones)
    {
        m_pheromoneLevel += pheromones;
    }
} // namespace SBH