#ifndef BOOST_ASTRONOMY_IO_FITS_HPP
#define BOOST_ASTRONOMY_IO_FITS_HPP

#include <fstream>
#include <string>
#include <vector>
#include <memory>

#include <boost/astronomy/io/primary_hdu.hpp>
#include <boost/astronomy/io/extension_hdu.hpp>

namespace boost
{
    namespace astronomy
    {
        namespace io
        {
            struct fits 
            {
            protected:
                std::fstream fits_file;
                std::vector<std::shared_ptr<boost::astronomy::io::hdu>> _hdu; //stores all th HDU in file

            public:
                fits() {}

                fits(std::string file_path, std::ios_base::openmode mode = std::ios_base::in | std::ios_base::binary)
                {
                    fits_file.open(file_path, std::ios_base::in | std::ios_base::binary | mode);
                    _hdu.resize(1);
                    read_primary_hdu();
                    read_extensions();
                }

                void read_primary_hdu()
                {
                    _hdu[0] = std::make_shared<hdu>(fits_file);
                    _hdu[0] = std::make_shared<primary_hdu<_hdu[0]->bitpix()>>(*_hdu[0]);
                }

                void read_extensions()
                {

                }
            };
        } //namespace io
    } //namespace astronomy
} //namespace boost

#endif // !BOOST_ASTRONOMY_IO_FITS_HPP

