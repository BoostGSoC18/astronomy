#ifndef BOOST_ASTRONOMY_IO_IMAGE_HPP
#define BOOST_ASTRONOMY_IO_IMAGE_HPP


#include <valarray>
#include <fstream>
#include <cstddef>
#include <algorithm>
#include <iterator>
#include <cstdint>
#include <string>
#include <cmath>
#include <numeric>

#include <boost/astronomy/io/bitpix.hpp>
#include <boost/endian/conversion.hpp>
#include <boost/cstdfloat.hpp>


namespace boost
{
    namespace astronomy
    {
        namespace io
        {
            template <typename PixelType>
            struct image_buffer
            {
            protected:
                std::valarray<PixelType> data; //! stores the image
                std::size_t width; //! width of image 
                std::size_t height; //! height of image
                long total_pixel; //! total pixel in the image usually (height * width)
                std::fstream image; //! image file

                union pixel_data
                {
                    PixelType pixel;
                    std::uint8_t byte[sizeof(PixelType)];
                    //char byte[sizeof(PixelType)];
                };

            public:
                image_buffer() {}

                //! returns the maximum value of all the pixels in the image
                PixelType max() const
                {
                    return this->data.max();
                }

                //! returns the manimum value of all the pixels in the image
                PixelType min() const
                {
                    return this->data.min();
                }

                //! returns the mean value of all the pixels in image
                double mean() const
                {
                    if (this->data.size() == 0)
                    {
                        return 0;
                    }

                    return (std::accumulate(std::begin(this->data), std::end(this->data), 0.0) / this->data.size());
                }

                //! returns the median of all the pixel values in the image 
                //! Note: uses additional space of order O(n) where n is the number of total pixels
                PixelType median() const
                {
                    std::valarray<PixelType> soreted_array = this->data;
                    std::nth_element(std::begin(soreted_array), std::begin(soreted_array) + soreted_array.size() / 2, std::end(soreted_array));

                    return soreted_array[soreted_array.size() / 2];
                }

                //! returns the standard deviation of all the pixel values in the image 
                //! Note: uses additional space of order O(n) where n is the number of total pixels
                double std_dev() const
                {
                    if (this->data.size() == 0)
                    {
                        return 0;
                    }

                    double avg = this->mean();

                    std::valarray<double> diff(this->data.size());
                    for (size_t i = 0; i < diff.size(); i++)
                    {
                        diff[i] = this->data[i] - avg;
                    }
                    
                    diff *= diff;
                    return std::sqrt(diff.sum() / (diff.size() - 1));
                }
            };


            template<bitpix args>
            struct image {};


            template <>
            struct image<B8> : public image_buffer<std::uint8_t>
            {
            public:
                image() {}

                image(std::fstream &file, std::size_t width, std::size_t height, std::size_t start)
                {
                    read_image(file, width, height, start);
                }

                image(std::fstream &file, std::size_t width, std::size_t height)
                {
                    read_image(file, width, height, file.tellg());
                }

                void read_image(std::fstream &file, std::size_t width, std::size_t height, std::size_t start)
                {
                    data.resize(width*height);
                    file.seekg(start);
                    file.read((char*)std::begin(data), width*height);
                    //std::copy_n(std::istreambuf_iterator<char>(file.rdbuf()), width*height, std::begin(data));
                }

                void read_image(std::fstream &file, std::size_t width, std::size_t height)
                {
                    read_image(file, width, height, file.tellg());
                }
            };


            template <>
            struct image<B16> : public image_buffer<std::int16_t>
            {
            public:
                image() {}

                image(std::fstream &file, std::size_t width, std::size_t height, std::size_t start)
                {
                    read_image(file, width, height, start);
                }

                image(std::fstream &file, std::size_t width, std::size_t height)
                {
                    read_image(file, width, height, file.tellg());
                }

                void read_image(std::fstream &file, std::size_t width, std::size_t height, std::size_t start)
                {
                    data.resize(width*height);
                    file.seekg(start);

                    pixel_data single_pixel;
                    for (std::size_t i = 0; i < height*width; i++)
                    {
                        //std::copy_n(std::istreambuf_iterator<char>(file.rdbuf()), 2, std::begin(single_pixel.byte));

                        file.read((char*)single_pixel.byte, 2);
                        //data[i] = (single_pixel.byte[1] << 0) | (single_pixel.byte[0] << 8);
                        data[i] = boost::endian::big_to_native(data[i]);
                    }
                }

