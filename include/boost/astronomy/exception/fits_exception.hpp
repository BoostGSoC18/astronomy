#ifndef BOOST_ASTRONOMY_EXCEPTION_FITS_EXCEPTION_HPP
#define BOOST_ASTRONOMY_EXCEPTION_FITS_EXCEPTION_HPP

#include <exception>

namespace boost
{
    namespace astronomy
    {
        class fits_exception : public std::exception
        {
        public:
            const char* what() const throw()
            {
                return "FITS exception";
            }
        };

        class invalid_card_length_exception : public fits_exception
        {
        public:
            const char* what() const throw()
            {
                return "Card length must be 80 chars";
            }
        };

    } //namespace astronomy
} //namespace boost
#endif // !BOOST_ASTRONOMY_EXCEPTION_FITS_EXCEPTION_HPP

