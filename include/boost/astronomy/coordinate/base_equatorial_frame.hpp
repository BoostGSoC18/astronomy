#ifndef BOOST_ASTRONOMY_COORDINATE_BASE_EQUATORIAL_FRAME_HPP
#define BOOST_ASTRONOMY_COORDINATE_BASE_EQUATORIAL_FRAME_HPP

#include <type_traits>
#include <string>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/algorithms/transform.hpp>
#include <boost/geometry/algorithms/equals.hpp>
#include <boost/lexical_cast.hpp>

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
            template <typename RepresentationDegreeOrRadian = degree,
                typename DifferentialDegreeOrRadian = degree>
            struct base_equatorial_frame: public boost::astronomy::coordinate::base_frame
                <boost::astronomy::coordinate::spherical_representation<RepresentationDegreeOrRadian>,
                boost::astronomy::coordinate::spherical_coslat_differential<DifferentialDegreeOrRadian>>
            {
            public:
                //default constructor no initialization
                base_equatorial_frame() {}

                template <typename Representation>
                base_equatorial_frame(Representation const& representation_data)
                {
                    BOOST_STATIC_ASSERT_MSG((boost::is_base_template_of
                        <boost::astronomy::coordinate::base_representation, Representation>::value),
                        "argument type is expected to be a representation class");
                    this->data = representation_data;
                }

                template <typedef RaType>
                base_equatorial_frame(double dec, RaType ra, double distance)
                {
                    double ra_final;
                    if (std::is_same<RaType, std::string>::value)
                    {
                        if (std::is_same<RepresentationDegreeOrRadian, degree>::value)
                        {
                            ra_final = boost::lexical_cast<double>(ra.substr(0, 2)) * 15 +
                                boost::lexical_cast<double>(ra.substr(3, 2)) * 60 +
                                boost::lexical_cast<double>(ra.substr(4)) * 3600;
                        }
                        else
                        {
                            ra_final = (boost::lexical_cast<double>(ra.substr(0, 2)) * 15 +
                                boost::lexical_cast<double>(ra.substr(3, 2)) * 60 +
                                boost::lexical_cast<double>(ra.substr(4)) * 3600) * 0.0174533;
                        }
                    }
                    else {
                        ra_final = ra;
                    }
                    this->data.set_lat_lon_dist(dec, ra_final, distance);
                }

                template <typedef RaType>
                base_equatorial_frame(double dec, RaType ra, double distance, double pm_dec, double pm_ra_cosdec, double radial_velocity):
                    base_equatorial_frame(dec, ra, distance)
                {
                    this->motion.set_dlat_dlon_coslat_ddist(pm_dec, pm_ra_cosdec, radial_velocity);
                }

                template <typename Representation, typename Differential>
                base_equatorial_frame(Representation const& representation_data, Differentail const& diff)
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

                //returns Declination component of the coordinate
                double get_dec() const
                {
                    return boost::geometry::get<0>(this->data.get_point());
                }

                //returns Right Ascension component of the coordinate
                double get_ra() const
                {
                    return boost::geometry::get<1>(this->data.get_point());
                }

                //returns distance component of the coordinate
                double get_distance() const
                {
                    return boost::geometry::get<2>(this->data.get_point());
                }

                //returns proper motion in Declination
                double get_pm_dec() const
                {
                    return boost::geometry::get<0>(this->motion.get_differential());
                }

                //returns proper motion in Right Ascension including cos(dec)
                double get_pm_ra_cosdec() const
                {
                    return boost::geometry::get<1>(this->motion.get_differential());
                }

                //returns radial_velocity
                double get_radial_velocity() const
                {
                    return boost::geometry::get<2>(this->motion.get_differential());
                }

                //sets value of Declination component of the coordinate
                double set_dec(double dec)
                {
                    boost::geometry::set<0>(this->data.get_point(), dec);
                }

                //sets value of Right Ascension component of the coordinate
                template <typename RaType>
                double set_ra(RaType ra)
                {
                    double ra_final;
                    if (std::is_same<RaType, std::string>::value)
                    {
                        if (std::is_same<RepresentationDegreeOrRadian, degree>::value)
                        {
                            ra_final = boost::lexical_cast<double>(ra.substr(0, 2)) * 15 +
                                boost::lexical_cast<double>(ra.substr(3, 2)) * 60 +
                                boost::lexical_cast<double>(ra.substr(4)) * 3600;
                        }
                        else
                        {
                            ra_final = (boost::lexical_cast<double>(ra.substr(0, 2)) * 15 +
                                boost::lexical_cast<double>(ra.substr(3, 2)) * 60 +
                                boost::lexical_cast<double>(ra.substr(4)) * 3600) * 0.0174533;
                        }
                    }
                    else {
                        ra_final = ra;
                    }
                    boost::geometry::set<1>(this->data.get_point(), ra_final);
                }

                //sets value of distance component of the coordinate
                double set_distance(double distance)
                {
                    boost::geometry::set<2>(this->data.get_point(), distance);
                }

                //sets the proper motion in Declination
                double set_pm_dec(double pm_dec)
                {
                    boost::geometry::set<0>(this->motion.get_differential(), pm_dec);
                }

                //sets the proper motion in Right Ascension including cos(dec)
                double set_pm_ra_cosdec(double pm_ra_cosdec)
                {
                    boost::geometry::set<1>(this->motion.get_differential(), pm_ra_cosdec);
                }

                //sets the radial_velocity
                double set_radial_velocity(double radial_velocity)
                {
                    boost::geometry::set<2>(this->motion.get_differential(), radial_velocity);
                }
            };

        } //namespace coordinate
    } //namespace astronomy
} //namespace boost
#endif // !BOOST_ASTRONOMY_COORDINATE_BASE_EQUATORIAL_FRAME_HPP