                void read_image(std::fstream &file, std::size_t width, std::size_t height)
                {
                    read_image(file, width, height, file.tellg());
                }
            };


            template <>
            struct image<B32> : public image_buffer<std::int32_t>
            {
            public:
                image() {}

                image(std::fstream &file, std::size_t width, std::size_t height, std::size_t start)
                {
                    read_image(file, width, height, start);
                }

                image(std::fstream &file, std::size_t width, std::size_t height)
                {
                    read_image(file, width, height, file.tellg());
                }

                //!reads image
                void read_image(std::fstream &file, std::size_t width, std::size_t height, std::size_t start)
                {
                    data.resize(width*height);
                    file.seekg(start);

                    pixel_data single_pixel;
                    for (std::size_t i = 0; i < height*width; i++)
                    {
                        //std::copy_n(std::istreambuf_iterator<char>(file.rdbuf()), 4, std::begin(single_pixel.byte));

                        file.read((char*)single_pixel.byte, 4);
                        //data[i] = (single_pixel.byte[3] << 0) | (single_pixel.byte[2] << 8) |
                        //    (single_pixel.byte[1] << 16) | (single_pixel.byte[0] << 24);
                        data[i] = boost::endian::big_to_native(data[i]);
                    }
                }

                void read_image(std::fstream &file, std::size_t width, std::size_t height)
                {
                    read_image(file, width, height, file.tellg());
                }
            };


            template <>
            struct image<_B32> : public image_buffer<boost::float32_t>
            {
            public:
                image() {}

                image(std::fstream &file, std::size_t width, std::size_t height, std::size_t start)
                {
                    read_image(file, width, height, start);
                }

                image(std::fstream &file, std::size_t width, std::size_t height)
                {
                    read_image(file, width, height, file.tellg());
                }

                void read_image(std::fstream &file, std::size_t width, std::size_t height, std::size_t start)
                {
                    data.resize(width*height);
                    file.seekg(start);

                    pixel_data single_pixel;
                    for (std::size_t i = 0; i < height*width; i++)
                    {
                        //std::copy_n(std::istreambuf_iterator<char>(file.rdbuf()), 4, std::begin(single_pixel.byte));

                        file.read((char*)single_pixel.byte, 4);
                        data[i] = (single_pixel.byte[3] << 0) | (single_pixel.byte[2] << 8) |
                            (single_pixel.byte[1] << 16) | (single_pixel.byte[0] << 24);
                    }
                }

                void read_image(std::fstream &file, std::size_t width, std::size_t height)
                {
                    read_image(file, width, height, file.tellg());
                }
            };


            template <>
            struct image<_B64> : public image_buffer<boost::float64_t>
            {
            public:
                image() {}

                image(std::fstream &file, std::size_t width, std::size_t height, std::size_t start)
                {
                    read_image(file, width, height, start);
                }

                image(std::fstream &file, std::size_t width, std::size_t height)
                {
                    read_image(file, width, height, file.tellg());
                }

                void read_image(std::fstream &file, std::size_t width, std::size_t height, std::size_t start)
                {
                    data.resize(width*height);
                    file.seekg(start);

                    pixel_data single_pixel;
                    for (std::size_t i = 0; i < height*width; i++)
                    {
                        //std::copy_n(std::istreambuf_iterator<char>(file.rdbuf()), 8, std::begin(single_pixel.byte));

                        file.read((char*)single_pixel.byte, 8);
                        data[i] = (single_pixel.byte[7] << 0) | (single_pixel.byte[6] << 8) |
                            (single_pixel.byte[5] << 16) | (single_pixel.byte[4] << 24) |
                            (single_pixel.byte[3] << 32) | (single_pixel.byte[2] << 40) |
                            (single_pixel.byte[1] << 48) | (single_pixel.byte[0] << 56);
                    }
                }

                void read_image(std::fstream &file, std::size_t width, std::size_t height)
                {
                    read_image(file, width, height, file.tellg());
                }
            };
        } //namespace io
    } //namespace astronomy
} //namespace boost

#endif // !BOOST_ASTRONOMY_IO_IMAGE_HPP
