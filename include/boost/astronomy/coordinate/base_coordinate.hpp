#ifndef BOOOST_ASTRONOMY_COORDINATE_BASE_COORDINATE_SYSTEM_HPP
#define BOOOST_ASTRONOMY_COORDINATE_BASE_COORDINATE_SYSTEM_HPP

#include <tuple>

#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/algorithms/transform.hpp>
#include <boost/geometry/algorithms/equals.hpp>
#include <boost/static_assert.hpp>

#include <boost/astronomy/coordinate/representation.hpp>
#include <boost/astronomy/coordinate/differential.hpp>
#include <boost/is_base_template_of.hpp>


namespace boost 
{
    namespace astronomy
    {
        namespace coordinate
        {

            template <typename Representation, typename Differential>
            struct base_coordinate
            {
            protected:
                Representation data;
                Differential motion;
                bool has_data = false, has_differential = false;

            public:
                virtual proper_motion() = 0;
                virtual radial_velocity() = 0;

                Representation get_representation()
                {
                    return data;
                }

                Differential get_differential()
                {
                    return motion;
                }

                template <typename ReturnType>
                ReturnType represen_as()
                {
                    BOOST_STATIC_ASSERT_MSG((boost::is_base_template_of
                        <boost::astronomy::coordinate::base_representation, ReturnType>::value), 
                        "return type is expected to be a representation class");

                    return ReturnType(data);
                }

                template <typename OtherRepresentation, typename OtherDifferential>
                double separation(base_coordinate<OtherRepresentation, OtherDifferential> const& other);

                template <typename OtherRepresentation, typename OtherDifferential>
                double separation_3d(base_coordinate<OtherRepresentation, OtherDifferential> const& other);
                
            };
        } //namespace coordinate
    } //namespace astronomy
} //namespace boost
#endif  // !BOOOST_ASTRONOMY_COORDINATE_BASE_COORDINATE_SYSTEM_HPP
