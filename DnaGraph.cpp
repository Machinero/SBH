#include "DnaGraph.hpp"
#include "Helper.hpp"
#include "DnaGraphException.hpp"

#include <tuple>

namespace SBH
{
    DnaGraph::DnaGraph(std::string nucleotides, int oligonucleotideSize)
        : Dna(std::move(nucleotides)), m_oligonucleotideSize(oligonucleotideSize)
    {
        int loopRange = GetNucleotides().size() - m_oligonucleotideSize;
        std::map<std::string_view, DnaGraph::vd> vertices;
        if(loopRange >= m_oligonucleotideSize)
        {
            for(auto i = 0; i <= loopRange; i++)
            {
                std::string_view nucleotides = GetNucleotides();
                std::string_view substring = nucleotides.substr(i, m_oligonucleotideSize);
                vertices.try_emplace(std::move(substring), i);
                // i == 0 ? m_firstOligoNucleotide == AddVertex(std::move(substring)) : AddVertex(std::move(substring));
            }
            for(auto& [vertex, index] : vertices)
            {
                std::string_view temp = vertex;
                index == 0 ? m_firstOligoNucleotide = AddVertex(std::move(temp)) : AddVertex(std::move(temp)); 
            }
        }
        else
        {
            throw DnaGraphException("Too big an oligonucleotide size"); 
        }

        auto vertexIterators = boost::make_iterator_range(GetVertexIterators());
        for(auto first : vertexIterators)
        {
            for(auto second : vertexIterators)
            {
                if(first != second)
                {   
                    for(auto i  = 0; i < m_oligonucleotideSize; i++)
                    {
                        std::string_view firstSubstr {m_graph[first].substr(i, m_oligonucleotideSize)};
                        std::string_view secondSubstr {m_graph[second].substr(0, m_oligonucleotideSize-i)};
                        if(firstSubstr == secondSubstr)
                        {
                            std::string_view diff = 
                                {m_graph[second].substr(m_oligonucleotideSize - i, m_oligonucleotideSize)};
                            // if(diff ==  "")
                            // {
                            //     break;
                            // }
                            AddEdge(first, second, {diff, m_oligonucleotideSize - diff.size()});
                            break;
                        }
                    }
                }
            }
        }
        if(GetAmountOfOutEdges(GetFirstOligonucleotide()) < 1)
        {
            throw DnaGraphException("No connections between first oligonucleotide");
        }
    }

    
    DnaGraph::vd DnaGraph::GetFirstOligonucleotide() const
    {
        return m_firstOligoNucleotide;
    }

    int DnaGraph::GetOligonucleotideSize() const
    {
        return m_oligonucleotideSize;
    }

    void DnaGraph::EvaporateAllEdges(double evaporationRatio, double minimalPherones, double smoothRatio)
    {
        for(auto [edgesIt, edgesEnd] = GetEdgesIterators(); edgesIt != edgesEnd; edgesIt++)
        {
            m_graph[*edgesIt].Evaporate(evaporationRatio, minimalPherones, smoothRatio);
        }
    }
}