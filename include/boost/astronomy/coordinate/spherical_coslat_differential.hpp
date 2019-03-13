#ifndef BOOST_ASTRONOMY_COORDINATE_SPHERICAL_COSLAT_DIFFERENTIAL_HPP
#define BOOST_ASTRONOMY_COORDINATE_SPHERICAL_COSLAT_DIFFERENTIAL_HPP


#include <tuple>
#include <math.h>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/algorithms/transform.hpp>
#include <boost/geometry/algorithms/equals.hpp>
#include <boost/static_assert.hpp>

#include <boost/astronomy/detail/is_base_template_of.hpp>
#include <boost/astronomy/coordinate/base_differential.hpp>
#include <boost/astronomy/coordinate/cartesian_differential.hpp>
#include <boost/astronomy/coordinate/spherical_differential.hpp>


namespace boost
{
    namespace astronomy
    {
        namespace coordinate
        {
            //!Represents the differential in spherical representation including cos(latitude) term
            //!Uses three components to represent a differential (dlatitude, dlongitude_coslat, ddistance)
            template <typename DegreeOrRadian>
            struct spherical_coslat_differential : public boost::astronomy::coordinate::base_differential
                <3, boost::geometry::cs::spherical<DegreeOrRadian>>
            {
            public:
                //default constructor no initialization
                spherical_coslat_differential() {}

                //!constructs object from provided value of differential (dlatitude, dlongitude_coslat, ddistance)
                spherical_coslat_differential(double dlat, double dlon_coslat, double ddistance)
                {
                    boost::geometry::set<0>(this->diff, dlat);
                    boost::geometry::set<1>(this->diff, dlon_coslat);
                    boost::geometry::set<2>(this->diff, ddistance);
                }

                //!constructs object from boost::geometry::model::point object
                template<std::size_t DimensionCount, typename System>
                spherical_coslat_differential(boost::geometry::model::point<double, DimensionCount, System> const& pointObject)
                {
                    boost::geometry::model::point<double, 3, boost::geometry::cs::cartesian> temp;
                    boost::geometry::transform(pointObject, temp);
                    boost::geometry::transform(temp, this->diff);
                }

                //copy constructor
                spherical_coslat_differential(spherical_coslat_differential<DegreeOrRadian> const& other)
                {
                    this->diff = other.get_differential();
                }

                //!constructs object from any type of representation
                template <typename Differential>
                spherical_coslat_differential(Differential const& other)
                {
                    BOOST_STATIC_ASSERT_MSG((boost::astronomy::detail::is_base_template_of
                        <boost::astronomy::coordinate::base_differential, Differential>::value),
                        "No constructor found with given argument type");

                    boost::astronomy::coordinate::spherical_differential<DegreeOrRadian> temp(other);
                    temp.set_dlon(temp.get_dlon() * cos(temp.get_dlat()));
                    this->diff = temp.get_differential();
                }

                //! returns the (dlat, dlon, ddistance) in the form of tuple
                std::tuple<double, double, double> get_dlat_dlon_coslat_ddist() const
                {
                    return std::make_tuple(boost::geometry::get<0>(this->diff),
                        boost::geometry::get<1>(this->diff), boost::geometry::get<2>(this->diff));
                }

                //!returns the dlat component of differential
                double get_dlat() const
                {
                    return boost::geometry::get<0>(this->diff);
                }

                //!returns the lon_coslat component of differential
                double get_dlon_coslat() const
                {
                    return boost::geometry::get<1>(this->diff);
                }

                //!returns the ddistance component of differential
                double get_ddist() const
                {
                    return boost::geometry::get<2>(this->diff);
                }

                //!set value of (dlat, dlon_coslat, ddistance) in current object
                void set_dlat_dlon_coslat_ddist(double dlat, double dlon, double ddistance)
                {
                    boost::geometry::set<0>(this->diff, dlat);
                    boost::geometry::set<1>(this->diff, dlon);
                    boost::geometry::set<2>(this->diff, ddistance);
                }

                //!set value of dlat component of differential
                void set_dlat(double dlat)
                {
                    boost::geometry::set<0>(this->diff, dlat);
                }

                //!set value of dlon_coslat component of differential
                void set_dlon_coslat(double dlon)
                {
                    boost::geometry::set<1>(this->diff, dlon);
                }

                //!set value of ddistance component of differential
                void set_ddist(double ddistance)
                {
                    boost::geometry::set<2>(this->diff, ddistance);
                }

                boost::astronomy::coordinate::spherical_coslat_differential<DegreeOrRadian>
                    operator +(boost::astronomy::coordinate::spherical_coslat_differential<DegreeOrRadian> const& diff) const
                {
                    boost::astronomy::coordinate::spherical_coslat_differential<DegreeOrRadian> temp(this->diff);

                    temp.set_dlat(temp.get_dlat() + diff.get_dlat());
                    temp.set_dlon_coslat(temp.get_dlon_coslat() + diff.get_dlon_coslat());
                    temp.set_ddist(temp.get_ddist() + diff.get_ddist());

                    return temp;
                }

                boost::astronomy::coordinate::spherical_coslat_differential<DegreeOrRadian>
                    operator *(double multiplier) const
                {
                    boost::astronomy::coordinate::spherical_coslat_differential<DegreeOrRadian> temp(this->diff);

                    temp.set_dlat(temp.get_dlat() * multiplier);
                    temp.set_dlon_coslat(temp.get_dlon_coslat() * multiplier);
                    temp.set_ddist(temp.get_ddist() * multiplier);

                    return temp;
                }
            };
        }//namespace coordinate
    } //namespace astronomy
} //namespace boost
#endif // !BOOST_ASTRONOMY_COORDINATE_SPHERICAL_COSLAT_DIFFERENTIAL_HPP


