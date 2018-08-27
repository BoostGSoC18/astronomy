# Creation of a point in Euclidean space

Representation classes are structured as such that they can be used as a vector or point at the same time as per the requirement.

All representations are accomodated in namespace `boost::astronomy::coordinate` 

All the representation classes have similar accessor only change is in the name of their corresponding component. The corresponding component of each representation can be found from the table below.

| *Representation*                      | *Component 1* | *Component 2* | *Component 3*
|---------------------------------------|---------------|---------------|---
| `cartesian_representation`            | X             | Y             | Z
| `spherical_representation`            | lat           | lon           | dist
| `spherical_equatorial_representation` | lat           | lon           | -

To access any of the component in any representation methods as below can be used:<br>
`get_<component>()`<br>
`set_<component>()`<br>
`get_<component1>_<component2>_<component3>()`<br>
`set_<component1>_<component2>_<component3>()`<br>
Here `<component>` is supposed to be replaced by the corrosponding component of the representation.<br>
E.g:- for cartesian_representatino its `get_x()` which will change for spherical_representation to `get_lat()`

## Cartesian Point
This representation uses (x, y, z) components to represent any point in the 3D space. This is the most widely used for regular geometry in maths.

Required header:
```c++
#include <boost/astronomy/coordinate/cartesian_representation.hpp>
```
or
```c++
#include <boost/astronomy/coordinate/representation.hpp>
```
or
```c++
#include <boost/astronomy/coordinate/coordinate.hpp>
```
Example of how to create a cartesian point and access its component:
```c++
#include <iostream>
#include <boost/astronomy/coordinate/cartesian_representation.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/core/cs.hpp>
#include <tuple>

typedef boost::astronomy::coordinate::cartesian_representation cartesian;
typedef boost::geometry::model::point<double, 3, boost::geometry::cs::spherical<boost::geometry::degree>> geometry_point;

int main()
{
    //creating point without any value
    cartesian point1;

    //creating a point by directly providing values of x, y and z
    //default value of y and z is 0
    cartesian point2(10, 20, 30);

    //assigning value of individual component
    point1.set_x(50);
    point1.set_y(40);
    point1.set_z(880);

    //or to set all the values in single statement tuple could be used as follow
    point2.set_xyz(38.5, 50.0, 64.23);

    //creating a point from another point
    cartesian point3(point2); //or point3 = point2

    //creating a point from boost::geometry::model::point
    //any type of point can be used here 
    //here we will demonstrate with cartesian point
    //https://www.boost.org/doc/libs/1_67_0/libs/geometry/doc/html/geometry/reference/models/model_point.html
    //https://www.boost.org/doc/libs/1_60_0/libs/geometry/doc/html/geometry/reference/cs.html
    geometry_point gp(45.0, 60.0, 50.0);
    cartesian point4(gp);

    //accessing each component of representation
    std::cout << point4.get_x() << std::endl; //methods get_y and get_z are available

    //get boost::geometry::model::point of current object
    auto stored_point = point3.get_point();

    //get the tuple of the component in the coordinate
    std::tuple<double, double, double> components = point3.get_xyz();

    std::cin.get();
    return 0;
}
```

## Spherical Point
This representation uses (latitude, longitude, distance) components to represent any point in the 3D space. This is the most widely used in astronomy and positional geometry.

Required header:
```c++
#include <boost/astronomy/coordinate/spherical_representation.hpp>
```
or
```c++
#include <boost/astronomy/coordinate/representation.hpp>
```
or
```c++
#include <boost/astronomy/coordinate/coordinate.hpp>
```
Example of how to create a cartesian point and access its component:
```c++
#include <iostream>
#include <boost/astronomy/coordinate/spherical_representation.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/core/cs.hpp>
#include <tuple>

typedef boost::astronomy::coordinate::spherical_representation spherical;
typedef boost::geometry::model::point<double, 3, boost::geometry::cs::cartesian> geometry_point;

int main()
{
    //To create spherical point we need to specify is angles are in radian or degree
    //creating point without any value
    spherical<boost::astronomy::coordinate::degree> point1;

    //creating a point by directly providing values of x, y and z
    //default value of y and z is 0
    spherical<boost::astronomy::coordinate::radian> point2(10, 20, 30);

    //assigning value of individual component
    point1.set_x(50);
    point1.set_y(40);
    point1.set_z(880);

    //or to set all the values in single statement tuple could be used as follow
    point2.set_xyz(38.5, 50.0, 64.23);

    //creating a point from another point
    spherical<boost::astronomy::coordinate::radian> point3(point2); //or point3 = point2

    //creating a point from boost::geometry::model::point
    //any type of point can be used here 
    //here we will demonstrate with cartesian point
    //https://www.boost.org/doc/libs/1_67_0/libs/geometry/doc/html/geometry/reference/models/model_point.html
    //https://www.boost.org/doc/libs/1_60_0/libs/geometry/doc/html/geometry/reference/cs.html
    geometry_point gp(45.0, 60.0, 50.0);
    spherical<boost::astronomy::coordinate::radian> point4(gp);

    //accessing each component of representation
    std::cout << point4.get_lon() << std::endl; //methods get_lat and get_dist are available

    //get boost::geometry::model::point of current object
    auto stored_point = point3.get_point();

    //get the tuple of the component in the coordinate
    std::tuple<double, double, double> components = point3.get_lat_lon_dist();

    std::cin.get();
    return 0
}
```

## Spherical equatorial Point
This representation uses (latitude, longitude) components to represent any point in the 3D space using only two components. It is similar to the spherical representation except it takes only two component and points are on the unit sphere.

Required header:
```c++
#include <boost/astronomy/coordinate/spherical_equatorial_representation.hpp>
```
or
```c++
#include <boost/astronomy/coordinate/representation.hpp>
```
or
```c++
#include <boost/astronomy/coordinate/coordinate.hpp>
```

All the APIs are the same as `spherical_representation`.

[Privious](euclidean_coordinate.md) | [Next](coordinate_conversion.md)
