#include <chrono>

// based on https://www.youtube.com/watch?v=GV0JMHOpoEw
template<typename T = std::chrono::milliseconds> 
class Timer
{
    public:
        using Clock = std::conditional_t<std::chrono::high_resolution_clock::is_steady,
                                        std::chrono::high_resolution_clock,
                                        std::chrono::steady_clock>;
        Timer() = default;
        ~Timer()
        {
            Stop();
            DisplayElapsedTime();
        }

    private:
        Clock::time_point m_start = Clock::now();
        Clock::time_point m_end;

        void Stop()
        {
            m_end = Clock::now();
        }    

        void DisplayElapsedTime()
        {
            std::chrono::duration<double> duration = m_end - m_start;
            std::cout   
                    << "Elapsed " 
                    << std::chrono::duration_cast<T>(duration).count() 
                    << std::endl;
        }
};