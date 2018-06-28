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
                std::map<std::string, std::string> header;
                std::fstream file;

            public:
                fits() {}

                //template <typename Mode=std::ios::in>
                fits(std::string const& path)
                {
                    file.open(path);
                    
                    char card[81] = "";
                    std::string header_part = "", value_part = "";
                    while (!(card[0] == 'E' && card[1] == 'N' && card[2] == 'D'))
                    {
                        file.read(card, 80);
                        header_part.assign(card, 8);
                        value_part.assign(card + 10, 70);
                        header[header_part] = value_part;
                    }

                    file.seekg(((int)(file.tellg() / 2880) + 1) * 2880);
                }

            };
        } //namespace io
    } //namespace astronomy
} //namespace boost

#endif // !BOOST_ASTRONOMY_IO_FITS_HPP

