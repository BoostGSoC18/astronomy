#ifndef BOOST_ASTRONOMY_IO_FITS_HPP
#define BOOST_ASTRONOMY_IO_FITS_HPP

#include <fstream>
#include <string>
#include <vector>
#include <memory>

#include <boost/astronomy/io/primary_hdu.hpp>
#include <boost/astronomy/io/extension_hdu.hpp>
#include <boost/astronomy/exception/fits_exception.hpp>

namespace boost
{
    namespace astronomy
    {
        namespace io
        {
            struct fits 
            {
            protected:
                std::fstream fits_file; //!FITS to be processed
                std::vector<std::shared_ptr<boost::astronomy::io::hdu>> _hdu; //!Stores all th HDU in file

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
                    _hdu[0] = std::make_shared<boost::astronomy::io::hdu>(fits_file);
                    
                    switch (_hdu[0]->value_of<int>(std::string("BITPIX")))
                    {
                    case 8:
                        _hdu[0] = std::make_shared<boost::astronomy::io::primary_hdu<boost::astronomy::io::B8>>(fits_file, *_hdu[0]);
                        break;
                    case 16:
                        _hdu[0] = std::make_shared<boost::astronomy::io::primary_hdu<boost::astronomy::io::B16>>(fits_file, *_hdu[0]);
                        break;
                    case 32:
                        _hdu[0] = std::make_shared<boost::astronomy::io::primary_hdu<boost::astronomy::io::B32>>(fits_file, *_hdu[0]);
                        break;
                    case -32:
                        _hdu[0] = std::make_shared<boost::astronomy::io::primary_hdu<boost::astronomy::io::_B32>>(fits_file, *_hdu[0]);
                        break;
                    case -64:
                        _hdu[0] = std::make_shared<boost::astronomy::io::primary_hdu<boost::astronomy::io::_B64>>(fits_file, *_hdu[0]);
                        break;
                    default:
                        throw fits_exception();
                        break;
                    }
                }

                void read_extensions()
                {
                    //if no extension then return
                    if (!_hdu[0]->value_of<bool>("EXTEND"))
                    {
                        return;
                    }

                    while (!fits_file.eof())
                    {
                        _hdu.emplace_back(std::make_shared<boost::astronomy::io::hdu>(fits_file));

                        if (_hdu.back()->value_of<std::string>("XTENSION") == "'IMAGE   '")
                        {
                            switch (_hdu.back()->value_of<int>(std::string("BITPIX")))
                            {
                            case 8:
                                _hdu.back() = std::make_shared<boost::astronomy::io::primary_hdu<boost::astronomy::io::B8>>(fits_file, *_hdu.back());
                                break;
                            case 16:
                                _hdu.back() = std::make_shared<boost::astronomy::io::primary_hdu<boost::astronomy::io::B16>>(fits_file, *_hdu.back());
                                break;
                            case 32:
                                _hdu.back() = std::make_shared<boost::astronomy::io::primary_hdu<boost::astronomy::io::B32>>(fits_file, *_hdu.back());
                                break;
                            case -32:
                                _hdu.back() = std::make_shared<boost::astronomy::io::primary_hdu<boost::astronomy::io::_B32>>(fits_file, *_hdu.back());
                                break;
                            case -64:
                                _hdu.back() = std::make_shared<boost::astronomy::io::primary_hdu<boost::astronomy::io::_B64>>(fits_file, *_hdu.back());
                                break;
                            default:
                                throw fits_exception();
                                break;
                            }
                        }
                        else if (_hdu.back()->value_of<std::string>("XTENSION") == "'TABLE   '")
                        {

                        }
                        
                    }
                }
            };
        } //namespace io
    } //namespace astronomy
} //namespace boost

#endif // !BOOST_ASTRONOMY_IO_FITS_HPP

