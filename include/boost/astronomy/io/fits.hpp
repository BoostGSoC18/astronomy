#ifndef BOOST_ASTRONOMY_IO_FITS_HPP
#define BOOST_ASTRONOMY_IO_FITS_HPP

#include <fstream>
#include <string>
#include <vector>

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
                boost::astronomy::io::primary_hdu phdu;
                std::vector<boost::astronomy::io::extension_hdu> ehdu;

            public:
                fits() {}

                fits(std::string file_path, std::ios_base::openmode mode = std::ios_base::in)
                {
                    fits_file.open(file_path, mode);
                    read_primary_hdu();
                    read_extensions();
                }

                void read_primary_hdu()
                {

                }

                void read_extensions()
                {

                }
            };
        } //namespace io
    } //namespace astronomy
} //namespace boost

#endif // !BOOST_ASTRONOMY_IO_FITS_HPP

