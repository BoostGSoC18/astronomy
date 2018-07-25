#ifndef BOOST_ASTRONOMY_COORDINATE_ALT_AZ_HPP
#define BOOST_ASTRONOMY_COORDINATE_ALT_AZ_HPP

#include <type_traits>
#include <tuple>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/algorithms/transform.hpp>
#include <boost/geometry/algorithms/equals.hpp>
#include <boost/units/quantity.hpp>
#include <boost/units/systems/si/pressure.hpp>
#include <boost/units/systems/temperature/celsius.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/static_assert.hpp>

#include <boost/astronomy/detail/is_base_template_of.hpp>
#include <boost/astronomy/coordinate/base_frame.hpp>
#include <boost/astronomy/coordinate/representation.hpp>
#include <boost/astronomy/coordinate/differential.hpp>

namespace boost
{
    namespace astronomy
    {
        namespace coordinate
        {
            struct alt_az : public boost::astronomy::coordinate::base_frame
                <boost::astronomy::coordinate::spherical_representation<boost::geometry::degree>,
                boost::astronomy::coordinate::spherical_coslat_differential<boost::geometry::degree>>
            {
            protected:
                //frame parameters
                boost::astronomy::coordinate::spherical_equatorial_representation<boost::geometry::degree> earth_location;

                boost::units::quantity<boost::units::si::pressure> pressure = 0.0 * boost::units::si::pascals;

				boost::units::quantity<boost::units::celsius::temperature> temperature = 0.0 * boost::units::celsius::degrees;

                boost::posix_time::ptime obs_time;
                double rel_humidity;

            public:
                alt_az() {}

                template <typename Representation>
                alt_az(Representation const& representation_data)
                {
                    BOOST_STATIC_ASSERT_MSG((boost::astronomy::detail::is_base_template_of
                        <boost::astronomy::coordinate::base_representation, Representation>::value),
                        "argument type is expected to be a representation class");
                    this->data = representation_data;
                }

                alt_az(double alt, double az, double distance)
                {
                    this->data.set_lat_lon_dist(alt, az, distance);
                }

                alt_az(double alt, double az, double distance, double pm_alt, double pm_az_cosalt, double radial_velocity) :
                    alt_az(alt, az, distance)
                {
                    this->motion.set_dlat_dlon_coslat_ddist(pm_alt, pm_az_cosalt, radial_velocity);
                }

                template <typename Representation, typename Differential>
                alt_az(Representation const& representation_data, Differential const& diff)
                {
                    BOOST_STATIC_ASSERT_MSG((boost::astronomy::detail::is_base_template_of
                        <boost::astronomy::coordinate::base_representation, Representation>::value),
                        "argument type is expected to be a representation class");
                    this->data = representation_data;

                    BOOST_STATIC_ASSERT_MSG((boost::astronomy::detail::is_base_template_of
                        <boost::astronomy::coordinate::base_differential, Differential>::value),
                        "argument type is expected to be a differential class");
                    this->motion = diff;
                }

                //returns altitude component of the coordinate
                double get_alt() const
                {
					return this->data.get_lat();
                }

                //returns azimuth component of the coordinate
                double get_az() const
                {
					return this->data.get_lon();
                }

                //returns distance component of the coordinate
                double get_distance() const
                {
					return this->data.get_dist();
                }

                //returns the (alt, az, dist) in the form of tuple
                std::tuple<double, double, double> get_alt_az_dist() const
                {
                    return this->data.get_lat_lon_dist();
                }

                //returns proper motion in altitude
                double get_pm_alt() const
                {
					return this->motion.get_dlat();
                }

                //returns proper motion in azimuth including cos(alt)
                double get_pm_az_cosalt() const
                {
					return this->motion.get_dlon_coslat();
                }

                //returns radial_velocity
                double get_radial_velocity() const
                {
					return this->motion.get_ddist();
                }

                //returns the proper motion in tuple form
                std::tuple<double, double, double> get_pm_alt_az_radial() const
                {
                    return this->motion.get_dlat_dlon_coslat_ddist();
                }

                //sets value of altitude component of the coordinate
                void set_alt(double alt)
                {
					this->data.set_lat(alt);
                }

                //sets value of azimuth component of the coordinate
                void set_az(double az)
                {
					this->data.set_lon(az);
                }

                //sets value of distance component of the coordinate
                void set_distance(double distance)
                {
					this->data.set_dist(distance);
                }

                //sets value of all component of the coordinate including cos(alt)
                void set_alt_az_dist(double alt, double az, double dist)
                {
                    this->data.set_lat_lon_dist(alt, az, dist);
                }

                //sets the proper motion in altitude
                void set_pm_alt(double pm_alt)
                {
					this->motion.set_dlat(pm_alt);
                }

                //sets the proper motion in azimuth including cos(alt)
                void set_pm_az_cosalt(double pm_az_cosalt)
                {
					this->motion.set_dlon_coslat(pm_az_cosalt);
                }

                //sets the radial_velocity
                void set_radial_velocity(double radial_velocity)
                {
					this->motion.set_ddist(radial_velocity);
                }

                //set value of motion
                void set_pm_alt_az_radial(double pm_alt, double pm_az_cosalt, double radial_velocity)
                {
                    this->motion.set_dlat_dlon_coslat_ddist(pm_alt, pm_az_cosalt, radial_velocity);
                }

                //set all the perameters of current frame object
                void set_frame_parameters
                (boost::astronomy::coordinate::spherical_equatorial_representation<boost::geometry::degree> const& location,
                    boost::units::quantity<boost::units::si::pressure> const& pressure,
					boost::units::quantity<boost::units::celsius::temperature> const& temperature,
                    boost::posix_time::ptime const& obs_time, double rel_humidity)
                {
                    this->earth_location = location;
                    this->pressure = pressure;
                    this->temperature = temperature;
                    this->obs_time = obs_time;
                    this->rel_humidity = rel_humidity;
                }

                //get all the perameters of current frame object
                std::tuple<                
                    boost::astronomy::coordinate::spherical_equatorial_representation<boost::geometry::degree>,
                    boost::units::quantity<boost::units::si::pressure>,
					boost::units::quantity<boost::units::celsius::temperature>,
                    boost::posix_time::ptime, double> get_frame_parameters() const
                {
                    return std::make_tuple
                    (this->earth_location, this->pressure, this->temperature, this->obs_time, this->rel_humidity);
                }

                //get earth location of the current object
                boost::astronomy::coordinate::spherical_equatorial_representation<boost::geometry::degree> get_location() const
                {
                    return this->earth_location;
                }

                //set earth location of the current object
                void set_location
                (boost::astronomy::coordinate::spherical_equatorial_representation<boost::geometry::degree> const& location)
                {
                    this->earth_location = location;
                }

                //get atmospheric pressure
                boost::units::quantity<boost::units::si::pressure> get_pressure() const
                {
                    return this->pressure;
                }

                //set atmospheric pressure
                void set_pressure(boost::units::quantity<boost::units::si::pressure> const& pressure)
                {
                    this->pressure = pressure;
                }

                //get temperature of the location
				boost::units::quantity<boost::units::celsius::temperature> get_temprature() const
                {
                    return this->temperature;
                }

                //set temperature of the location
                void set_temprature(boost::units::quantity<boost::units::celsius::temperature> const& temperature)
                {
                    this->temperature = temperature;
                }

                //get observation time 
                boost::posix_time::ptime get_obs_time() const
                {
                    return this->obs_time;
                }

                //set observation time 
                void set_obs_time(boost::posix_time::ptime const& time)
                {
                    this->obs_time = time;
                }

                //get relative humidity
                double get_rel_humidity() const
                {
                    return this->rel_humidity;
                }

                //set relative humidity
                void set_rel_humidity(double humidity)
                {
                    this->rel_humidity = humidity;
                }
            };
        } //namespace coordinate
    } //namespace astronomy
} //namespace boost
#endif // !BOOST_ASTRONOMY_COORDINATE_ALT_AZ_HPP

