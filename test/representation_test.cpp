#define BOOST_TEST_DYN_LINK


#include <boost/test/unit_test.hpp>
#include <boost/astronomy/coordinate/representation.hpp>

using namespace std;
using namespace boost::astronomy::coordinate;

BOOST_AUTO_TEST_SUITE(representation_constructor)

BOOST_AUTO_TEST_CASE(cartesian)
{
    //checking construction from value
    cartesian_representation point1(1.5, 9.0, 3.5);
    BOOST_CHECK_CLOSE(point1.get_x(), 1.5, 0.001);
    BOOST_CHECK_CLOSE(point1.get_y(), 9.0, 0.001);
    BOOST_CHECK_CLOSE(point1.get_z(), 3.5, 0.001);

    //copy constructor
    cartesian_representation point2(point1);
    BOOST_CHECK_CLOSE(point1.get_x(), point2.get_x(), 0.001);
    BOOST_CHECK_CLOSE(point1.get_y(), point2.get_y(), 0.001);
    BOOST_CHECK_CLOSE(point1.get_z(), point2.get_z(), 0.001);

    //constructing from boost::geometry::model::point
    boost::geometry::model::point<double, 2, boost::geometry::cs::spherical<boost::geometry::degree>> model_point(30, 60);
    cartesian_representation point3(model_point);
    BOOST_CHECK_CLOSE(point3.get_x(), 0.75, 0.001);
    BOOST_CHECK_CLOSE(point3.get_y(), 0.4330127019, 0.001);
    BOOST_CHECK_CLOSE(point3.get_z(), 0.5, 0.001);

    //constructing from another representation
    spherical_representation<radian> spherical_point(0.523599, 1.047198, 1);
    cartesian_representation point4(spherical_point);
    BOOST_CHECK_CLOSE(point4.get_x(), 0.75, 0.001);
    BOOST_CHECK_CLOSE(point4.get_y(), 0.4330127019, 0.001);
    BOOST_CHECK_CLOSE(point4.get_z(), 0.5, 0.001);
}

BOOST_AUTO_TEST_CASE(spherical)
{
    //checking construction from value
    spherical_representation<degree> point1(45.0, 18, 3.5);
    BOOST_CHECK_CLOSE(point1.get_lat(), 45.0, 0.001);
    BOOST_CHECK_CLOSE(point1.get_lon(), 18.0, 0.001);
    BOOST_CHECK_CLOSE(point1.get_dist(), 3.5, 0.001);

    //copy constructor
    spherical_representation<degree> point2(point1);
    BOOST_CHECK_CLOSE(point1.get_lat(), point2.get_lat(), 0.001);
    BOOST_CHECK_CLOSE(point1.get_lon(), point2.get_lon(), 0.001);
    BOOST_CHECK_CLOSE(point1.get_dist(), point2.get_dist(), 0.001);

    //constructing from boost::geometry::model::point
    boost::geometry::model::point<double, 3, boost::geometry::cs::cartesian> model_point(50, 20, 30);
    spherical_representation<radian> point3(model_point);
    BOOST_CHECK_CLOSE(point3.get_lat(), 0.38050637711237, 0.001);
    BOOST_CHECK_CLOSE(point3.get_lon(), 1.0625290806236, 0.001);
    BOOST_CHECK_CLOSE(point3.get_dist(), 61.64414002969, 0.001);

    //constructing from another representation
    cartesian_representation cartesian_point(60, 45, 85);
    spherical_representation<degree> point4(cartesian_point);
    BOOST_CHECK_CLOSE(point4.get_lat(), 36.869897645844, 0.001);
    BOOST_CHECK_CLOSE(point4.get_lon(), 41.423665625003, 0.001);
    BOOST_CHECK_CLOSE(point4.get_dist(), 113.35784048755, 0.001);
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(representation_functions)

BOOST_AUTO_TEST_CASE(cross_product)
{
    cartesian_representation point1(15, 25, 30);
    spherical_representation<degree> point2(45, 45, 3);

    auto result = point1.cross<cartesian_representation>(point2);

    BOOST_CHECK_CLOSE(result.get_x(), 8.0330086, 0.001);
    BOOST_CHECK_CLOSE(result.get_y(), 13.18019484, 0.001);
    BOOST_CHECK_CLOSE(result.get_z(), -15, 0.001);
}

BOOST_AUTO_TEST_CASE(dot_product)
{
    spherical_representation<degree> point1(30, 60, 3), point2(60, 30);

    double result = point1.dot(point2);

    BOOST_CHECK_CLOSE(result, 2.4240381058501, 0.001);
}

BOOST_AUTO_TEST_CASE(unit_vector)
{
    cartesian_representation point1(25, 36, 90);

    auto result = point1.unit_vector<cartesian_representation>();

    BOOST_CHECK_CLOSE(result.get_x(), 0.2497379127153113, 0.001);
    BOOST_CHECK_CLOSE(result.get_y(), 0.3596225943100483, 0.001);
    BOOST_CHECK_CLOSE(result.get_z(), 0.8990564857751207, 0.001);

}

BOOST_AUTO_TEST_CASE(magnitude)
{
    cartesian_representation point1(25, 36, 90);

    double result = point1.magnitude();

    BOOST_CHECK_CLOSE(result, 100.1049449328054, 0.001);

}

BOOST_AUTO_TEST_CASE(sum)
{
    cartesian_representation point1(10, 20, 30), point2(50, 60, 30);

    auto result = point1.sum<spherical_representation<degree>>(point2);

    BOOST_CHECK_CLOSE(result.get_lat(), 53.130102354156, 0.001);
    BOOST_CHECK_CLOSE(result.get_lon(), 59.036243467927, 0.001);
    BOOST_CHECK_CLOSE(result.get_dist(), 116.61903789691, 0.001);
}

BOOST_AUTO_TEST_CASE(mean)
{
    cartesian_representation point1(10, 20, 30), point2(50, 60, 30);
    auto result = point1.mean<cartesian_representation>(point2);

    BOOST_CHECK_CLOSE(result.get_x(), 30.0, 0.001);
    BOOST_CHECK_CLOSE(result.get_y(), 40.0, 0.001);
    BOOST_CHECK_CLOSE(result.get_z(), 30.0, 0.001);
}

BOOST_AUTO_TEST_SUITE_END()
