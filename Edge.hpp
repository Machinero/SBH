#ifndef EDGE_HPP
#define EDGE_HPP

#include <iostream>
#include <cstdint>

#include "Settings.hpp"

namespace SBH
{
    class Edge 
    {
        public:
            Edge(std::string_view name, std::size_t size);
            Edge() = default;
            Edge(Edge const&) = default;
            friend std::ostream& operator << (std::ostream& stream, Edge const& edge);
            friend bool operator == (Edge const& rhs, Edge const& lhs);
            friend bool operator != (Edge const& rhs, Edge const& lhs);

            uint16_t const& GetWeight() const;
            double const& GetPheromoneLevel() const;
            std::string_view const& GetName() const;

            void SetWeight(int weight);
            void SetPheromoneLevel(double pheromoneLevel);
            void SetName(std::string name);

            void UpdatePheromones(double pheromones);
            void Evaporate(double evaporationRatio);
            void Evaporate(double evaporationRatio, double minimalPheromones, double smoothRatio);

        private:
            void Smooth(double minimalPheromones, double smoothRatio);

            uint16_t m_weight;
            double m_pheromoneLevel {settings::STARTING_PHEROMONES};
            std::string_view m_name;
    };
}

#endif /* EDGE_HPP */