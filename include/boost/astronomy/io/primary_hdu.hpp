#ifndef BOOST_ASTRONOMY_IO_PRIMARY_HDU_HPP
#define BOOST_ASTRONOMY_IO_PRIMARY_HDU_HPP

//#include <map>
#include <string>
#include <vector>
#include <cstddef>
#include <valarray>
#include <fstream>

#include <boost/astronomy/io/hdu.hpp>
#include <boost/astronomy/io/image.hpp>

namespace boost
{
    namespace astronomy
    {
        namespace io
        {
            template <typename DataType>
            struct primary_hdu : public boost::astronomy::io::hdu
            {
            protected:
                bool simple;
                bool extend;
                image_buffer<DataType> *data;
                
            public:
                primary_hdu() {}
            };
        } //namespace io
    } //namespace astronomy
} //namespace boost


#endif // !BOOST_ASTRONOMY_IO_PRIMARY_HDU_HPP

