#ifndef BOOOST_ASTRONOMY_COORDINATE_ALT_AZ_HPP
#define BOOOST_ASTRONOMY_COORDINATE_ALT_AZ_HPP

#include <boost/astronomy/coordinate/base_coordinate.hpp>
#include <boost/astronomy/coordinate/representation.hpp>
#include <boost/astronomy/coordinate/differential.hpp>

namespace boost
{
    namespace astronomy
    {
        namespace coordinate
        {
            template <typename Representation=boost::astronomy::coordinate::spherical_representation<boost::geometry::degree>, 
                typename Differential=boost::astronomy::coordinate::spherical_coslat_differential<boost::geometry::degree>>
            struct alt_az : public base_coordinate<Representation, Differential>
            {
                
            };
        } //namespace coordinate
    } //namespace astronomy
} //namespace boost
#endif // !BOOOST_ASTRONOMY_COORDINATE_ALT_AZ_HPP

