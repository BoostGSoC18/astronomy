#ifndef BOOST_ASTRONOMY_IO_EXTENSION_HDU_HPP
#define BOOST_ASTRONOMY_IO_EXTENSION_HDU_HPP

//#include <map>
#include <string>
#include <vector>
#include <cstddef>
#include <valarray>

#include <boost/astronomy/io/hdu.hpp>

namespace boost
{
    namespace astronomy
    {
        namespace io
        {
            struct extension_hdu : public boost::astronomy::io::hdu
            {
            protected:
                int gcount = 1;
                int pcount = 0;

            public:

            };
        } //namespace io
    } //namespace astronomy
} //namespace boost

#endif // !BOOST_ASTRONOMY_IO_EXTENSION_HDU_HPP

