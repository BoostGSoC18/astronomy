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
#include <boost/astronomy/coordinate/cartesian_representation.hpp>

namespace boost
{
    namespace astronomy
    {
        namespace coordinate
        {
            template<typename DegreeOrRadian>
            struct spherical_representation : public boost::astronomy::coordinate::base_representation
                <3, boost::geometriy::cs::spherical<DegreeOrRadian>>
            {
            public:
                spherical_representation() {}

                spherical_representation(double lat, double, lon, double distance)
                {
                    boost::geometry::set<0>(this->point, lat);
                    boost::geometry::set<1>(this->point, lon);
                    boost::geometry::set<2>(this->point, distance);
                }

                template<int DimensionCount, typename Type>
                spherical_representation(boost::geometry::model::point<double, DimensionCount, Type> const& pointObject)
                {
                    boost::geometry::model::point<double, 3, boost::geometry::cs::cartesian> temp;
                    boost::geometry::transform(pointObject, temp);
                    boost::geometry::transform(temp, this->point);
                }

                template <typename OtherDegreeOrRadian>
                spherical_representation(spherical_representation<OtherDegreeOrRadian> const& other)
                {
                    boost::geometry::transform(other.get_point(), this->point);
                }

                template <typename Representation>
                spherical_representaion(Representation const& other)
                {
                    BOOST_STATIC_ASSERT_MSG((boost::is_base_template_of
                        <boost::astronomy::coordinate::base_representation, Representation>::value),
                        "No constructor found with given argument type");

                    boost::geometry::model::point<double, 3, boost::geometry::cs::cartesian> temp;
                    boost::geometry::transform(other, temp);
                    boost::geometry::transform(temp, this->point);
                }

                // returns the (lat, lon, distance) in the form of tuple
                std::tuple<double, double, double> get_lat_lon_dist() const
                {
                    return std::make_tuple(boost::geometry::get<0>(this->point),
                        boost::geometry::get<1>(this->point), boost::geometry::get<2>(this->point));
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

                //returns the distance component of point
                double get_lon() const
                {
                    return boost::geometry::get<2>(this->point);
                }

                //set value of (lat, lon, distance) in current object
                void set_lat_lon_dist(double lat, double lon, double distance)
                {
                    boost::geometry::set<0>(this->point, lat);
                    boost::geometry::set<1>(this->point, lon);
                    boost::geometry::set<2>(this->point, distance);
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

                //set value of distance component of point
                void set_dist(double distance)
                {
                    boost::geometry::set<2>(this->point, distance);
                }
            };
        }//namespace coordinate
    } //namespace astronomy
} //namespace boost
#endif // !BOOST_ASTRONOMY_COORDINATE_SPHERICAL_REPRESENTATION_HPP


