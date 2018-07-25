#ifndef BOOST_ASTRONOMY_COORDINATE_HELIOCENTRIC_HPP
#define BOOST_ASTRONOMY_COORDINATE_HELIOCENTRIC_HPP

#include <boost/astronomy/coordinate/base_ecliptic_frame.hpp>

namespace boost
{
    namespace astronomy
    {
        namespace coordinate
        {
            template <typename RepresentationDegreeOrRadian = boost::astronomy::coordinate::degree,
                typename DifferentailDegreeOrRadian = boost::astronomy::coordinate::degree>
                struct heliocentric : public base_ecliptic_frame
                <RepresentationDegreeOrRadian, DifferentailDegreeOrRadian>
            {
            public:
                heliocentric() {}

                template <typename Represetation>
                heliocentric(Represetation const& representation_data) : base_ecliptic_frame
                    <RepresentationDegreeOrRadian, DifferentailDegreeOrRadian>(representation_data) {}

                heliocentric(double lat, double lon, double distance) : base_ecliptic_frame
                    <RepresentationDegreeOrRadian, DifferentailDegreeOrRadian>(lat, lon, distance) {}

                heliocentric(double lat, double lon, double distance, double pm_lat, double pm_lon_coslat, double radial_velocity) :
                    base_ecliptic_frame<RepresentationDegreeOrRadian, DifferentailDegreeOrRadian>
                    (lat, lon, distance, pm_lat, pm_lon_coslat, radial_velocity) {}

                template <typename Representation, typename Differential>
                heliocentric(Representation const& representation_data, Differential const& diff) :
                    base_ecliptic_frame<RepresentationDegreeOrRadian, DifferentailDegreeOrRadian>
                    (representation_data, diff) {}
            };
        } //namespace coordinate
    } //namespace astronomy
} //namespace boost

#endif // !BOOST_ASTRONOMY_COORDINATE_HELIOCENTRIC_HPP

