#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <string_view>

namespace SBH
{

    namespace settings
    {
        inline static constexpr double STARTING_PHEROMONES = 0.5;
        inline static constexpr double MINIMAL_PHEROMONES = 0.5;
        inline static constexpr double Q = 0.1; 
        inline static constexpr double VISITED_MULTIPLY = 0.59; 
        inline static constexpr double EVAPORATE = 0.9;
        inline static constexpr std::size_t ALPHA = 2;
        inline static constexpr std::size_t BETA = 40; 
        inline static constexpr std::size_t NUMBER_OF_ANTS = 30;
        inline static constexpr std::size_t NUMBER_OF_GENERATIONS = 1000; 
        inline static constexpr std::size_t OLIGONUCLEOTIDE_SIZE = 10;
        inline static constexpr std::size_t SMOOTH_RATIO = 8;
    }
}

#endif /* SETTINGS_HPP */