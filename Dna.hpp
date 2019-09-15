#ifndef DNA_HPP
#define DNA_HPP

#include <iostream>
#include <optional>
#include <array>
#include <vector>


namespace SBH 
{
    class Dna 
    {
        public:
            explicit Dna(std::string text);
            Dna() = default;
            Dna(Dna const&) = default;
            Dna(Dna&&) = default;
            Dna& operator = (Dna const &) = default;
            Dna& operator = (Dna&&) = default;
            ~Dna() = default;
            
            friend std::ostream& operator << (std::ostream& stream, Dna const& dna);
            std::string const& GetNucleotides() const;
            void Append(std::string oligonucleotide);
            std::size_t GetDnaSize() const;
            void ClearNucleotides(); 
            double Score(std::string const& generatedDna);
            void LoadFromFile(std::string filePath);

        private:
            bool AreNucleotides(std::string const& text);
            std::vector<std::vector<int>> m_dp;
            std::string m_nucleotides {};
            static constexpr std::array<char, 4> sm_nucleotides = {'A', 'C', 'G', 'T'}; 
    };
}

#endif /* DNA_HPP */