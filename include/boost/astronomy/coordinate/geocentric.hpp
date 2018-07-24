#ifndef BOOST_ASTRONOMY_COORDINATE_GEOCENTRIC_HPP
#define BOOST_ASTRONOMY_COORDINATE_GEOCENTRIC_HPP

#include <boost/astronomy/coordinate/base_ecliptic_frame.hpp>

namespace boost
{
    namespace astronomy
    {
        namespace coordinate
        {
            template <typename RepresentationDegreeOrRadian = boost::astronomy::coordinate::degree,
                typename DifferentailDegreeOrRadian = boost::astronomy::coordinate::degree>
            struct geocentric : public boost::astronomy::coordinate::base_ecliptic_frame
                <RepresentationDegreeOrRadian, DifferentailDegreeOrRadian>
            {
            public:
                geocentric() {}

                template <typename Represetation>
                geocentric(Represetation const& representation_data) : base_ecliptic_frame
                    <RepresentationDegreeOrRadian, DifferentailDegreeOrRadian>(representation_data) {}

                geocentric(double lat, double lon, double distance = 1.0) : base_ecliptic_frame
                    <RepresentationDegreeOrRadian, DifferentailDegreeOrRadian>(lat, lon, distance) {}

                geocentric(double lat, double lon, double distance, double pm_lat, double pm_lon_coslat, double radial_velocity) :
                    base_ecliptic_frame<RepresentationDegreeOrRadian, DifferentailDegreeOrRadian>
                    (lat, lon, distance, pm_lat, pm_lon_coslat, radial_velocity) {}

                template <typename Representation, typename Differential>
                geocentric(Representation const& representation_data, Differential const& diff) :
                    base_ecliptic_frame<RepresentationDegreeOrRadian, DifferentailDegreeOrRadian>
                    (representation_data, diff) {}
            };
        } //namespace coordinate
    } //namespace astronomy
} //namespace boost

#endif // !BOOST_ASTRONOMY_COORDINATE_GEOCENTRIC_HPP

