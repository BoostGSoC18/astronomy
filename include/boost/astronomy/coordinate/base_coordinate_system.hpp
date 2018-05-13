#ifndef BOOOST_ASTRONOMY_COORDINATE_BASE_COORDINATE_SYSTEM_HPP
#define BOOOST_ASTRONOMY_COORDINATE_BASE_COORDINATE_SYSTEM_HPP

#include <string>

#include <boost/units/systems/si.hpp>
#include <boost/units/systems/angle/degrees.hpp>
#include <boost/units/io.hpp>


namespace boost 
{
    namespace astronomy
    {
        namespace coordinate
        {
            typedef boost::units::quantity<boost::units::degree::plane_angle> degree;
            typedef boost::units::quantity<boost::units::divide_typeof_helper
                <boost::units::degree::plane_angle,boost::units::si::time>::type>
                degree_per_sec;

            template <class Representation=void, class Differential=void>
            struct base_coordinate_system
            {
            protected:
                std::string system_name;
                std::string representation;
                std::string differential;

            public:

                template<class OtherRepresentation>
                degree separation(base_coordinate_system<OtherRepresenation> other);

                template<class System>
                virtual bool is_transformable_to() const = 0;

                degree_per_sec motion() const = 0;

                degree_per_sec radial_velocity() = 0;

            }; //base_coordinate_system
        } //namespace coordinate
    } //namespace astronomy
} //namespace boost
#endif  // !BOOOST_ASTRONOMY_COORDINATE_BASE_COORDINATE_SYSTEM_HPP
