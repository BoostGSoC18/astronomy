#ifndef BOOST_ASTRONOMY_IO_HDU_HPP
#define BOOST_ASTRONOMY_IO_HDU_HPP

#include <string>
#include <fstream>
#include <vector>
#include <cstddef>
#include <unordered_map>

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
                std::unordered_map<std::string, int> key_index;

            public:
                hdu() {}

                hdu(std::fstream &file)
                {
                    read_header(file);
                }

                void read_header(std::fstream &file)
                {
                    cards.reserve(36);
                    char _80_char_from_file[80];

                    //reading file line by line 
                    while (true)
                    {
                        file.read(_80_char_from_file, 80);
                        cards.emplace_back(_80_char_from_file);

                        this->key_index[this->cards.back().key()] = this->cards.size() - 1;

                        if(this->cards.back().key(true) == "END     ")
                        {
                            break;
                        }
                    }
                    file.seekg(((int)(file.tellg() / 2880) + 1) * 2880);    //set cursor to the end of the HDU unit

                    //finding and storing bitpix value
                    
                    switch (cards[key_index["BITPIX"]].value<int>())
                    {
                    case 8:
                        this->bitpix = boost::astronomy::io::B8;
                        break;
                    case 16:
                        this->bitpix = boost::astronomy::io::B16;
                        break;
                    case 32:
                        this->bitpix = boost::astronomy::io::B32;
                        break;
                    case -32:
                        this->bitpix = boost::astronomy::io::_B32;
                        break;
                    case -64:
                        this->bitpix = boost::astronomy::io::_B64;
                        break;
                    default:
                        throw fits_exception();
                        break;
                    }
                    
                    //setting naxis values
                    naxis.emplace_back(cards[key_index["NAXIS"]].value<std::size_t>());
                    naxis.reserve(naxis[0]);
                    
                    for (size_t i = 1; i <= naxis[0]; i++)
                    {
                        naxis.emplace_back(cards[key_index["NAXIS" + boost::lexical_cast<std::string>(i)]].value<std::size_t>());
                    }
                }
            };
        } //namespace io
    } //namespace astronomy
} //namespace boost

#endif // !BOOST_ASTRONOMY_IO_HDU_HPP

