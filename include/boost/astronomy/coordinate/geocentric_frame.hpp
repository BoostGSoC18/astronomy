#ifndef BOOST_ASTRONOMY_COORDINATE_GEOCENTRIC_FRAME_HPP
#define BOOST_ASTRONOMY_COORDINATE_GEOCENTRIC_FRAME_HPP

#include <boost/astronomy/coordinate/base_ecliptic_frame.hpp>

namespace boost
{
    namespace astronomy
    {
        namespace coordinate
        {
            template <typename RepresentationDegreeOrRadian = boost::astronomy::coordinate::degree,
                typename DifferentailDegreeOrRadian = boost::astronomy::coordinate::degree>
            struct geocentric_frame : public boost::astronomy::coordinate::base_ecliptic_frame
                <RepresentationDegreeOrRadian, DifferentailDegreeOrRadian>
            {
            public:
                geocentric_frame() {}

                template <typename Represetation>
                geocentric_frame(Represetation const& representation_data) : base_ecliptic_frame(representation_data) {}

                geocentric_frame(double lat, double lon, double distance) : base_ecliptic_frame(lat, lon, distance) {}

                geocentric_frame(double lat, double lon, double distance, double pm_lat, double pm_lon_coslat, double radial_velocity) :
                    base_ecliptic_frame(lat, lon, distance, pm_lat, pm_lon_coslat, radial_velocity) {}

                template <typename Representation, typename Differential>
                geocentric_frame(Representation const& representation_data, Differential const& diff) :
                    base_ecliptic_frame(representation_data, diff) {}
            };
        } //namespace coordinate
    } //namespace astronomy
} //namespace boost

#endif // !BOOST_ASTRONOMY_COORDINATE_GEOCENTRIC_FRAME_HPP

