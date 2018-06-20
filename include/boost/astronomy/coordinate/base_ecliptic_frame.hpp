#ifndef BOOST_ASTRONOMY_COORDINATE_BASE_ECLIPTIC_FRAME_HPP
#define BOOST_ASTRONOMY_COORDINATE_BASE_ECLIPTIC_FRAME_HPP

#include <type_traits>
#include <string>
#include <ctime>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/algorithms/transform.hpp>
#include <boost/geometry/algorithms/equals.hpp>

#include <boost/is_base_template_of.hpp>
#include <boost/astronomy/coordinate/base_frame.hpp>
#include <boost/astronomy/coordinate/spherical_representation.hpp>
#include <boost/astronomy/coordinate/spherical_coslat_differential.hpp>

namespace boost
{
    namespace astronomy
    {
        namespace coordinate
        {
            template <typename RepresentationDegreeOrRadian = boost::astronomy::coordinate::degree,
                typename DifferentialDegreeOrRadian = boost::astronomy::coordinate::degree>
            struct base_ecliptic_frame : public boost::astronomy::coordinate::base_frame
                <boost::astronomy::coordinate::spherical_representation<RepresentationDegreeOrRadian>,
                boost::astronomy::coordinate::spherical_coslat_differential<DifferentialDegreeOrRadian>>
            {
            protected:
                tm equinox;

            public:
                //default constructor no initialization
                base_ecliptic_frame() {}

                template <typename Representation>
                base_ecliptic_frame(Representation const& representation_data)
                {
                    BOOST_STATIC_ASSERT_MSG((boost::is_base_template_of
                        <boost::astronomy::coordinate::base_representation, Representation>::value),
                        "argument type is expected to be a representation class");
                    this->data = representation_data;
                }

                base_ecliptic_frame(double lat, double lon, double distance)
                {
                    this->data.set_lat_lon_dist(lat, lon, distance);
                }

                base_ecliptic_frame
                (double lat, double lon, double distance, double pm_lat, double pm_lon_coslat, double radial_velocity) :
                    base_ecliptic_frame(lat, lon, distance)
                {
                    this->motion.set_dlat_dlon_coslat_ddist(pm_lat, pm_lon_coslat, radial_velocity);
                }

                template <typename Representation, typename Differential>
                base_ecliptic_frame(Representation const& representation_data, Differential const& diff)
                {
                    BOOST_STATIC_ASSERT_MSG((boost::is_base_template_of
                        <boost::astronomy::coordinate::base_representation, Representation>::value),
                        "argument type is expected to be a representation class");
                    this->data = representation_data;

                    BOOST_STATIC_ASSERT_MSG((boost::is_base_template_of
                        <boost::astronomy::coordinate::base_differential, Differential>::value),
                        "argument type is expected to be a differential class");
                    this->motion = diff;
                }

                //returns latitude component of the coordinate
                double get_lat() const
                {
                    return boost::geometry::get<0>(this->data.get_point());
                }

                //returns longitude component of the coordinate
                double get_lon() const
                {
                    return boost::geometry::get<1>(this->data.get_point());
                }

                //returns distance component of the coordinate
                double get_distance() const
                {
                    return boost::geometry::get<2>(this->data.get_point());
                }

                //returns the (lat, lon, dist) in the form of tuple
                std::tuple<double, double, double> get_lat_lon_dist() const
                {
                    return this->data.get_lat_lon_dist();
                }

                //returns proper motion in latitude
                double get_pm_lat() const
                {
                    return boost::geometry::get<0>(this->motion.get_differential());
                }

                //returns proper motion in longitude including cos(lat)
                double get_pm_lon_coslat() const
                {
                    return boost::geometry::get<1>(this->motion.get_differential());
                }

                //returns radial_velocity
                double get_radial_velocity() const
                {
                    return boost::geometry::get<2>(this->motion.get_differential());
                }

                //returns the proper motion in form of tuple
                std::tuple<double, double, double> get_pm_lat_lon_radial() const
                {
                    return this->motion.get_dlat_dlon_coslat_ddist();
                }

                //sets value of latitude component of the coordinate
                void set_lat(double lat)
                {
                    boost::geometry::set<0>(this->data.get_point(), lat);
                }

                //sets value of longitude component of the coordinate
                void set_lon(double lon)
                {
                    boost::geometry::set<1>(this->data.get_point(), lon);
                }

                //sets value of distance component of the coordinate
                void set_distance(double distance)
                {
                    boost::geometry::set<2>(this->data.get_point(), distance);
                }

                //sets value of all component of the coordinate
                void set_alt_az_dist(double lat, double lon, double dist)
                {
                    this->data.set_lat_lon_dist(lat, lon, dist);
                }

                //sets the proper motion in latitude
                void set_pm_lat(double pm_lat)
                {
                    boost::geometry::set<0>(this->motion.get_differential(), pm_lat);
                }

                //sets the proper motion in longitude including cos(lat)
                void set_pm_lon_coslat(double pm_lon_coslat)
                {
                    boost::geometry::set<1>(this->motion.get_differential(), pm_lon_coslat);
                }

                //sets the radial_velocity
                void set_radial_velocity(double radial_velocity)
                {
                    boost::geometry::set<2>(this->motion.get_differential(), radial_velocity);
                }

                //set value of motion  including cos(b)
                void set_pm_alt_az_radial(double pm_lat, double pm_lon_coslat, double radial_velocity)
                {
                    this->motion.set_dlat_dlon_coslat_ddist(pm_lat, pm_lon_coslat, radial_velocity);
                }

                tm get_equinox() const
                {
                    return this->equinox;
                }

                void set_equinox(tm const& time)
                {
                    this->equinox = boost::posix_time::from_iso_string(time);
                }
            };

        } //namespace coordinate
    } //namespace astronomy
} //namespace boost
#endif // !BOOST_ASTRONOMY_COORDINATE_BASE_ECLIPTIC_FRAME_HPP


