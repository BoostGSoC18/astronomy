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
                boost::astronomy::io::bitpix bitpix_value;
                std::vector<std::size_t> _naxis;
                std::vector<card> cards;
                std::unordered_map<std::string, int> key_index;

            public:
                hdu() {}

                hdu(std::fstream &file)
                {
                    read_header(file);
                }

                hdu(std::fstream &file, std::streampos pos)
                {
                    read_header(file, pos);
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
                        this->bitpix_value = boost::astronomy::io::B8;
                        break;
                    case 16:
                        this->bitpix_value = boost::astronomy::io::B16;
                        break;
                    case 32:
                        this->bitpix_value = boost::astronomy::io::B32;
                        break;
                    case -32:
                        this->bitpix_value = boost::astronomy::io::_B32;
                        break;
                    case -64:
                        this->bitpix_value = boost::astronomy::io::_B64;
                        break;
                    default:
                        throw fits_exception();
                        break;
                    }
                    
                    //setting naxis values
                    _naxis.emplace_back(cards[key_index["NAXIS"]].value<std::size_t>());
                    _naxis.reserve(_naxis[0]);
                    
                    for (size_t i = 1; i <= _naxis[0]; i++)
                    {
                        _naxis.emplace_back(cards[key_index["NAXIS" + boost::lexical_cast<std::string>(i)]].value<std::size_t>());
                    }
                }

                void read_header(std::fstream &file, std::streampos pos)
                {
                    file.seekg(pos);
                    read_header(file);
                }

                //!returns the value of bitpix
                boost::astronomy::io::bitpix bitpix() const
                {
                    return this->bitpix_value;
                }

                //!returns the value of all naxis (NAXIS, NAXIS1, NAXIS2...)
                std::vector<std::size_t> all_naxis() const
                {
                    return this->_naxis;
                }

                //!returns the value of particular naxis
                std::size_t naxis(std::size_t n = 0)
                {
                    return this->_naxis[n];
                }

                //!returns the value of perticular key 
                template <typename ReturnType>
                ReturnType value_of(std::string const& key) const
                {
                    return cards[key_index[key]].value<ReturnType>()
                }

            };
        } //namespace io
    } //namespace astronomy
} //namespace boost

#endif // !BOOST_ASTRONOMY_IO_HDU_HPP

