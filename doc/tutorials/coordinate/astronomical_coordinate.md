# Astronomical Cooridnate Systems

The way we use the geographical coordinate system consisting of longitude and latitude to pinpoint any location on earth, there are many different systems available to pinpoint any location in the cosmos.

Any body in the cosmos would have some motion and its position would change accordingly. So to represent any body in cosmos this library has provided a single class called `sky_point` which supports multiple astronomical coordinate systems and its differentials.

Supported coordinate systems:
* Alt-Az
* ICRS
* CIRS
* Galactic
* SuperGalactic
* HelioCentric
* GeoCentric

>**NOTE:** All the astronomical coordinate systems are referred as frames in this library.

Example:

```c++
#include <boost/astronomy/coordinate/coordinate.hpp>

using namespace boost::astronomy::coordinate;

int main()
{
    //first we create a point we want to represent in the sky
    sherical_representation star(30.455, 85.56);

    //we define motion it has (if it has)
    sherical_coslat_differential motion(0.01,0.03);

    //we create a frame
    icrs frame(star, motion);

    //creating a sky point object
    sky_point<icrs> object(frame);
    
    return 0;
}
```

[Privious](motion.md) | [Next](astronomical_coordinate_operation.md)