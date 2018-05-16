#ifndef BOOST_ASTRONOMY_COORDINATE_SPHERICAL_REPRESENTATION_HPP
#define BOOST_ASTRONOMY_COORDINATE_SPHERICAL_REPRESENTATION_HPP


#include <tuple>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/algorithms/transform.hpp>
#include <boost/geometry/algorithms/equals.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp>

#include <boost/astronomy/coordinate/base_representation.hpp>


namespace boost
{
    namespace astronomy
    {
        namespace coordinate
        {
            //Represents the coordinate in spherical representation on unit sphere
            template <typename DegreeOrRadian>
            struct spherical_equatorial_representation : public boost::astronomy::coordinate::base_representation
                <2, boost::geometry::cs::spherical_equatorial<DegreeOrRadian>>
            {
            public:
                spherical_equatorial_representation(){}

                spherical_equatorial_representation(double lat, double lon)
                {
                    boost::geometry::set<0>(this->point, lat);
                    boost::geometry::set<1>(this->point, lon);
                }

                template <int DimensionCount, typename Type>
                spherical_equatorial_representation(boost::geometry::model::point<double, DimensionCount, Type> pointObject)
                {
                    boost::geometry::transform(pointObject, this->point);
                }

                spherical_equatorial_representation(spherical_equatorial_representation &object)
                {
                    this->point = object.get_point();
                }

                template <typename Representation>
                spherical_equatorial_representation(Representation const& other)
                {
                    BOOST_STATIC_ASSERT_MSG((boost::is_base_template_of
                        <boost::astronomy::coordinate::base_representation, Representation>::value),
                        "No constructor found with given argument type");

                    boost::geometry::transform(other.get_point(), this->point);
                }
                // returns the (lat, lon) in the form of tuple
                std::tuple<double, double> get_lat_lon() const
                {
                    return std::make_tuple(boost::geometry::get<0>(this->point), boost::geometry::get<1>(this->point));
                }

                //returns the lat component of point
                double get_lat() const
                {
                    return boost::geometry::get<0>(this->point);
                }

                //returns the lon component of point
                double get_lon() const
                {
                    return boost::geometry::get<1>(this->point);
                }

                //set value of (lat, lon) in current object
                void set_lat_lon(double x, double y)
                {
                    boost::geometry::set<0>(this->point, x);
                    boost::geometry::set<1>(this->point, y);
                }

                //set value of lat component of point
                void set_lat(double lat)
                {
                    boost::geometry::set<0>(this->point, lat);
                }

                //set value of lon component of point
                void set_lon(double lon)
                {
                    boost::geometry::set<1>(this->point, lon);
                }
            };
        }
    }
}
#endif // !BOOST_ASTRONOMY_COORDINATE_SPHERICAL_REPRESENTATION_HPP

