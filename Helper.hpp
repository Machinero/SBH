#ifndef HELPER_HPP
#define HELPER_HPP

#include <iterator>
#include <thread>
#include <chrono>
#include <random>

namespace helper
{
    template <typename Container>
    auto GetIndex(Container const& container, std::size_t offset = 0)
    {
        return [&container, offset](auto const& iterator)
        {
            return std::distance(std::begin(container), iterator) + offset;
        };
    }

    template <typename T>
    T GenerateRandomNumber(T min, T max)
    {
        thread_local std::random_device rd;
        thread_local std::mt19937 engine(rd() + std::hash<std::thread::id>{}(std::this_thread::get_id()));
        std::uniform_real_distribution<T> dist(min, max);
        return dist(engine);
    }
}



#endif /* HELPER_HPP */