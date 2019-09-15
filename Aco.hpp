#ifndef THREADPOOL_HPP
#define THREADPOOL_HPP

#include "Ant.hpp"
#include "DnaGraph.hpp"

#include <thread>
#include <condition_variable>
#include <atomic>


namespace SBH
{
    class Aco 
    {
        public:
            explicit Aco(std::shared_ptr<DnaGraph>& graph);
            ~Aco();
            void Start();
            void DisplayGeneratedDna();
            void Stop() noexcept;
            

        private:
            using result = std::pair<std::string, std::size_t>;
            std::mutex m_mutex;
            std::condition_variable m_eventVariable;
            std::condition_variable m_continue;
            std::vector<std::thread> m_threads;
            std::vector<Ant> m_ants;
            std::size_t findPathCounter {0};
            bool m_synchronize {false};
            bool m_break {false};
            std::size_t m_generationCount {0};
            std::shared_ptr<DnaGraph> m_graph;
            std::vector<Dna> synchronizedDna; 
            std::size_t m_bestResult {0};
            std::list<result> m_resultsList;

            void CreateAnts(std::size_t numbAnts);
            void RunAnt(Ant &);
            void SynchronizeAnts();
            void UpdateResults();

    };
}


#endif /* THREADPOOL_HPP */