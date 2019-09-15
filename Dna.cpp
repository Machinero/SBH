#include "Dna.hpp"
#include "DnaException.hpp"
#include "Settings.hpp"

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
            m_dp.resize(m_nucleotides.size() + 1, std::vector<int>(m_nucleotides.size() + 1));
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

    void Dna::ClearNucleotides()
    {
        m_nucleotides = "";
    }

    double Dna::Score(std::string const& generatedDna) 
    {
        static constexpr int MATCH = 2;
        static constexpr int MISS = 1;
        static constexpr int GAP = 1;

        for(auto& vec : m_dp)
        {
            std::fill(vec.begin(), vec.end(), 0);
        }
        std::size_t size = m_nucleotides.size();
        for(auto i = 0U; i <= size; i++)
        {
           m_dp[i][0] = m_dp[0][i] = -i * GAP;
        }
        for(auto i = 1U; i <= size; i++)
        {
            for(auto j = 1U; j <= generatedDna.size(); j++)
            {
                auto S = (m_nucleotides[i-1] == generatedDna[j-1] ? MATCH : MISS);
                auto lhs = m_dp[i-1][j-1] + S;
                auto rhs = std::max(m_dp[i-1][j] - GAP, m_dp[i][j-1] - GAP);
                m_dp[i][j] = std::max(lhs, rhs);
            }
        }
        return (m_dp[size][generatedDna.size()] / static_cast<double>(size * 2)) * 100;
    }

    void Dna::LoadFromFile(std::string filePath)
    {
        std::ifstream file;
        file.open(filePath);
        if(file.is_open())
        {
            std::string text; 
            getline(file, text);
            if(text.empty())
            {
                throw DnaException("Inputted text are blank.");
            }
            if(AreNucleotides(text)) 
            {
                m_nucleotides = std::move(text);
                m_dp.resize(m_nucleotides.size() + 1, std::vector<int>(m_nucleotides.size() + 1));
            }
            else
            {
                throw DnaException("Invalid dna sequence.");
            }
        }
    }
}

