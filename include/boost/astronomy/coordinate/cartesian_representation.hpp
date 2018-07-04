#ifndef BOOST_ASTRONOMY_COORDINATE_CARTESIAN_REPRESENTATION_HPP
#define BOOST_ASTRONOMY_COORDINATE_CARTESIAN_REPRESENTATION_HPP


#include <tuple>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/algorithms/transform.hpp>
#include <boost/geometry/algorithms/equals.hpp>
#include <boost/static_assert.hpp>

#include <boost/astronomy/detail/is_base_template_of.hpp>
#include <boost/astronomy/coordinate/base_representation.hpp>
#include <boost/astronomy/coordinate/cartesian_differential.hpp>


namespace boost
{
    namespace astronomy
    {
        namespace coordinate
        {
            //Represents the coordinate in cartesian representation
            //Uses three components to represent a point/vector (x, y, z)
            struct cartesian_representation : public boost::astronomy::coordinate::base_representation
                <3, boost::geometry::cs::cartesian>
            {
            public:
                //default constructoer no initialization
                cartesian_representation(){}

                //constructs object from provided value of coordinates
                cartesian_representation(double x, double y=0.0, double z=0.0)
                {
                    boost::geometry::set<0>(this->point, x);
                    boost::geometry::set<1>(this->point, y);
                    boost::geometry::set<2>(this->point, z);
                }

                //constructs object from boost::geometry::model::point object
                template <int DimensionCount, typename Type>
                cartesian_representation(boost::geometry::model::point<double, DimensionCount, Type> const& pointObject)
                {
                    boost::geometry::transform(pointObject, this->point);

                }

                //copy constructor
                cartesian_representation(cartesian_representation const& object)
                {
                    this->point = object.get_point();
                }

                //constructs object from any type of representation
                template <typename Representation>
                cartesian_representation(Representation const& other)
                {
                    BOOST_STATIC_ASSERT_MSG((boost::astronomy::detail::is_base_template_of
                        <boost::astronomy::coordinate::base_representation, Representation>::value),
                        "No constructor found with given argument type");

                    boost::geometry::transform(other.get_point(), this->point);
                }

                // returns the (x, y, z) in the form of tuple
                std::tuple<double, double, double> get_xyz() const
                {
                    return std::make_tuple(boost::geometry::get<0>(this->point),
                        boost::geometry::get<0>(this->point), boost::geometry::get<0>(this->point));
                }

                //returns the x component of point
                double get_x() const
                {
                    return boost::geometry::get<0>(this->point);
                }

                //returns the y component of point
                double get_y() const
                {
                    return boost::geometry::get<1>(this->point);
                }

                //returns the z component of point
                double get_z() const
                {
                    return boost::geometry::get<2>(this->point);
                }

                //set value of (x, y, z) in current object
                void set_xyz(double x, double y, double z)
                {
                    boost::geometry::set<0>(this->point, x);
                    boost::geometry::set<1>(this->point, y);
                    boost::geometry::set<2>(this->point, z);
                }

                //set value of x component of point
                void set_x(double x)
                {
                    boost::geometry::set<0>(this->point, x);
                }

                //set value of y component of point
                void set_y(double y)
                {
                    boost::geometry::set<1>(this->point, y);
                }

                //set value of z component of point
                void set_z(double z)
                {
                    boost::geometry::set<2>(this->point, z);
                }

                boost::astronomy::coordinate::cartesian_representation 
                    operator +(boost::astronomy::coordinate::cartesian_differential const& diff) const 
                {
                    boost::astronomy::coordinate::cartesian_representation temp(this->point);

                    temp.set_x(temp.get_x() + diff.get_dx());
                    temp.set_y(temp.get_y() + diff.get_dy());
                    temp.set_z(temp.get_z() + diff.get_dx());

                    return temp;
                }

            }; //cartesian_representation
        } //namespace coordinate
    } //namespace astronomy
} //namespace boost

#endif // !BOOST_ASTRONOMY_COORDINATE_CARTESIAN_REPRESENTATION_HPP
