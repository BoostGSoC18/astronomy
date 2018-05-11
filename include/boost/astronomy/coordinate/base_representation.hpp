#ifndef BOOST_BASE_REPRESENTATION_HPP
#define BOOST_BASE_REPRESENTATION_HPP


#include <boost/geometry/geometries/point.hpp>

namespace boost
{
    namespace astronomy
    {
        namespace coordinate
        {

            template <int DimensionCount, typename Type>
            struct base_representation
            {
            protected:
                protected boost::geometry::model::point<double, DimensionCount, Type> point;
            public:
                
                // cross prodct of current vector with specified vector
                template<int OtherDimensionCount, typename OtherType, int ReturnDimensionCount = DimensionCount, typename ReturnType = Type>
                virtual base_representation<ReturnDimensionCount, ReturnType>
                    cross(const base_representation<OtherDimensionCount, OtherType> other) const = 0;

                // dot prodct of current vector with specified vector
                template<int OtherDimensionCount, typename OtherType>
                virtual double dot(const base_representation<OtherDimensionCount, OtherType> other) const = 0;

                // returns the unit vector of current vector
                template<int OtherDimensionCount = DimensionCount, typename OtherType = Type>
                virtual base_representation<OtherDimensionCount, OtherType> unit_vector() const = 0;

                // converts current representation into specified representation
                template<int OtherDimensionCount, typename OtherType>
                virtual base_representation<OtherDimensionCount, OtherType> to_representation() const = 0;

                // sum of current vector and specified vector
                template<int OtherDimensionCount, typename OtherType, int ReturnDimensionCount = DimensionCount, typename ReturnType = Type>
                virtual base_representation<ReturnDimensionCount, ReturnType>
                    sum(const base_representation<OtherDimensionCount, OtherType> other) const = 0;

                // mean of current vector with specified vector
                template<int OtherDimensionCount, typename OtherType>
                virtual base_representation<ReturnDimensionCount, ReturnType>
                    mean(const base_representation<OtherDimensionCount, OtherType> other) const = 0;

                virtual double norm() = 0;
            };
        }
    }
}
#endif // !BOOST_BASE_REPRESENTATION_HPP

