#ifndef BOOST_ASTRONOMY_COORDINATE_GALACTIC_HPP
#define BOOST_ASTRONOMY_COORDINATE_GALACTIC_HPP

#include <tuple>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/algorithms/transform.hpp>
#include <boost/geometry/algorithms/equals.hpp>

#include <boost/astronomy/detail/is_base_template_of.hpp>
#include <boost/astronomy/coordinate/base_representation.hpp>
#include <boost/astronomy/coordinate/base_frame.hpp>
#include <boost/astronomy/coordinate/spherical_representation.hpp>
#include <boost/astronomy/coordinate/spherical_coslat_differential.hpp>

namespace boost
{
    namespace astronomy
    {
        namespace coordinate
        {
            template <typename RepresentationDegreeOrRadian = degree,
                typename DifferentialDegreeOrRadian = degree>
            struct galactic: public boost::astronomy::coordinate::base_frame
                <boost::astronomy::coordinate::spherical_representation<RepresentationDegreeOrRadian>,
                boost::astronomy::coordinate::spherical_coslat_differential<DifferentialDegreeOrRadian>>
            {
            public:
                //default constructor no initialization
                galactic() {}

                //!creates coordinate in galactic frame using any subclass of base_representation
                template <typename Representation>
                galactic(Representation const& representation_data)
                {
                    BOOST_STATIC_ASSERT_MSG((boost::astronomy::detail::is_base_template_of
                        <boost::astronomy::coordinate::base_representation, Representation>::value),
                        "Invalid representation class");

                    this->data = representation_data;
                }

                //!creates coordinate from given values
                //!b -> latitude, l -> longitude
                galactic(double b, double l, double distance)
                {
                    this->data.set_lat_lon_dist(b, l, distance);
                }

                //!creates coordinate with motion from given values
                //!b -> latitude, l -> longitude
                //!pm_b -> proper motion in b, pm_l_cosb -> proper motion in l including cos(b) 
                galactic(double b, double l, double distance, double pm_b, double pm_l_cosb, double radial_velocity):
                    galactic(b, l, distance)
                {
                    this->motion.set_dlat_dlon_coslat_ddist(pm_b, pm_l_cosb, radial_velocity);
                }

                //!creates coordinate with motion
                //!representation class is used for coordinate data
                //!differential class is used for motion data
                template <typename Representation, typename Differential>
                galactic(Representation const& representation_data, Differential const& diff)
                {
                    BOOST_STATIC_ASSERT_MSG((boost::astronomy::detail::is_base_template_of
                        <boost::astronomy::coordinate::base_representation, Representation>::value),
                        "argument type is expected to be a differential class");
                    this->data = representation_data;

                    BOOST_STATIC_ASSERT_MSG((boost::astronomy::detail::is_base_template_of
                        <boost::astronomy::coordinate::base_differential, Differential>::value),
                        "argument type is expected to be a differential class");
                    this->motion = diff;
                }

                //copy constructor
                galactic(galactic const& other)
                {
                    this->data = other.get_data();
                    this->motion = other.get_differential();
                }

                //!returns component b of the galactic coordinate
                double get_b() const
                {
                    return this->data.get_lat();
                }

                //!returns component l of the galactic coordinate
                double get_l() const
                {
                    return this->data.get_lon();
                }

                //!returns distance component of the galactic coordinate
                double get_distance() const
                {
                    return this->data.get_dist();
                }

                //!returns the (b, l, dist) in the form of tuple
                std::tuple<double, double, double> get_b_l_dist() const
                {
                    return this->data.get_lat_lon_dist();
                }

                //!returns proper motion in galactic latitude
                double get_pm_b() const
                {
                    return this->motion.get_dlat();
                }

                //!returns proper motion in galactic longitude including cos(b)
                double get_pm_l_cosb() const
                {
                    return this->motion.get_dlon_coslat();
                }

                //!returns radial_velocity
                double get_radial_velocity() const
                {
                    return this->motion.get_ddist();
                }

                //!returns the proper motion in form of tuple including cos(b)
                std::tuple<double, double, double> get_pm_b_l_radial() const
                {
                    return this->motion.get_dlat_dlon_coslat_ddist();
                }

                //!sets value of component b of the galactic coordinate
                double set_b(double b)
                {
                    this->data.set_lat(b);
                }

                //!sets value of component l of the galactic coordinate
                double set_l(double l) const
                {
                    this->data.set_lon(l);
                }

                //!sets value of distance component of the galactic coordinate
                double set_distance(double distance)
                {
                    this->data.set_dist(distance);
                }

                //!sets value of all component of the coordinate
                void set_b_l_dist(double b, double l, double dist)
                {
                    this->data.set_lat_lon_dist(b, l, dist);
                }

                //!sets the proper motion in galactic latitude
                double set_pm_b(double pm_b)
                {
                    this->motion.set_dlat(pm_b);
                }

                //!sets the proper motion in galactic longitude including cos(b)
                double set_pm_l_cosb(double pm_l_cosb)
                {
                    this->motion.set_dlon_coslat(pm_l_cosb);
                }

                //!sets the radial_velocity
                double set_radial_velocity(double radial_velocity)
                {
                    this->motion.set_ddist(radial_velocity);
                }

                //!set value of motion including cos(b)
                void set_pm_b_l_radial(double pm_b, double pm_l_cosb, double radial_velocity)
                {
                    this->motion.set_dlat_dlon_coslat_ddist(pm_b, pm_l_cosb, radial_velocity);
                }
            };
        } //namespace coordinate
    } //namespace astronomy
} //namespace boost
#endif // !BOOST_ASTRONOMY_COORDINATE_GALACTIC_HPP
