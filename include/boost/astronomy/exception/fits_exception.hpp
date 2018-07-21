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

        class hdu_unit_overflow_exception : public fits_exception
        {
        public:
            const char* what() const throw()
            {
                return "HDU unit can accommodate 36 cards max";
            }
        };

    } //namespace astronomy
} //namespace boost
#endif // !BOOST_ASTRONOMY_EXCEPTION_FITS_EXCEPTION_HPP

