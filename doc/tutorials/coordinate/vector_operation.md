Representation classes have provided few of the most used vector operations which are as follows:
* Cross product of two vectors
* Dot product of two vectors
* Unit Vector
* Magnitude of vector
* Addition of two vectors
* Mean of two vectors

For the convenience of the users, these functions are developed in such a way that the operation results can directly be returned in any of the representation.

>**NOTE:** All these functions first convert vectors into cartesian_representation, performs the operation on it and then returns the result in requested representation

```c++
#include <iostream>
#include <boost/astronomy/coordinate/representation.hpp>

using namespace boost::astronomy::coordinate;

int main()
{
    //Cross Product 
    cartesian_representation point1(15, 25, 30);
    spherical_representation<degree> point2(45, 45, 3);

    cartesian_representation cross_result = point1.cross<cartesian_representation>(point2);

    //dot product
    std::cout << point1.dot(point2) << std::endl;

    //unit vector
    cartesian_representation unit_vector = point2.unit_vector<cartesian_representation>();

    //magnitude
    std::cout << point1.magnitude() << std::endl;

    //sum of two vectors
    //Here we show the flexibility provided by the library to use any representation for the operations and implicit casting
    //right hand of the equal returns object of cartesian_representation
    //But it gets converted implicitly into spherical_representation<radian>
    spherical_representation<radian> sum_result = point1.sum<cartesian_representation>(point2);

    //mean of two vectors
    spherical_representation<degree> mean_result = point1.mean<spherical_representation<degree>>(point2);

    return 0;
}
```

[Privious](coordinate_conversion.md) | [Next](motion.md)