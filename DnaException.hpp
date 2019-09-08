#ifndef DNA_EXCEPTION_HPP
#define DNA_EXCEPTION_HPP

#include <exception>
#include <string>


namespace SBH 
{

    class DnaException : public std::exception
    {
        public:
            explicit DnaException(std::string error)
                : m_error(std::move(error))
            {

            }
            explicit DnaException(char const* error)
                : m_error(error)           
            {

            }

            char const* what() const noexcept
            {
                return m_error.c_str();
            }
        private:
            std::string m_error;    
    };
}

#endif /* DNA_EXCEPTION */