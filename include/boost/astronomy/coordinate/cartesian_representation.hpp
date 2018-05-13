#ifndef BOOST_ASTRONOMY_COORDINATE_CARTESIAN_REPRESENTATION_HPP
#define BOOST_ASTRONOMY_COORDINATE_CARTESIAN_REPRESENTATION_HPP


#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/arithmetic/cross_product.hpp>
#include <boost/geometry/arithmetic/dot_product.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/algorithms/transform.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/static_assert.hpp>

#include <boost/astronomy/coordinate/base_representation.hpp>


namespace boost
{
    namespace astronomy
    {
        namespace coordinate
        {
            struct cartesian_representation : public base_representation<3, boost::geometry::cs::cartesian>
            {
            public:
                cartesian_representation(double x, double y, double z=0.0)
                {
                    boost::geometry::set<0>(this->point, x);
                    boost::geometry::set<1>(this->point, y);
                    boost::geometry::set<2>(this->point, z);
                }

                template <int DimensionCount, typename Type>
                cartesian_representation(boost::geometry::model::point<double, DimensionCount, Type> pointObject)
                {
                    boost::geometry::transform(pointObject, this->point);
                }

                cartesian_representation(cartesian_representation &object)
                {
                    this->point = object.get_point();
                }

                template <typename Representation>
                cartesian_representation(Representation const& other)
                {
                    BOOST_STATIC_ASSERT_MSG((boost::is_template_base_of
                        <boost::astronomy::coordinate::base_representation, Representation>::value),
                        "No constructor found with given argument type");

                    boost::geometry::transform(other.get_point(), this->point);
                }
            }; //cartesian_representation
        } //namespace coordinate
    } //namespace astronomy
} //namespace boost

#endif // !BOOST_ASTRONOMY_COORDINATE_CARTESIAN_REPRESENTATION_HPP
