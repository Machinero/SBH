#include "Aco.hpp"

namespace SBH
{

    Aco::Aco(std::shared_ptr<DnaGraph>& graph)
        : m_graph(graph)
    {
        CreateAnts(settings::NUMBER_OF_ANTS);
        Start();
    }

    Aco::~Aco()
    {
        Stop();
        DisplayGeneratedDna();
    }

    void Aco::Start()
    {
        for(auto i = 0U; i < settings::NUMBER_OF_ANTS; i++)
        {
             m_threads.emplace_back(&Aco::RunAnt, this, std::ref(m_ants[i]));
        }
        m_threads.emplace_back(&Aco::SynchronizeAnts,this);
    }

    void Aco::CreateAnts(std::size_t numAnts)
    {
        for(auto i = 0U; i < numAnts; i++)
        {
            m_ants.emplace_back(std::move(Ant(m_graph)));
        }
    }

    void Aco::RunAnt(Ant & ant)
    {
        while(true)
        {
            ant.ResetCounter();
            ant.FindPath();
            {
                std::lock_guard<std::mutex> lock(m_mutex);
                findPathCounter++;
                if(findPathCounter == settings::NUMBER_OF_ANTS)
                {
                    m_synchronize = false;
                    m_eventVariable.notify_all();
                }
            }
            {
                std::unique_lock<std::mutex> lock(m_mutex);
                m_eventVariable.wait(lock, [=] { return m_synchronize || m_break; } );
                if(m_break)
                {
                    break;
                }
            }
        }
    }

    void Aco::SynchronizeAnts()
    {
        auto [edgesBegin, edgesEnd] = m_graph->GetEdgesIterators();
        while(true)
        {
            {
                std::unique_lock<std::mutex> lock(m_mutex);
                m_eventVariable.wait(lock, [=] { return !m_synchronize;});
                m_graph->EvaporateAllEdges(settings::EVAPORATE, settings::MINIMAL_PHEROMONES, settings::SMOOTH_RATIO);
                UpdateResults();
                if(m_generationCount >= settings::NUMBER_OF_GENERATIONS)
                {
                    m_break = true;
                    m_synchronize = false;
                    m_eventVariable.notify_all();
                    break;
                }
                m_synchronize = true;
                findPathCounter = 0;
                m_generationCount++;
            }
            m_eventVariable.notify_all();

        }
    }

    void Aco::Stop() noexcept
    {
        for(auto & thread : m_threads)
        {
            thread.join();
        }
    }

    void Aco::UpdateResults()
    {
        for(auto& ant : m_ants)
        {
            auto count = ant.GetCount();
            auto dna = ant.GetGeneratedDna();
            if(count >= m_bestResult)
            {
                m_resultsList.emplace_back(dna,count);
                m_bestResult = count;
            }
        }
    }

    void Aco::DisplayGeneratedDna()
    {
        m_resultsList.sort();
        m_resultsList.unique();
        auto amount = std::count_if(m_resultsList.begin(), m_resultsList.end(), [&](auto el)
        {
            return el.second == m_bestResult;
        });
        std::cout << "Visited of best vertices " << amount << '\n';
        for(auto& [dna, count] : m_resultsList)
        {
            if(count == m_bestResult)
            {
                std::cout 
                    << "Best result " 
                    << m_graph->Score(dna) << ' '
                    << count << " " << dna << '\n';
            }
        }
    }

}
