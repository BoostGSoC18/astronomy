#ifndef BOOST_SKY_POINT_HPP
#define BOOST_SKY_POINT_HPP


#include <string>

#include <boost/units/systems/angle/degrees.hpp>
#include <boost/units/io.hpp>


namespace boost
{
    namespace astronomy
    {
        namespace coordinate
        {
            typedef boost::units::quantity<boost::units::degree::plane_angle> degree;

            /*sky_point is used to represent a point(coordinate) in the sky*/
            template <class System, typename Unit, typename Unit2=void>
            struct sky_point
            {
            protected:
                degree latitude;    //hosrizontal coordinate
                degree longitude;   //vertical coordinate
                std::string coordinate_system;  //type of coordinate system

            public:
                //constructors  

                //default constructor
                sky_point() {}

                //copy constructor
                template<class OtherSystem, typename OtherUnit, typename OtherUnit2 = void>
                sky_point(const sky_point<OtherSystem, OtherUnit, OtherUnit2> object);

                //constructing from numbers
                sky_point(double latitude, double longitude);

                //constructing from string
                sky_point(const char* latitude, const char* longitude);

                //constructing from name of object if available in the calatoge
                sky_point(const char* name);

                // destructor 
                ~sky_point();

                std::string get_constillation();

                template<class OtherSystem, typename OtherUnit, typename OtherUnit2 = void>
                degree separation(const sky_point<OtherSystem, OtherUnit, OtherUnit2> object);

                template<class OtherSystem, typename OtherUnit, typename OtherUnit2 = void>
                bool is_equivalant_system(const sky_point<OtherSystem, OtherUnit, OtherUnit2> object);

                sky_point<System, Unit, Unit2> from_name(const char* name);

                template<class OtherSystem, typename OtherUnit, typename OtherUnit2 = void>
                degree positional_angle(const sky_point<OtherSystem, OtherUnit, OtherUnit2> object);

                template<class OtherSystem, typename OtherUnit, typename OtherUnit2 = void>
                sky_point<OtherSystem, OtherUnit, OtherUnit2> transform_to();

            }; //sky_point

        } // namespace coordinate
    } // namespace astronomy
} // namespace boost

#endif // !BOOST_SKY_POINT_HPP