# Astronomical coordinate Operations

There are only a few operations available at this time on coordinate which are demonstrated below.

```c++
#include <iostream>
#include <boost/astronomy/coordinate/coordinate.hpp>

using namespace boost::astronomy::coordinate;

int main()
{
        //first we create a point we want to represent in the sky
    sherical_representation star(30.455, 85.56);

    //we define motion it has (if it has)
    sherical_coslat_differential motion(0.01,0.03);

    //creating  sky point object
    sky_point<icrs> object1(star, motion);
    sky_point<icrs> object(35.568, 89.5)

    sky_point<galactic> object2(star, motion)
    ///Note that here object1 and object2 are not the same points in the sky as they are represented in different frames

    //Different frames have different origins so even after having the same values they refer to the different point in the sky

    //to retrive frame from object
    icrs frame_object = object1.get_point();

    if(object1.is_equivalant_system(object2))
    {
        std::cout << "They are in same frame" << std::endl;
    }//will print nothing

    //to find seperation between two point
    //both objects must be in same frame
    std::cout << object1.separation(object) << std::endl;

    //to find positional angle between two point
    //https://en.wikipedia.org/wiki/Position_angle
    //both objects must be in same frame
    std::cout << object1.positional_angle(object) << std::endl;
    return 0;
}
```

[Privious](astronomical_coordinate.md) | [Next]()