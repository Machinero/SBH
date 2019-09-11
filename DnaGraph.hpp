#ifndef DNAGRAPH_HPP
#define DNAGRAPH_HPP

#include "Graph.hpp"
#include "Dna.hpp"
#include "Edge.hpp"

#include <vector>
#include <atomic>

namespace SBH
{
    class DnaGraph 
        : public Dna, public Graph<std::string_view, Edge, boost::vecS>
    {
        public:
            DnaGraph(std::string nucleotides, int oligonucleotideSize);
            explicit DnaGraph(Dna dna);
            DnaGraph() = default;
            DnaGraph::vd GetFirstOligonucleotide() const;
            void EvaporateAllEdges(double evaporationRatio, double minimalPheromones, double smoothRatio);
            int GetOligonucleotideSize() const;

        private:
            int m_oligonucleotideSize;
            DnaGraph::vd m_firstOligoNucleotide;

    };      
}


#endif /* DNAGRAPH_HPP */