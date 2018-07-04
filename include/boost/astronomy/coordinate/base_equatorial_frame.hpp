#ifndef BOOST_ASTRONOMY_COORDINATE_BASE_EQUATORIAL_FRAME_HPP
#define BOOST_ASTRONOMY_COORDINATE_BASE_EQUATORIAL_FRAME_HPP

#include <type_traits>
#include <string>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/algorithms/transform.hpp>
#include <boost/geometry/algorithms/equals.hpp>
#include <boost/lexical_cast.hpp>

#include <boost/astronomy/detail/is_base_template_of.hpp>
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
            struct base_equatorial_frame : public boost::astronomy::coordinate::base_frame
                <boost::astronomy::coordinate::spherical_representation<RepresentationDegreeOrRadian>,
                boost::astronomy::coordinate::spherical_coslat_differential<DifferentialDegreeOrRadian>>
            {
            public:
                //default constructor no initialization
                base_equatorial_frame() {}

                template <typename Representation>
                base_equatorial_frame(Representation const& representation_data)
                {
                    BOOST_STATIC_ASSERT_MSG((boost::astronomy::detail::is_base_template_of
                        <boost::astronomy::coordinate::base_representation, Representation>::value),
                        "argument type is expected to be a representation class");
                    this->data = representation_data;
                }

                
                //if want to provide value in hours:minute:sec formate then a string expected with particular format
                //hour angle formate: "hhmmss..."
                //first two char as hours next two as minutes and remaining are treated as seconds
                //hour angles are converted to degree/radian and then stored
                //eg: if RA = 06h 45m 08.9s then value should be provided like "064508.9"           
                base_equatorial_frame(double dec, std::string const& ra, double distance)
                {
                    double ra_final;
                    
                    if (std::is_same<RepresentationDegreeOrRadian, degree>::value)
                    {
                        ra_final = (boost::lexical_cast<double>(ra.substr(0, 2)) * 15.0) +
                            (boost::lexical_cast<double>(ra.substr(2, 2)) / 4.0) +
                            (boost::lexical_cast<double>(ra.substr(4)) / 240.0);
                    }
                    else
                    {
                        ra_final = ((boost::lexical_cast<double>(ra.substr(0, 2)) * 15.0) +
                            (boost::lexical_cast<double>(ra.substr(2, 2)) / 4.0) +
                            (boost::lexical_cast<double>(ra.substr(4)) / 240.0)) * 0.0174533;
                    }
                    
                    this->data.set_lat_lon_dist(dec, ra_final, distance);
                }

                //RA is expected to be a double if value is in degree/radian
                base_equatorial_frame(double dec, double ra, double distance)
                {
                    this->data.set_lat_lon_dist(dec, ra, distance);
                }

                template <typename RaType>
                base_equatorial_frame
                (double dec, RaType const& ra, double distance, double pm_dec, double pm_ra_cosdec, double radial_velocity):
                    base_equatorial_frame(dec, ra, distance)
                {
                    this->motion.set_dlat_dlon_coslat_ddist(pm_dec, pm_ra_cosdec, radial_velocity);
                }

                template <typename Representation, typename Differential>
                base_equatorial_frame(Representation const& representation_data, Differential const& diff)
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

                //returns the (dec, ra, dist) in the form of tuple
                std::tuple<double, double, double> get_dec_ra_dist() const
                {
                    return this->data.get_lat_lon_dist();
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

                //returns the proper motion in form of tuple including cos(dec)
                std::tuple<double, double, double> get_pm_dec_ra_radial() const
                {
                    return this->motion.get_dlat_dlon_coslat_ddist();
                }

                //sets value of Declination component of the coordinate
                void set_dec(double dec)
                {
                    boost::geometry::set<0>(this->data.get_point(), dec);
                }

                //sets value of Right Ascension component of the coordinate
                //if want to provide value in hours:minute:sec formate then a string expected with particular format
                //hour angle formate: "hhmmss..."
                //first two char as hours next two as minutes and remaining are treated as seconds
                //hour angles are converted to degree/radian and then stored
                //eg: RA = 06h 45m 08.9s then value should be provided like "064508.9"
                void set_ra(std::string const& ra)
                {
                    double ra_final;
                    
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
                    
                    boost::geometry::set<1>(this->data.get_point(), ra_final);
                }
                
                //sets value of Right Ascension component of the coordinate
                //RA is expected to be a double if value is in degree/radian
                void set_ra(double ra)
                {
                    boost::geometry::set<1>(this->data.get_point(), ra);
                }


                //sets value of distance component of the coordinate
                void set_distance(double distance)
                {
                    boost::geometry::set<2>(this->data.get_point(), distance);
                }

                //sets value of all component of the coordinate 
                void set_dec_ra_dist(double dec, double ra, double dist)
                {
                    this->data.set_lat_lon_dist(dec, ra, dist);
                }

                //sets value of all component of the coordinate (ra in hour angle)
                void set_dec_ra_dist(double dec, std::string ra, double dist)
                {
                    double ra_final;

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
                    this->data.set_lat_lon_dist(dec, ra_final, dist);
                }

                //sets the proper motion in Declination
                void set_pm_dec(double pm_dec)
                {
                    boost::geometry::set<0>(this->motion.get_differential(), pm_dec);
                }

                //sets the proper motion in Right Ascension including cos(dec)
                void set_pm_ra_cosdec(double pm_ra_cosdec)
                {
                    boost::geometry::set<1>(this->motion.get_differential(), pm_ra_cosdec);
                }

                //sets the radial_velocity
                void set_radial_velocity(double radial_velocity)
                {
                    boost::geometry::set<2>(this->motion.get_differential(), radial_velocity);
                }

                //set value of motion including cos(dec)
                void set_pm_dec_ra_radial(double pm_dec, double pm_ra_cosdec, double radial_velocity)
                {
                    this->motion.set_dlat_dlon_coslat_ddist(pm_dec, pm_ra_cosdec, radial_velocity);
                }
            };

        } //namespace coordinate
    } //namespace astronomy
} //namespace boost
#endif // !BOOST_ASTRONOMY_COORDINATE_BASE_EQUATORIAL_FRAME_HPP

