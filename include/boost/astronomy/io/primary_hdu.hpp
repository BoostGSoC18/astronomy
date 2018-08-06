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
                image<DataType> data;
                
            public:
                primary_hdu() {}

                primary_hdu(std::fstream &file) : hdu(file)
                {
                    simple = this->value_of<bool>("SIMPLE");
                    extend = this->value_of<bool>("EXTEND");

                    //read image according to dimension specified by naxis
                    switch (this->naxis())
                    {
                    case 0:
                        break;
                    case 1:
                        data.read_image(file, this->naxis(1), 1);
                        break;
                    case 2:
                        data.read_image(file, this->naxis(1), this->naxis(2));
                    default:
                        data.read_image(file, this->naxis(1), std::accumulate(this->_naxis.begin()+1, this->_naxis.end(), 0, std::multiplies<std::size_t>()));
                        break;
                    }
                }

                primary_hdu(hdu const& other) : hdu(other)
                {
                    simple = this->value_of<bool>("SIMPLE");
                    extend = this->value_of<bool>("EXTEND");

                    //read image according to dimension specified by naxis
                    switch (this->naxis())
                    {
                    case 0:
                        break;
                    case 1:
                        data.read_image(file, this->naxis(1), 1);
                        break;
                    case 2:
                        data.read_image(file, this->naxis(1), this->naxis(2));
                    default:
                        data.read_image(file, this->naxis(1), std::accumulate(this->_naxis.begin() + 1, this->_naxis.end(), 0, std::multiplies<std::size_t>()));
                        break;
                    }
                }
            };
        } //namespace io
    } //namespace astronomy
} //namespace boost


#endif // !BOOST_ASTRONOMY_IO_PRIMARY_HDU_HPP

