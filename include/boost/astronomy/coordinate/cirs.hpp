#ifndef BOOST_ASTRONOMY_COORDINATE_CIRS_HPP
#define BOOST_ASTRONOMY_COORDINATE_CIRS_HPP

#include <string>
#include <ctime>

#include <boost/astronomy/coordinate/base_equatorial_frame.hpp>

namespace boost
{
    namespace astronomy
    {
        namespace coordinate
        {
            template <typename RepresentationDegreeOrRadian = degree,
                typename DifferentialDegreeOrRadian = degree>
            struct cirs : public boost::astronomy::coordinate::base_equatorial_frame
                <RepresentationDegreeOrRadian, DifferentialDegreeOrRadian>
            {
            protected:
                //time used to determine the position of earth at the time of observation
                tm obstime;

            public:
                //default constructor no initialization
                cirs() {}

                template <typename Representation>
                cirs(Representation const& representation_data) : base_equatorial_frame(representation_data) {}

                //RA is expected to be a double if value is in degree/radian
                //if want to provide value in hours minute sec formate then a string expected with particular format
                //hour angle formate: "hhmmss..."
                //first two char as hours next two as minutes and remaining are treated as seconds
                //hour angles are converted to degree/radian and then stored
                //eg: if RA = 06h 45m 08.9s then value should be provided like "064508.9"
                template <typename RaType>
                cirs(double dec, RaType ra, double distance) : base_equatorial_frame(dec, ra, distance) {}

                template <typename RaType>
                cirs(double dec, RaType ra, double distance, double pm_dec, double pm_ra_cosdec, double radial_velocity) :
                    base_equatorial_frame(dec, ra, dustance, pm_dec, pm_ra_cosdec, radial_velocity) {}

                template <typename Representation, typename Differential>
                cirs(Representation const& representation_data, Differential const& diff) :
                    base_equatorial_frame(representation_data, diff) {}

                tm get_obstime() const
                {
                    return this->obstime;
                }

                void set_obstime(tm const& time)
                {
                    this->obstime = time;
                }

            };
        } //namespace coordinate
    } //namespace astronomy
} //namespace boost

#endif // !BOOST_ASTRONOMY_COORDINATE_CIRS_HPP

