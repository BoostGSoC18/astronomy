#ifndef BOOOST_ASTRONOMY_COORDINATE_ALT_AZ_HPP
#define BOOOST_ASTRONOMY_COORDINATE_ALT_AZ_HPP

#include <time.h>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/algorithms/transform.hpp>
#include <boost/geometry/algorithms/equals.hpp>
#include <boost/units/quantity.hpp>
#include <boost/units/systems/si/pressure.hpp>
#include <boost/units/systems/temperature/celsius.hpp>

#include <boost/astronomy/coordinate/base_coordinate.hpp>
#include <boost/astronomy/coordinate/representation.hpp>
#include <boost/astronomy/coordinate/differential.hpp>

namespace boost
{
    namespace astronomy
    {
        namespace coordinate
        {
            struct alt_az : public base_coordinate
                <boost::astronomy::coordinate::spherical_representation<boost::geometry::degree>,
                boost::astronomy::coordinate::spherical_coslat_differential<boost::geometry::degree>>
            {
            protected:
                double rel_humidity;
                boost::astronomy::coordinate::spherical_equatorial_representation<boost::geometry::degree> earth_location;
                boost::units::quantity<boost::units::si::pressure> pressure;
                boost::units::quantity<boost::units::temperature::celsius_base_unit> temprature = 0;
                time_t obs_time;

            public:
                alt_az() {}

                alt_az(double az, double alt, double distance = 1.0)
                {
                    boost::geometry::set<0>(this->data, az);
                    boost::geometry::set<1>(this->data, alt);
                    boost::geometry::set<2>(this->data, distance);
                    this->has_data = true;
                }

            };
        } //namespace coordinate
    } //namespace astronomy
} //namespace boost
#endif // !BOOOST_ASTRONOMY_COORDINATE_ALT_AZ_HPP

