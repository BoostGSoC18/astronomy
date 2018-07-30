#ifndef BOOST_ASTRONOMY_IO_IMAGE_HPP
#define BOOST_ASTRONOMY_IO_IMAGE_HPP


#include <valarray>
#include <fstream>
#include <cstddef>
#include <algorithm>
#include <iterator>
#include <cstdint>

#include <boost/astronomy/io/bitpix.hpp>

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
                std::valarray<PixelType> data;

                union pixel_data
                {
                    PixelType pixel;
                    std::uint8_t byte[sizeof(PixelType)];
                };

            public:

            };


            template<bitpixes ... args>
            struct image {};


            template <>
            struct image<B8> : public image_buffer<std::uint8_t>
            {
            public:
                image(std::fstream &file, std::size_t start, std::size_t width, std::size_t height)
                {
                    data.resize(width*height);
                    file.seekg(start);
                    std::copy_n(std::istreambuf_iterator<char>(file.rdbuf()), width*height, std::begin(data));
                }
            };


            template <>
            struct image<B16> : public image_buffer<std::int16_t>
            {
            public:
                image(std::fstream &file, std::size_t start, std::size_t width, std::size_t height)
                {
                    data.resize(width*height);
                    file.seekg(start);

                    pixel_data single_pixel;
                    for (std::size_t i = 0; i < height*width; i++)
                    {
                        std::copy_n(std::istreambuf_iterator<char>(file.rdbuf()), 2, std::begin(single_pixel.byte));
                        data[i] = (single_pixel.byte[1] << 0) | (single_pixel.byte[0] << 8);
                    }
                }
            };


            template <>
            struct image<B32> : public image_buffer<std::int32_t>
            {
            public:
                image(std::fstream &file, std::size_t start, std::size_t width, std::size_t height)
                {
                    data.resize(width*height);
                    file.seekg(start);

                    pixel_data single_pixel;
                    for (std::size_t i = 0; i < height*width; i++)
                    {
                        std::copy_n(std::istreambuf_iterator<char>(file.rdbuf()), 4, std::begin(single_pixel.byte));
                        data[i] = (single_pixel.byte[3] << 0) | (single_pixel.byte[2] << 8) |
                            (single_pixel.byte[1] << 16) | (single_pixel.byte[0] << 24);
                    }
                }
            };


            template <>
            struct image<_B32> : public image_buffer<float>
            {
            public:
                image(std::fstream &file, std::size_t start, std::size_t width, std::size_t height)
                {
                    data.resize(width*height);
                    file.seekg(start);

                    pixel_data single_pixel;
                    for (std::size_t i = 0; i < height*width; i++)
                    {
                        std::copy_n(std::istreambuf_iterator<char>(file.rdbuf()), 4, std::begin(single_pixel.byte));
                        data[i] = (single_pixel.byte[3] << 0) | (single_pixel.byte[2] << 8) |
                            (single_pixel.byte[1] << 16) | (single_pixel.byte[0] << 24);
                    }
                }
            };


            template <>
            struct image<_B64> : public image_buffer<double>
            {
            public:
                image(std::fstream &file, std::size_t start, std::size_t width, std::size_t height)
                {
                    data.resize(width*height);
                    file.seekg(start);

                    pixel_data single_pixel;
                    for (std::size_t i = 0; i < height*width; i++)
                    {
                        std::copy_n(std::istreambuf_iterator<char>(file.rdbuf()), 8, std::begin(single_pixel.byte));
                        data[i] = (single_pixel.byte[7] << 0) | (single_pixel.byte[6] << 8) |
                            (single_pixel.byte[5] << 16) | (single_pixel.byte[4] << 24) |
                            (single_pixel.byte[3] << 32) | (single_pixel.byte[2] << 40) |
                            (single_pixel.byte[1] << 48) | (single_pixel.byte[0] << 56);
                    }
                }
            };
        } //namespace io
    } //namespace astronomy
} //namespace boost

#endif // !BOOST_ASTRONOMY_IO_IMAGE_HPP

