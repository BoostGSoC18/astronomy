#ifndef BOOST_SKY_POINT_HPP
#define BOOST_SKY_POINT_HPP


#include<string>
#include<boost\units\base_units\angle\degree.hpp>
#include<boost\units\base_units\angle\radian.hpp>


namespace boost
{
    namespace astronomy
    {
        namespace coordinate
        {
            typedef boost::units::angle::degree_base_unit degree;

            /*sky_point is used to represent a point(coordinate) in the sky*/
            template <class System, typename Unit, typename Unit2 = void>
            struct sky_point
            {
            protected:
                degree latitude;
                degree longitude;
                std::string coordinate_system;

            public:
                // constructor  
                sky_point() {}
                sky_point(double latitude, double longitude);
                sky_point(std::string latitude, std::string longitude);
                sky_point(std::string name);

                // destructor 
                ~sky_point();

                std::string get_constillation();
                degree separation(sky_point<System, Unit, Unit2> object);
                bool is_equivalant_system(sky_point<System, Unit, Unit2> object);
                sky_point<System, Unit, Unit2> from_name(std::string name);
                degree positional_angle(sky_point<System, Unit, Unit2> object);
            };

        } // namespace coordinate
    } // namespace astronomy
} // namespace boost

#endif // !BOOST_SKY_POINT_HPP