#include<iostream>

#include<boost/astronomy/coordinate/cartesian_representation.hpp>
#include<boost/astronomy/coordinate/spherical_equatorial_representation.hpp>
#include<boost/geometry/io/dsv/write.hpp>

int main()
{
    boost::geometry::model::point<double, 2, boost::geometry::cs::spherical_equatorial<boost::geometry::degree>> p(15, 10);
    boost::astronomy::coordinate::cartesian_representation c(1, 2, 3);

    //testing all the constructors
    boost::astronomy::coordinate::spherical_equatorial_representation<boost::geometry::degree> s1;
    boost::astronomy::coordinate::spherical_equatorial_representation<boost::geometry::radian> s2;
    boost::astronomy::coordinate::spherical_equatorial_representation<boost::geometry::degree> s3(30, 60);
    boost::astronomy::coordinate::spherical_equatorial_representation<boost::geometry::radian> s4(p);
    boost::astronomy::coordinate::spherical_equatorial_representation<boost::geometry::degree> s5(s3);
    boost::astronomy::coordinate::spherical_equatorial_representation<boost::geometry::degree> s6(c);

    s1 = s4;
    s2 = s1;

    //checking initializations
    std::cout << "s1: " << boost::geometry::dsv(s1.get_point()) << std::endl;
    std::cout << "s2: " << boost::geometry::dsv(s2.get_point()) << std::endl;
    std::cout << "s3: " << boost::geometry::dsv(s3.get_point()) << std::endl;
    std::cout << "s4: " << boost::geometry::dsv(s4.get_point()) << std::endl;
    std::cout << "s5: " << boost::geometry::dsv(s5.get_point()) << std::endl;
    std::cout << "s6: " << boost::geometry::dsv(s6.get_point()) << std::endl;

    std::cin.get();
    return 0;
}