#ifndef BOOST_ASTRONOMY_COORDINATE_BASE_COORDINATE_SYSTEM_HPP
#define BOOST_ASTRONOMY_COORDINATE_BASE_COORDINATE_SYSTEM_HPP

#include <tuple>
#include <cmath>

#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/algorithms/transform.hpp>
#include <boost/geometry/algorithms/equals.hpp>
#include <boost/static_assert.hpp>

#include <boost/astronomy/coordinate/representation.hpp>
#include <boost/astronomy/coordinate/differential.hpp>
#include <boost/astronomy/detail/is_base_template_of.hpp>


namespace boost 
{
    namespace astronomy
    {
        namespace coordinate
        {
            typedef boost::geometry::degree degree;
            typedef boost::geometry::radian radian;

            template <typename Representation, typename Differential>
            struct base_frame
            {
            protected:
                Representation data;
                Differential motion;

            public:

                //!returns 2d propermotion
                std::tuple<double, double> proper_motion() const
                {
                    return std::make_tuple(boost::geometry::get<0>(data.get_differential()), 
                        boost::geometry::get<1>(data.get_differential()));
                }

                //!returns radial velocity (line of sight velocity) of the object
                double radial_velocity() const
                {
                    return boost::geometry::get<2>(data.get_differential());
                }

                /*!returns differential data in form of boost::geometry::model::point 
                having components (pm_lat, pm_lon, radial_velocity) including cos(lat) component*/
                Differential get_differential() const
                {
                    return motion;
                }

                //!set differential for the motion of the object
                template <typename OtherRepresentation>
                void set_differential(OtherRepresentation const& other)
                {
                    BOOST_STATIC_ASSERT_MSG((boost::astronomy::detail::is_base_template_of
                        <boost::astronomy::coordinate::base_differential, OtherRepresentation>::value),
                        "argument type is expected to be a differential class");

                    this->motion = other;
                }

                /*!returns coordinate data in form of boost::geometry::model::point
                having components (lat, lon, distance)*/
                Representation get_data() const
                {
                    return data;
                }

                //!returns data in specified subclass of base_representation
                template <typename ReturnType>
                ReturnType represen_as() const
                {
                    BOOST_STATIC_ASSERT_MSG((boost::astronomy::detail::is_base_template_of
                        <boost::astronomy::coordinate::base_representation, ReturnType>::value), 
                        "return type is expected to be a representation class");

                    return ReturnType(data);
                }

                //!angular separation between two coordinates in radians
                template <typename OtherCoordinate>
                double separation(OtherCoordinate const& other) const
                {
                    BOOST_STATIC_ASSERT_MSG((boost::astronomy::detail::is_base_template_of
                        <boost::astronomy::coordinate::base_frame, OtherCoordinate>::value),
                        "argument type is expected to be a coordinate class");

                    return std::acos(this->data.dot(other.get_data()));
                }

                
            };
        } //namespace coordinate
    } //namespace astronomy
} //namespace boost
#endif  // !BOOST_ASTRONOMY_COORDINATE_BASE_COORDINATE_SYSTEM_HPP
