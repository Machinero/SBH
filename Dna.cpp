#include "Dna.hpp"
#include "DnaException.hpp"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <utility>
#include <iostream>

namespace SBH 
{
    Dna::Dna(std::string text)
    { 
        if(text.empty())
        {
            throw DnaException("Inputted text are blank.");
        }
        if(AreNucleotides(text)) 
        {
            m_nucleotides = std::move(text);
        }
        else
        {
            throw DnaException("Invalid dna sequence.");
        }
    }

    bool Dna::AreNucleotides(std::string const& text)
    {
        return std::all_of(text.begin(), text.end(), [&](auto const& mark) {
            for(auto const& nucleotide : sm_nucleotides)
                if(nucleotide == mark)
                {
                    return true;
                }
            return false;
        });
    }

    std::ostream& operator << (std::ostream& stream, Dna const& dna)
    {
        stream << dna.m_nucleotides;
        return stream;
    }

    std::string const& Dna::GetNucleotides() const 
    {
        return m_nucleotides;
    }

    std::size_t Dna::GetDnaSize() const
    {
        return m_nucleotides.size();
    }

    void Dna::Append(std::string oligonucleotide)
    {
        m_nucleotides += std::move(oligonucleotide);
    }

}