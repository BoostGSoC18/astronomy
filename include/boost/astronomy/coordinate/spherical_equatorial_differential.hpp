#ifndef BOOST_ASTRONOMY_COORDINATE_SPHERICAL_EQUATORIAL_DIFFERENTIAL_HPP
#define BOOST_ASTRONOMY_COORDINATE_SPHERICAL_EQUATORIAL_DIFFERENTIAL_HPP


#include <tuple>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/algorithms/transform.hpp>
#include <boost/geometry/algorithms/equals.hpp>
#include <boost/static_assert.hpp>

#include <boost/astronomy/detail/is_base_template_of.hpp>
#include <boost/astronomy/coordinate/cartesian_differential.hpp>
#include <boost/astronomy/coordinate/base_differential.hpp>



namespace boost
{
    namespace astronomy
    {
        namespace coordinate
        {
            //!Represents the differential in spherical representation on unit sphere
            //!Uses two components to represent a differential (dlatitude, dlongitude)
            template <typename DegreeOrRadian>
            struct spherical_equatorial_differential : public boost::astronomy::coordinate::base_differential
                <2, boost::geometry::cs::spherical_equatorial<DegreeOrRadian>>
            {
            public:
                //default constructor no initialization
                spherical_equatorial_differential() {}

                //!constructs object from provided value of differential (dlatitude, dlongitude)
                spherical_equatorial_differential(double dlat, double dlon)
                {
                    boost::geometry::set<0>(this->diff, dlat);
                    boost::geometry::set<1>(this->diff, dlon);
                }

                //!constructs object from boost::geometry::model::point object
                template <int DimensionCount, typename Type>
                spherical_equatorial_differential(boost::geometry::model::point<double, DimensionCount, Type> const& pointObject)
                {
                    boost::astronomy::coordinate::cartesian_differential temp = pointObject;
                    boost::geometry::transform(temp.unit_vector
                        <boost::astronomy::coordinate::cartesian_differential>().get_differential(), this->diff);
                }

                //copy constructor
                spherical_equatorial_differential(spherical_equatorial_differential<DegreeOrRadian> const& object)
                {
                    this->diff = object.get_differential();
                }

                //!constructs object from any type of differential
                template <typename Differential>
                spherical_equatorial_differential(Differential const& other)
                {
                    BOOST_STATIC_ASSERT_MSG((boost::astronomy::detail::is_base_template_of
                        <boost::astronomy::coordinate::base_differential, Differential>::value),
                        "No constructor found with given argument type");

                    boost::astronomy::coordinate::cartesian_differential temp = other;
                    boost::geometry::transform(temp.unit_vector
                        <boost::astronomy::coordinate::cartesian_differential>().get_differential(), this->diff);

                }
                //! returns the (dlat, dlon) in the form of tuple
                std::tuple<double, double> get_dlat_dlon() const
                {
                    return std::make_tuple(boost::geometry::get<0>(this->diff), boost::geometry::get<1>(this->diff));
                }

                //!returns the dlat component of differential
                double get_dlat() const
                {
                    return boost::geometry::get<0>(this->diff);
                }

                //!returns the dlon component of differential
                double get_dlon() const
                {
                    return boost::geometry::get<1>(this->diff);
                }

                //!set value of (dlat, dlon) in current object
                void set_dlat_dlon(double dlat, double dlon)
                {
                    boost::geometry::set<0>(this->diff, dlat);
                    boost::geometry::set<1>(this->diff, dlon);
                }

                //!set value of dlat component of differential
                void set_dlat(double dlat)
                {
                    boost::geometry::set<0>(this->diff, dlat);
                }

                //!set value of dlon component of differential
                void set_dlon(double dlon)
                {
                    boost::geometry::set<1>(this->diff, dlon);
                }

                boost::astronomy::coordinate::spherical_equatorial_differential<DegreeOrRadian>
                    operator +(boost::astronomy::coordinate::spherical_equatorial_differential<DegreeOrRadian> const& diff) const
                {
                    boost::astronomy::coordinate::spherical_equatorial_differential<DegreeOrRadian> temp(this->diff);

                    temp.set_dlat(temp.get_dlat() + diff.get_dlat());
                    temp.set_dlon(temp.get_dlon() + diff.get_dlon());

                    return temp;
                }

                
                boost::astronomy::coordinate::spherical_equatorial_differential<DegreeOrRadian>
                    operator *(double multiplier) const
                {
                    boost::astronomy::coordinate::spherical_equatorial_differential<DegreeOrRadian> temp(this->diff);

                    temp.set_dlat(temp.get_dlat() * multiplier);
                    temp.set_dlon(temp.get_dlon() * multiplier);

                    return temp;
                }
            };
        }
    }
}
#endif // !BOOST_ASTRONOMY_COORDINATE_SPHERICAL_EQUATORIAL_DIFFERENTIAL_HPP


