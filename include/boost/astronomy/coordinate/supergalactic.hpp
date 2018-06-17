#ifndef BOOST_ASTRONOMY_COORDINATE_SUPERGALACTIC_HPP
#define BOOST_ASTRONOMY_COORDINATE_SUPERGALACTIC_HPP

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
            struct supergalactic : public boost::astronomy::coordinate::base_frame
                <boost::astronomy::coordinate::spherical_representation<RepresentationDegreeOrRadian>,
                boost::astronomy::coordinate::spherical_coslat_differential<DifferentialDegreeOrRadian>>
            {
            public:
                //default constructor no initialization
                supergalactic() {}

                //creates coordinate in supergalactic frame using any subclass of base_representation
                template <typename Representation>
                supergalactic(Representation const& representation_data)
                {
                    BOOST_STATIC_ASSERT_MSG((boost::is_base_template_of
                        <boost::astronomy::coordinate::base_representation, Representation>::value),
                        "Invalid representation class");

                    this->data = representation_data;
                }

                //creates coordinate from given values
                //sgb -> latitude, sgl -> longitude
                supergalactic(double sgb, double sgl, double distance)
                {
                    this->data.set_lat_lon_dist(sgb, sgl, distance);
                }

                //creates coordinate with motion from given values
                //sgb -> latitude, sgl -> longitude
                //pm_sgb -> proper motion in sgb, pm_sgl_cossgb -> proper motion in sgl including cos(sgb) 
                supergalactic(double sgb, double sgl, double distance, double pm_sgb, double pm_sgl_cossgb, double radial_velocity) :
                    supergalactic(sgb, sgl, distance)
                {
                    this->motion.set_dlat_dlon_coslat_ddist(pm_sgb, pm_sgl_cossgb, radial_velocity);
                }

                //creates coordinate with motion
                //representation class is used for coordinate data
                //differential class is used for motion data
                template <typename Representation, typename Differential>
                supergalactic(Representation const& representation_data, Differential const& diff)
                {
                    BOOST_STATIC_ASSERT_MSG((boost::is_base_template_of
                        <boost::astronomy::coordinate::base_representation, Representation>::value),
                        "argument type is expected to be a differential class");
                    this->data = representaion_data;

                    BOOST_STATIC_ASSERT_MSG((boost::is_base_template_of
                        <boost::astronomy::coordinate::base_differential, Differential>::value),
                        "argument type is expected to be a differential class");
                    this->motion = diff;
                }

                //copy constructor
                supergalactic(supergalactic const& other)
                {
                    this->data = other.get_data();
                    this->motion = other.get_differential();
                }

                //returns component sgb of the supergalactic coordinate
                double get_sgb() const
                {
                    return boost::geometry::get<0>(this->data.get_point());
                }

                //returns component sgl of the supergalactic coordinate
                double get_sgl() const
                {
                    return boost::geometry::get<1>(this->data.get_point());
                }

                //returns distance component of the supergalactic coordinate
                double get_distance() const
                {
                    return boost::geometry::get<2>(this->data.get_point());
                }

                //returns the (sgb, sgl, dist) in the form of tuple
                std::tuple<double, double, double> get_sgb_sgl_dist() const
                {
                    return this->data.get_lat_lon_dist();
                }

                //returns proper motion in supergalactic latitude
                double get_pm_sgb() const
                {
                    return boost::geometry::get<0>(this->motion.get_differential());
                }

                //returns proper motion in supergalactic longitude including cos(b)
                double get_pm_sgl_cossgb() const
                {
                    return boost::geometry::get<1>(this->motion.get_differential());
                }

                //returns radial_velocity
                double get_radial_velocity() const
                {
                    return boost::geometry::get<2>(this->motion.get_differential());
                }

                //returns the proper motion in form of tuple including cos(b)
                std::tuple<double, double, double> get_pm_sgb_sgl_radial() const
                {
                    return this->motion.get_dlat_dlon_coslat_ddist();
                }

                //sets value of component b of the supergalactic coordinate
                double set_sgb(double b)
                {
                    boost::geometry::set<0>(this->data.get_point(), sgb);
                }

                //sets value of component sgl of the supergalactic coordinate
                double set_sgl(double l) const
                {
                    boost::geometry::set<1>(this->data.get_point(), sgl);
                }

                //sets value of distance component of the supergalactic coordinate
                double set_distance(double distance)
                {
                    boost::geometry::set<2>(this->data.get_point(), distance);
                }

                //sets value of all component of the coordinate 
                void set_sgb_sgl_dist(double sgb, double sgl, double dist)
                {
                    this->data.set_lat_lon_dist(sgb, sgl, dist);
                }

                //sets the proper motion in supergalactic latitude
                double set_pm_sgb(double pm_sgb)
                {
                    boost::geometry::set<0>(this->motion.get_differential(), pm_sgb);
                }

                //sets the proper motion in supergalactic longitude including cos(b)
                double set_pm_sgl_cossgb(double pm_sgl_cossgb)
                {
                    boost::geometry::set<1>(this->motion.get_differential(), pm_sgl_cossgb);
                }

                //sets the radial_velocity
                double set_radial_velocity(double radial_velocity)
                {
                    boost::geometry::set<2>(this->motion.get_differential(), radial_velocity);
                }

                //set value of motion including cos(b)
                void set_pm_sgb_sgl_radial(double pm_sgb, double pm_sgl_cosb, double radial_velocity)
                {
                    this->motion.set_dlat_dlon_coslat_ddist(pm_sgb, pm_sgl_cosb, radial_velocity);
                }
            };
        } //namespace coordinate
    } //namespace astronomy
} //namespace boost
#endif // !BOOST_ASTRONOMY_COORDINATE_SUPERGALACTIC_HPP

