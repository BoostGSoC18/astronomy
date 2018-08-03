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
                return "Card length must not be more 80 chars";
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

        class invalid_key_length_exception : public invalid_card_length_exception
        {
        public:
            const char* what() const throw()
            {
                return "Key length must note be more than 8 chars";
            }
        };

        class invalid_value_length_exception : public invalid_card_length_exception
        {
        public:
            const char* what() const throw()
            {
                return "value length must not be more than 70 chars including comments";
            }
        };

        class key_not_defined_exception : public fits_exception
        {
        public:
            const char* what() const throw()
            {
                return "key is not defined";
            }
        };

    } //namespace astronomy
} //namespace boost
#endif // !BOOST_ASTRONOMY_EXCEPTION_FITS_EXCEPTION_HPP

