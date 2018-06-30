#ifndef BOOST_ASTRONOMY_IO_FITS_HPP
#define BOOST_ASTRONOMY_IO_FITS_HPP

#include <map>
#include <string>
#include <fstream>

#include <boost/algorithm/string/trim.hpp>

namespace boost
{
    namespace astronomy
    {
        namespace io
        {
            struct fits {
            protected:
                std::multimap<std::string, std::string> header;
                std::fstream file;

            public:
                fits() {}

                fits(std::string const& path, std::ios_base::openmode mode = std::ios_base::in)
                {
                    file.open(path, mode);
                    
                    char card[81] = "";
                    std::string header_part = "", value_part = "";
                    while (header_part != "END")
                    {
                        file.read(card, 80);
                        header_part.assign(card, 8);
                        boost::algorithm::trim(header_part);
                        value_part.assign(card + 10, 70);
                        if(header_part != "")
                            header.insert(std::pair<std::string, std::string>(header_part, value_part));
                    }

                    file.seekg(((int)(file.tellg() / 2880) + 1) * 2880);
                }

            };
        } //namespace io
    } //namespace astronomy
} //namespace boost

#endif // !BOOST_ASTRONOMY_IO_FITS_HPP

