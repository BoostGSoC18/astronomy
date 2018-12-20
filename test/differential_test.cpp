#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <boost/astronomy/coordinate/differential.hpp>
#include <boost/astronomy/coordinate/representation.hpp>

using namespace std;
using namespace boost::astronomy::coordinate;

BOOST_AUTO_TEST_SUITE(differential_constructors)

BOOST_AUTO_TEST_CASE(cartesian)
{
    //checking construction from value
    cartesian_differential motion1(1.5, 9.0, 3.5);
    BOOST_CHECK_CLOSE(motion1.get_dx(), 1.5, 0.001);
    BOOST_CHECK_CLOSE(motion1.get_dy(), 9.0, 0.001);
    BOOST_CHECK_CLOSE(motion1.get_dz(), 3.5, 0.001);

    //copy constructor
    cartesian_differential motion2(motion1);
    BOOST_CHECK_CLOSE(motion1.get_dx(), motion2.get_dx(), 0.001);
    BOOST_CHECK_CLOSE(motion1.get_dy(), motion2.get_dy(), 0.001);
    BOOST_CHECK_CLOSE(motion1.get_dz(), motion2.get_dz(), 0.001);

    //constructing from boost::geometry::model::point
    boost::geometry::model::point<double, 2, boost::geometry::cs::spherical<boost::geometry::degree>> model_point(30, 60);
    cartesian_differential motion3(model_point);
    BOOST_CHECK_CLOSE(motion3.get_dx(), 0.75, 0.001);
    BOOST_CHECK_CLOSE(motion3.get_dy(), 0.4330127019, 0.001);
    BOOST_CHECK_CLOSE(motion3.get_dz(), 0.5, 0.001);

    //constructing from another differential
    spherical_differential<radian> spherical_motion(0.523599, 1.047198, 1);
    cartesian_differential motion4(spherical_motion);
    BOOST_CHECK_CLOSE(motion4.get_dx(), 0.75, 0.001);
    BOOST_CHECK_CLOSE(motion4.get_dy(), 0.4330127019, 0.001);
    BOOST_CHECK_CLOSE(motion4.get_dz(), 0.5, 0.001);
}

BOOST_AUTO_TEST_CASE(spherical)
{
    //checking construction from value
    spherical_differential<degree> motion1(45.0, 18, 3.5);
    BOOST_CHECK_CLOSE(motion1.get_dlat(), 45.0, 0.001);
    BOOST_CHECK_CLOSE(motion1.get_dlon(), 18.0, 0.001);
    BOOST_CHECK_CLOSE(motion1.get_ddist(), 3.5, 0.001);

    //copy constructor
    spherical_differential<degree> motion2(motion1);
    BOOST_CHECK_CLOSE(motion1.get_dlat(), motion2.get_dlat(), 0.001);
    BOOST_CHECK_CLOSE(motion1.get_dlon(), motion2.get_dlon(), 0.001);
    BOOST_CHECK_CLOSE(motion1.get_ddist(), motion2.get_ddist(), 0.001);

    //constructing from boost::geometry::model::point
    boost::geometry::model::point<double, 3, boost::geometry::cs::cartesian> model_point(50, 20, 30);
    spherical_differential<radian> motion3(model_point);
    BOOST_CHECK_CLOSE(motion3.get_dlat(), 0.38050637711237, 0.001);
    BOOST_CHECK_CLOSE(motion3.get_dlon(), 1.0625290806236, 0.001);
    BOOST_CHECK_CLOSE(motion3.get_ddist(), 61.64414002969, 0.001);

    //constructing from another representation
    cartesian_differential cartesian_motion(60, 45, 85);
    spherical_differential<degree> motion4(cartesian_motion);
    BOOST_CHECK_CLOSE(motion4.get_dlat(), 36.869897645844, 0.001);
    BOOST_CHECK_CLOSE(motion4.get_dlon(), 41.423665625003, 0.001);
    BOOST_CHECK_CLOSE(motion4.get_ddist(), 113.35784048755, 0.001);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(differential_functions)

BOOST_AUTO_TEST_CASE(magnitude)
{
    cartesian_differential point1(25, 36, 90);

    double result = point1.magnitude();

    BOOST_CHECK_CLOSE(result, 100.1049449328054, 0.001);

}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(differential_operators)

BOOST_AUTO_TEST_CASE(addition)
{
    cartesian_representation point1(10, 20, 30);
    cartesian_differential motion1(1, 5), motion2(6,0,0);
    
    //point1 with motion1 and motion2 after one instance of time
    cartesian_representation _1_instance = point1 + motion1 + motion2;

    BOOST_CHECK_CLOSE(_1_instance.get_x(), 17.0, 0.001);
    BOOST_CHECK_CLOSE(_1_instance.get_y(), 25, 0.001);
    BOOST_CHECK_CLOSE(_1_instance.get_z(), 30.0, 0.001);
}

BOOST_AUTO_TEST_CASE(multiplication)
{
    cartesian_representation point1(10, 20, 30);
    cartesian_differential motion1(1, 5);

    //point1 with motion1 after 5 instance of time 
    cartesian_representation _1_instance = point1 + (motion1 * 5);

    BOOST_CHECK_CLOSE(_1_instance.get_x(), 15.0, 0.001);
    BOOST_CHECK_CLOSE(_1_instance.get_y(), 45.0, 0.001);
    BOOST_CHECK_CLOSE(_1_instance.get_z(), 30.0, 0.001);
}

BOOST_AUTO_TEST_SUITE_END()