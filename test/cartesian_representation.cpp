#include<iostream>

#include<boost/astronomy/coordinate/cartesian_representation.hpp>
#include<boost/astronomy/coordinate/spherical_equatorial_representation.hpp>
#include<boost/geometry/io/dsv/write.hpp>


int main()
{
    typedef boost::astronomy::coordinate::cartesian_representation cartesian;
    boost::geometry::model::point<double, 2, boost::geometry::cs::spherical_equatorial<boost::geometry::degree>> p(30, 60);
    boost::astronomy::coordinate::spherical_equatorial_representation<boost::geometry::degree> spherical(30, 60);

    //testing all the constructor
    cartesian c1;  //default constructor
    cartesian c2(1, 2, 3);   //constructing by providing value
    cartesian c3(c2);  //copy constructor
    cartesian c4(p);   //constructing from the point
    cartesian c5(spherical);   //constructing from the spherical representation

    c1 = c3;

    //checking initializations
    std::cout << "c1: " << boost::geometry::dsv(c1.get_point()) << std::endl;
    std::cout << "c2: " << boost::geometry::dsv(c2.get_point()) << std::endl;
    std::cout << "c3: " << boost::geometry::dsv(c3.get_point()) << std::endl;
    std::cout << "c4: " << boost::geometry::dsv(c4.get_point()) << std::endl;
    std::cout << "c5: " << boost::geometry::dsv(c5.get_point()) << std::endl;

    std::cout << "c1 X c2 = " << boost::geometry::dsv(c1.cross<cartesian>(spherical).get_point()) << std::endl;
    std::cout << "c1 * c2 = " << c1.dot(spherical) << std::endl;
    //std::cout << "unit vector of c3" << boost::geometry::dsv(c1.unit_vector<cartesian>().get_point()) << std::endl;
    //std::cout << c2.magnitude();
    std::cin.get();

    return 0;
}