#ifndef BOOST_ASTRONOMY_IO_HDU_HPP
#define BOOST_ASTRONOMY_IO_HDU_HPP

//#include <map>
#include <string>
#include <fstream>
#include <vector>
#include <cstddef>

#include <boost/algorithm/string/trim.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/astronomy/io/image.hpp>

#include <boost/astronomy/exception/fits_exception.hpp>

namespace boost
{
    namespace astronomy
    {
        namespace io
        {
            //!structure to store a card (80 byte key value pairs as well as comments and history cards)
            struct card
            {
            private:
                std::string card_;

            public:
                card()
                {
                    this->card_.reserve(80);
                }

                card(std::string str) : card()
                {
                    if (str.length() != 80)
                    {
                        throw invalid_card_length_exception();
                    }
                    this->card_ = str;
                }

                std::string key(bool whole = false) const
                {
                    if (whole)
                    {
                        return this->card_.substr(0, 8);
                    }
                    return boost::algorithm::trim_copy(this->card_.substr(0, 8));
                }

                template <typename ReturnType>
                ReturnType value(bool comment = false) const
                {
                    if (comment)
                    {
                        return this->card_.substr(10);
                    }
                    std::string val = boost::algorithm::trim_copy(this->card_.substr(10, this->card_.find('/')));
                    try
                    {
                        return boost::lexical_cast<int>(val);
                    }
                    catch (boost::bad_lexical_cast int_e)
                    {
                        try
                        {
                            return boost::lexical_cast<double>(val);
                        }
                        catch (boost::bad_lexical_cast double_e)
                        {
                            return val;
                        }
                    }

                }

                void value(std::string const& value)
                {
                    if (value.length() > 70)
                    {
                        throw invalid_card_length_exception();
                    }
                    this->card_.append(70 - value.length(), ' ');
                }
            };

            //structure to represent a header unit with max 36 cards
            //struct hdu_unit
            //{
            //protected:
            //    std::vector<card> cards;

            //public:
            //    hdu_unit() {}

            //    hdu_unit(std::vector<card> const& c)
            //    {
            //        if (c.size() > 36)
            //        {
            //            throw hdu_unit_overflow_exception();
            //        }
            //        this->cards = c;
            //    }

            //    void add_card(card const &c)
            //    {
            //        if (cards.size() == 36)
            //        {
            //            throw hdu_unit_overflow_exception();
            //        }
            //        this->cards.push_back(c);
            //    }

            //    void add_card(std::string str)
            //    {
            //        card c(str);
            //        this->add_card(c);
            //    }

            //    inline std::size_t size() const
            //    {
            //        return cards.size();
            //    }
            //};

            struct hdu
            {
            protected:
                boost::astronomy::io::bitpixes bitpix;
                std::vector<std::size_t> naxis;
                std::vector<card> cards;
                //std::map<std::string, int> index;

            public:
                hdu() {}
            };
        } //namespace io
    } //namespace astronomy
} //namespace boost

#endif // !BOOST_ASTRONOMY_IO_HDU_HPP

