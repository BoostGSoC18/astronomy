# Motion of a point

Astronomy library provides a way to integrate motions with the coordinate. For every representation class, there is one corresponding differential class for it which will denote the motion of the point. 

At this time as units are not integrated with coordinate system so it is assumed that representation and differentials are in same corresponding unit.(E.g: if representation is in k.m then differential will be taken with respect to time so in this case units will be k.m/time here time can be any unit of time).

Creation of differential is exactly as representation classes.

There are 4 available differential classes:
* cartesian_differential
* spherical_differential
* spherical_equatorial_differential
* spherical_coslat_differential

>**NOTE:** spherical_coslat_differential is the differential longitude with cos(lat) included, latitude and distance. This differential is used in all the astronomical coordinate system.

This classes also provide multiplication and addition operator overload.
* If you want to add motion stored in differential to a representation class for one instance of time then addition operator can be used
* If you want to add motion stored in differential to a representation class for n instance of time then first multiply the differential by n and then add it to the representation.

required heade files to inclue all the differential classes:

```c++
#include <boost/astronomy/coordinate/coordinate.hpp>
```
or
```c++
#include <boost/astronomy/coordinate/differential.hpp>
```

Example:
```c++
#include <iostream>
#include <boost/astronomy/coordinate/cartesian_representation.hpp>
#include <boost/astronomy/coordinate/cartesian_differential.hpp>

using namespace std;
using namespace boost::astronomy::coordinate;

int main()
{
    cartesian_representation point(1.0, 35.0, 45.0);
    cartesian_differential motion1(1, 2, 0);
    cartesian_differential motion2(6, -3, 1);

    //for a point having only one motion
    //moving forward for one instance of time
    cartesian_representation x = point1 + motion1; // x = (1.0, 37.0, 45.0)

    //we can also add multiple motion to a point
    x = point + motion1 + motion2; //x = (8.0, 34.0, 46.0)

    //moving forward for 5 instance of time with single motion
    x = point + motion1 * 5; // x = (6.0, 45.0 45.0);

    //moving forward for 5 instance of time with multiple motion
    x = point + (motion1 + motion2) * 5; // x = (36.0, 30.0, 50.0)

    return 0;
}
```

[Privious](vector_operation.md) | [Next](astronomical_coordinate.md)