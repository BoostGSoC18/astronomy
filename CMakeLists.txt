cmake_minimum_required(VERSION 3.12)
project(astronomy)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
include_directories(include/boost)
include_directories(include/boost/astronomy)
include_directories(include/boost/astronomy/coordinate)
include_directories(include/boost/astronomy/detail)
include_directories(include/boost/astronomy/exception)
include_directories(include/boost/astronomy/io)
INCLUDE_DIRECTORIES(../boost_1_68_0)

add_executable(astronomy
        include/boost/astronomy/coordinate/alt_az.hpp
        include/boost/astronomy/coordinate/base_differential.hpp
        include/boost/astronomy/coordinate/base_ecliptic_frame.hpp
        include/boost/astronomy/coordinate/base_equatorial_frame.hpp
        include/boost/astronomy/coordinate/base_frame.hpp
        include/boost/astronomy/coordinate/base_representation.hpp
        include/boost/astronomy/coordinate/cartesian_differential.hpp
        include/boost/astronomy/coordinate/cartesian_representation.hpp
        include/boost/astronomy/coordinate/cirs.hpp
        include/boost/astronomy/coordinate/coordinate.hpp
        include/boost/astronomy/coordinate/differential.hpp
        include/boost/astronomy/coordinate/frame.hpp
        include/boost/astronomy/coordinate/galactic.hpp
        include/boost/astronomy/coordinate/geocentric.hpp
        include/boost/astronomy/coordinate/heliocentric.hpp
        include/boost/astronomy/coordinate/icrs.hpp
        include/boost/astronomy/coordinate/representation.hpp
        include/boost/astronomy/coordinate/sky_point.hpp
        include/boost/astronomy/coordinate/spherical_coslat_differential.hpp
        include/boost/astronomy/coordinate/spherical_differential.hpp
        include/boost/astronomy/coordinate/spherical_equatorial_differential.hpp
        include/boost/astronomy/coordinate/spherical_equatorial_representation.hpp
        include/boost/astronomy/coordinate/spherical_representation.hpp
        include/boost/astronomy/coordinate/supergalactic.hpp
        include/boost/astronomy/detail/is_base_template_of.hpp
        include/boost/astronomy/exception/fits_exception.hpp
        include/boost/astronomy/io/ascii_table_extension.hpp
        include/boost/astronomy/io/binary_table_extension.hpp
        include/boost/astronomy/io/bitpix.hpp
        include/boost/astronomy/io/card.hpp
        include/boost/astronomy/io/extension_hdu.hpp
        include/boost/astronomy/io/fits.hpp
        include/boost/astronomy/io/hdu.hpp
        include/boost/astronomy/io/image.hpp
        include/boost/astronomy/io/image_extension.hpp
        include/boost/astronomy/io/primary_hdu.hpp
        include/boost/astronomy/io/table_extension.hpp
        test/differential_test.cpp
        test/representation_test.cpp
        test/test.cpp)
