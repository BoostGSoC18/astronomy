#ifndef BOOST_ASTRONOMY_COORDINATE_SPHERICAL_REPRESENTATION_HPP
#define BOOST_ASTRONOMY_COORDINATE_SPHERICAL_REPRESENTATION_HPP


#include <tuple>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/algorithms/transform.hpp>
#include <boost/geometry/algorithms/equals.hpp>
#include <boost/static_assert.hpp>

#include <boost/astronomy/detail/is_base_template_of.hpp>
#include <boost/astronomy/coordinate/base_representation.hpp>
#include <boost/astronomy/coordinate/cartesian_representation.hpp>
#include <boost/astronomy/coordinate/spherical_differential.hpp>
#include <boost/astronomy/coordinate/spherical_coslat_differential.hpp>


namespace boost
{
    namespace astronomy
    {
        namespace coordinate
        {
            //!Represents the coordinate in spherical representation
            //!Uses three components to represent a point/vector (latitude, longitude, distance)
            template <typename DegreeOrRadian>
            struct spherical_representation : public boost::astronomy::coordinate::base_representation
                <3, boost::geometry::cs::spherical<DegreeOrRadian>>
            {
            public:
                //default constructor no initialization
                spherical_representation() {}

                //!constructs object from provided value of coordinates (latitude, longitude, distance)
                spherical_representation(double lat, double lon, double distance = 1.0)
                {
                    boost::geometry::set<0>(this->point, lat);
                    boost::geometry::set<1>(this->point, lon);
                    boost::geometry::set<2>(this->point, distance);
                }

                //!constructs object from boost::geometry::model::point object
                template<int DimensionCount, typename Type>
                spherical_representation(boost::geometry::model::point<double, DimensionCount, Type> const& pointObject)
                {
                    boost::geometry::model::point<double, 3, boost::geometry::cs::cartesian> temp;
                    boost::geometry::transform(pointObject, temp);
                    boost::geometry::transform(temp, this->point);
                }

                //copy constructor
                spherical_representation(spherical_representation<DegreeOrRadian> const& other)
                {
                    this->point = other.get_point();
                }

                //!constructs object from any type of representation
                template <typename Representation>
                spherical_representation(Representation const& other)
                {
                    BOOST_STATIC_ASSERT_MSG((boost::astronomy::detail::is_base_template_of
                        <boost::astronomy::coordinate::base_representation, Representation>::value),
                        "No constructor found with given argument type");

                    boost::geometry::model::point<double, 3, boost::geometry::cs::cartesian> temp;
                    boost::geometry::transform(other.get_point(), temp);
                    boost::geometry::transform(temp, this->point);
                }

                //! returns the (lat, lon, distance) in the form of tuple
                std::tuple<double, double, double> get_lat_lon_dist() const
                {
                    return std::make_tuple(boost::geometry::get<0>(this->point),
                        boost::geometry::get<1>(this->point), boost::geometry::get<2>(this->point));
                }

                //!returns the lat component of point
                double get_lat() const
                {
                    return boost::geometry::get<0>(this->point);
                }

                //!returns the lon component of point
                double get_lon() const
                {
                    return boost::geometry::get<1>(this->point);
                }

                //!returns the distance component of point
                double get_dist() const
                {
                    return boost::geometry::get<2>(this->point);
                }

                //!set value of (lat, lon, distance) in current object
                void set_lat_lon_dist(double lat, double lon, double distance)
                {
                    boost::geometry::set<0>(this->point, lat);
                    boost::geometry::set<1>(this->point, lon);
                    boost::geometry::set<2>(this->point, distance);
                }

                //!set value of lat component of point
                void set_lat(double lat)
                {
                    boost::geometry::set<0>(this->point, lat);
                }

                //!set value of lon component of point
                void set_lon(double lon)
                {
                    boost::geometry::set<1>(this->point, lon);
                }

                //!set value of distance component of point
                void set_dist(double distance)
                {
                    boost::geometry::set<2>(this->point, distance);
                }

                boost::astronomy::coordinate::spherical_representation<DegreeOrRadian>
                    operator +(boost::astronomy::coordinate::spherical_differential<DegreeOrRadian> const& diff) const
                {
                    boost::astronomy::coordinate::spherical_representation<DegreeOrRadian> temp(this->point);

                    temp.set_lat(temp.get_lat() + diff.get_dlat());
                    temp.set_lon(temp.get_lon() + diff.get_dlon());
                    temp.set_dist(temp.get_dist() + diff.get_ddist());

                    return temp;
                }

                boost::astronomy::coordinate::spherical_representation<DegreeOrRadian>
                    operator +(boost::astronomy::coordinate::spherical_coslat_differential<DegreeOrRadian> const& diff) const
                {
                    boost::astronomy::coordinate::spherical_representation<DegreeOrRadian> temp(this->diff);

                    temp.set_dlat(temp.get_lat() + diff.get_dlat());
                    temp.set_dlon_coslat(temp.get_lon() + diff.get_dlon_coslat());
                    temp.set_ddist(temp.get_dist() + diff.get_ddist());

                    return temp;
                }
            };
        }//namespace coordinate
    } //namespace astronomy
} //namespace boost
#endif // !BOOST_ASTRONOMY_COORDINATE_SPHERICAL_REPRESENTATION_HPP


