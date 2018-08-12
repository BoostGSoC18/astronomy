# Astronomy library

## **introduction**

Development of Astronomy library started as a part Google Summer of Code 2018 under mentor organization **Boost C++ Library** and mentor/guide **Vinícius dos Santos Oliveira**. 

This library provides basic functionalities which are required daily in the field of astronomy. Right now the scope of this library is limited to coordinate system and FITS file handling but will be expanded in future.

This library was developed using boost version *1.67.0*

## **Intended Audiance**

This library is designed for the programmers who are new to C++. It provides easy APIs which are easy to learn for the new C++ developer. While developing this we have kept scientist in mind because not all the scientists are programmers so instead of investing much time in learning library or C++ they can invest time in their real work.

The following tutorial will show how to use this library. This tutorial is created assuming the user has only a little experience with C++ and no experience with boost C++ libraries.

## Prerequisites
* Minimum C++11 is required
* Familiarity with boost.geometry (recommended but not necessary)
* Knowledge of coordinate system
* Knowledge of File handling with C++
* Knowledge of C++ templates

## Limitations
* In this version units are not supported with the coordinate system but will be added soon
* Limited functionality for FITS file

## **Index**
1. Coordinate System
    * [1.1 Euclidean Coordinate Systems](coordinate/euclidean_coordinate.md)
        * [1.1.1 Creating a coordinate point (Cartesian, Spherical, Equatorial)](coordinate/coordinate_point.md)
        * [1.1.2 Conversions of coordinate systems](coordinate/coordinate_conversion.md)
        * [1.1.3 Operations on vector](coordinate/vector_operation.md)
    * [1.2 Motion in Euclidean Space](coordinate/motion.md)
    * [1.3 Astronomical Coordinate System](coordinate/astronomical_coordinate.md)
        * [1.3.1 Creating celestial points](coordinate/astronomical_coordinate.md)
        * [1.3.2 Operations on Celestial points](coordinate/astronomical_coordinate_operation.md)
2. FITS File Handling
    * 2.1 Reading FITS
        * 2.1.1 Accessing headers
        * 2.1.1 Accessing data

[NEXT](coordinate/euclidean_coordinate.md)
