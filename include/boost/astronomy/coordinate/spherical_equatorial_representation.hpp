#ifndef BOOST_ASTRONOMY_COORDINATE_SPHERICAL_EQUATORIAL_REPRESENTATION_HPP
#define BOOST_ASTRONOMY_COORDINATE_SPHERICAL_EQUATORIAL_REPRESENTATION_HPP


#include <tuple>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/algorithms/transform.hpp>
#include <boost/geometry/algorithms/equals.hpp>
#include <boost/static_assert.hpp>

#include <boost/astronomy/detail/is_base_template_of.hpp>
#include <boost/astronomy/coordinate/base_representation.hpp>
#include <boost/astronomy/coordinate/cartesian_representation.hpp>
#include <boost/astronomy/coordinate/spherical_equatorial_differential.hpp>


namespace boost
{
    namespace astronomy
    {
        namespace coordinate
        {
            //Represents the coordinate in spherical representation on unit sphere
            //Uses two components to represent a point/vector (latitude, longitude)
            template <typename DegreeOrRadian>
            struct spherical_equatorial_representation : public boost::astronomy::coordinate::base_representation
                <2, boost::geometry::cs::spherical_equatorial<DegreeOrRadian>>
            {
            public:
                //default constructor no initialization
                spherical_equatorial_representation(){}

                //constructs object from provided value of coordinates (latitude, longitude)
                spherical_equatorial_representation(double lat, double lon)
                {
                    boost::geometry::set<0>(this->point, lat);
                    boost::geometry::set<1>(this->point, lon);
                }

                //constructs object from boost::geometry::model::point object
                template <int DimensionCount, typename Type>
                spherical_equatorial_representation(boost::geometry::model::point<double, DimensionCount, Type> const& pointObject)
                {
                    boost::astronomy::coordinate::cartesian_representation temp = pointObject;
                    boost::geometry::transform(temp.unit_vector
                        <boost::astronomy::coordinate::cartesian_representation>().get_point(), this->point);
                }

                //copy constructor
                spherical_equatorial_representation(spherical_equatorial_representation<DegreeOrRadian> const& object)
                {
                    this->point = object.get_point();
                }

                //constructs object from any type of representation
                template <typename Representation>
                spherical_equatorial_representation(Representation const& other)
                {
                    BOOST_STATIC_ASSERT_MSG((boost::astronomy::detail::is_base_template_of
                        <boost::astronomy::coordinate::base_representation, Representation>::value),
                        "No constructor found with given argument type");

                    boost::astronomy::coordinate::cartesian_representation temp = other;
                    boost::geometry::transform(temp.unit_vector
                        <boost::astronomy::coordinate::cartesian_representation>().get_point(), this->point);

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
                void set_lat_lon(double lat, double lon)
                {
                    boost::geometry::set<0>(this->point, lat);
                    boost::geometry::set<1>(this->point, lon);
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

                template <typename DiffDegreeOrRadian>
                boost::astronomy::coordinate::spherical_equatorial_representation<DegreeOrRadian>
                    operator +(boost::astronomy::coordinate::spherical_equatorial_differential<DiffDegreeOrRadian> const& diff) const
                {
                    boost::astronomy::coordinate::spherical_equatorial_representation<DegreeOrRadian> temp(this->point);

                    temp.set_lat(temp.get_lat() + diff.get_dlat());
                    temp.set_lon(temp.get_lon() + diff.get_dlon());

                    return temp;
                }
            };
        }
    }
}
#endif // !BOOST_ASTRONOMY_COORDINATE_SPHERICAL_EQUATORIAL__REPRESENTATION_HPP

