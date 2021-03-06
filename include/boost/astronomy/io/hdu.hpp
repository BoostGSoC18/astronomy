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
                boost::astronomy::io::bitpix bitpix_value; //! stores the BITPIX value (enum bitpix)
                std::vector<std::size_t> _naxis; //! values of all naxis (NAXIS, NAXIS1, NAXIS2...)
                std::vector<card> cards; //! Stores the each card in header unit (80 char key value pair)
                std::unordered_map<std::string, std::size_t> key_index; //! stores the card-key index (used for faster searching)

            public:
                hdu() {}

                hdu(std::string const& file_name)
                {
                    std::fstream file(file_name, std::ios_base::in | std::ios_base::binary);
                    read_header(file);
                    file.close();
                }

                hdu(std::string const& file_name, std::streampos pos)
                {
                    std::fstream file(file_name, std::ios_base::in | std::ios_base::binary);
                    read_header(file, pos);
                    file.close();
                }

                hdu(std::fstream &file)
                {
                    read_header(file);
                }

                hdu(std::fstream &file, std::streampos pos)
                {
                    read_header(file, pos);
                }

                //!Starts reading the header from current streampos of file
                void read_header(std::fstream &file)
                {
                    cards.reserve(36); //reserves the space of atleast 1 HDU unit 
                    char _80_char_from_file[80]; //used as buffer to read a card consisting of 80 char

                    //reading file card by card until END card is found
                    while (true)
                    {
                        //read from file and create push card into the vector
                        file.read(_80_char_from_file, 80);
                        cards.emplace_back(_80_char_from_file);

                        //store the index of the card in map
                        this->key_index[this->cards.back().key()] = this->cards.size() - 1;

                        //check if end card is found
                        if(this->cards.back().key(true) == "END     ")
                        {
                            break;
                        }
                    }
                    set_unit_end(file);    //set cursor to the end of the HDU unit

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
                    
                    for (std::size_t i = 1; i <= _naxis[0]; i++)
                    {
                        _naxis.emplace_back(cards[key_index["NAXIS" + boost::lexical_cast<std::string>(i)]].value<std::size_t>());
                    }
                }

                //!starts reading file from the position specified
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
                ReturnType value_of(std::string const& key)// const
                {
                    return this->cards[key_index[key]].value<ReturnType>();
                }

                void set_unit_end(std::fstream &file) const
                {
                    file.seekg((file.tellg() + (2880 - (file.tellg() % 2880))));    //set cursor to the end of the HDU unit
                }
            };
        } //namespace io
    } //namespace astronomy
} //namespace boost

#endif // !BOOST_ASTRONOMY_IO_HDU_HPP

