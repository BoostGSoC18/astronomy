#ifndef BOOST_ASTRONOMY_COORDINATE_BASE_REPRESENTATION_HPP
#define BOOST_ASTRONOMY_COORDINATE_BASE_REPRESENTATION_HPP


#include <cmath>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/algorithms/transform.hpp>
#include <boost/geometry/arithmetic/cross_product.hpp>
#include <boost/geometry/arithmetic/dot_product.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/static_assert.hpp>

namespace boost
{
    // structure to provide support like std::is_base_of for template base classes
    template <template <typename...> class Base, typename Derived>
    struct base_template
    {
        using U = typename std::remove_cv<Derived>::type;

        template <typename... Args>
        static std::true_type test(Base<Args...>*);

        static std::false_type test(void*);

        using type = decltype(test(std::declval<U*>()));
    };

    template <template <typename...> class Base, typename Derived>
    using is_template_base_of = typename base_template<Base, Derived>::type;

    namespace astronomy
    {
        namespace coordinate
        {
            // abstract structure which is the base for all the representation 
            template <int DimensionCount, typename Type>
            struct base_representation: public representation
            {
            protected:
                boost::geometry::model::point<double, DimensionCount, Type> point;
            public:
                
                // cross prodct of current vector with specified vector
                template <typename ReturnType, typename Representation>
                virtual ReturnType cross(Representation const& other) const
                {
                    /*both the coordinates/vector are first converted into cartesian coordinate system then
                    cross product of both cartesian vectors is converted into requested type and returned*/

                    /*checking types of argument and return type*/
                    BOOST_STATIC_ASSERT_MSG((boost::is_template_base_of
                        <boost::astronomy::coordinate::base_representation, Representation>::value),
                        "function argument type is expected to be a representation class");

                    BOOST_STATIC_ASSERT_MSG((boost::is_template_base_of
                        <boost::astronomy::coordinate::base_representation, ReturnType>::value), 
                        "return type is expected to be a representation class");

                    /*converting both coordinates/vector into cartesian system*/
                    boost::geometry::model::point<double, 3, boost::geometry::cs::cartesian> tempPoint1;
                    boost::geometry::transform(this->point, tempPoint1);

                    boost::geometry::model::point<double, 3, boost::geometry::cs::cartesian> tempPoint2;
                    boost::geometry::transform(other.get_point(), tempPoint2);

                    /*creating object of the specified return type and returning it */
                    return ReturnType(boost::geometry::cross_product
                        <boost::geometry::model::point<double, 3, boost::geometry::cs::cartesian>>
                        (tempPoint1, tempPoint2));
                }
                
                // dot prodct of current vector with specified vector
                template <typename Representation>
                virtual double dot(Representation const& other) const
                {
                    /*both the coordinates/vector are first converted into cartesian coordinate system then
                    dot product of both cartesian product is converted into requested type and returned*/

                    /*checking types of argument type*/
                    BOOST_STATIC_ASSERT_MSG((boost::is_template_base_of
                        <boost::astronomy::coordinate::base_representation, Representation>::value),
                        "function argument type is expected to be a representation class");

                    /*converting both coordinates/vector into cartesian system*/
                    boost::geometry::model::point<double, 3, boost::geometry::cs::cartesian> tempPoint1;
                    boost::geometry::transform(this->point, tempPoint1);

                    boost::geometry::model::point<double, 3, boost::geometry::cs::cartesian> tempPoint2;
                    boost::geometry::transform(other.get_point(), tempPoint2);

                    return boost::geometry::dot_product(tempPoint1, tempPoint2);

                }

                // returns the unit vector of current vector
                template <typename ReturnType>
                virtual ReturnType unit_vector() const
                {
                    BOOST_STATIC_ASSERT_MSG((boost::is_template_base_of(boost::astronomy::coordinate::base_representation, ReturnType)),
                        "Expected return type to be an astronomy representaion");
                    
                    boost::geometry::model::point<double, 3, boost::geometry::cs::cartesian> tempPoint;
                    double magnitude = this->norm();
                    boost::geometry::transform(this->point, tempPoint);

                    boost::geometry::set<0>(tempPoint, (boost::geometry::get<0>() / magnitude));
                    boost::geometry::set<1>(tempPoint, (boost::geometry::get<1>() / magnitude));
                    boost::geometry::set<2>(tempPoint, (boost::geometry::get<2>() / magnitude));

                    return ReturnType(tempPoint);
                }

                // converts current representation into specified representation
                template <typename ReturnType>
                virtual ReturnType to_representation() const = 0;

                // sum of current vector and specified vector
                template <typename ReturnType>
                virtual ReturnType sum(representation const& other) const = 0;

                // mean of current vector with specified vector
                template <typename ReturnType>
                virtual ReturnType mean(representation const& other) const = 0;

                // norm of the current class is returned
                virtual double norm() const
                {
                    double result = 0.0;
                    boost::geometry::model::point<double, 3, boost::geometry::cs::cartesian> tempPoint;
                    boost::geometry::transform(this->point, tempPoint);

                    for (int i = 0; i < DimensionCount; i++)
                    {
                        result += std::pow(boost::geometry::get<i>(this->point), 2);
                    }

                    return std::sqrt(result);
                }

                boost::geometry::model::point<double, DimensionCount, Type> get_point() const
                {
                    return this->point;
                }
            }; //base_representation
        } //namespace coordinate
    } //namespace astronomy
} //namespace boost
#endif // !BOOST_ASTRONOMY_COORDINATE_BASE_REPRESENTATION_HPP

