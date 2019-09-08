#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <string_view>

namespace SBH
{

    namespace settings
    {
        inline static constexpr double STARTING_PHEROMONES = 1.0;
        inline static constexpr double START_PHEROMONES = 1.0;
        inline static constexpr std::size_t ALPHA = 2;
        inline static constexpr std::size_t BETA = 5;
        inline static constexpr double Q = 10;
        inline static constexpr double VISITED_MULTIPLY = 0.5; 
        inline static constexpr double EVAPORATE = 0.5;
        inline static constexpr std::size_t NUMBER_OF_ANTS = 30; 
    }
    
    namespace messages
    {
    }
}

#endif /* SETTINGS_HPP */