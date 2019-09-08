#include "DnaGraph.hpp"
#include "Helper.hpp"
#include "DnaGraphException.hpp"

#include <tuple>

namespace SBH
{
    DnaGraph::DnaGraph(std::string nucleotides, int oligonucleotideSize)
        : Dna(std::move(nucleotides)), m_oligonucleotideSize(oligonucleotideSize)
    {
        int loopRange = GetNucleotides().length() - m_oligonucleotideSize;
        if(loopRange <= m_oligonucleotideSize)
        {
            for(auto i = 0; i <= loopRange; i++)
            {
                std::string_view nucleotides = GetNucleotides();
                std::string_view substring = nucleotides.substr(i, m_oligonucleotideSize);
                i == 0 ? m_firstOligoNucleotide == AddVertex(std::move(substring)) : AddVertex(std::move(substring));
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
                        std::string_view firstSubstr {GetVertex(first).substr(i, m_oligonucleotideSize)};
                        std::string_view secondSubstr {GetVertex(second).substr(0, m_oligonucleotideSize-i)};
                        if(firstSubstr == secondSubstr)
                        {
                            AddEdge(first, second, std::move(firstSubstr));
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
}