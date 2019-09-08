#ifndef DNAGRAP_EXCEPTION_HPP
#define DNAGRAP_EXCEPTION_HPP

#include <exception>
#include <string>


namespace SBH 
{

    class DnaGraphException : public std::exception
    {
        public:
            explicit DnaGraphException(std::string error)
                : m_error(std::move(error))
            {

            }
            explicit DnaGraphException(char const* error)
                : m_error(error)           
            {

            }

            char const* what() const noexcept override
            {
                return m_error.c_str();
            }
        private:
            std::string m_error;    
    };
}

#endif /* DNAGRAPH_EXCEPTION */