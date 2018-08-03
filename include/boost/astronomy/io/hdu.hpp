#ifndef BOOST_ASTRONOMY_IO_HDU_HPP
#define BOOST_ASTRONOMY_IO_HDU_HPP

#include <string>
#include <fstream>
#include <vector>
#include <cstddef>

#include <boost/algorithm/string/trim.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/astronomy/io/image.hpp>

#include <boost/astronomy/exception/fits_exception.hpp>
#include <boost/astronomy/io/card.hpp>

namespace boost
{
    namespace astronomy
    {
        namespace io
        {
            struct hdu
            {
            protected:
                boost::astronomy::io::bitpixes bitpix;
                std::vector<std::size_t> naxis;
                std::vector<card> cards;

            public:
                hdu() {}
            };
        } //namespace io
    } //namespace astronomy
} //namespace boost

#endif // !BOOST_ASTRONOMY_IO_HDU_HPP

