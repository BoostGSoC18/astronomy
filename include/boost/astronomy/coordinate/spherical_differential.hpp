#ifndef BOOST_ASTRONOMY_COORDINATE_SPHERICAL_DIFFERENTIAL_HPP
#define BOOST_ASTRONOMY_COORDINATE_SPHERICAL_DIFFERENTIAL_HPP


#include <tuple>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/algorithms/transform.hpp>
#include <boost/geometry/algorithms/equals.hpp>
#include <boost/static_assert.hpp>

#include <boost/astronomy/detail/is_base_template_of.hpp>
#include <boost/astronomy/coordinate/base_differential.hpp>
#include <boost/astronomy/coordinate/cartesian_differential.hpp>


namespace boost
{
    namespace astronomy
    {
        namespace coordinate
        {
            //!Represents the differential in spherical representation
            //!Uses three components to represent a differential (dlatitude, dlongitude, ddistance)
            template <typename DegreeOrRadian>
            struct spherical_differential : public boost::astronomy::coordinate::base_differential
                <3, boost::geometry::cs::spherical<DegreeOrRadian>>
            {
            public:
                //default constructor no initialization
                spherical_differential() {}

                //!constructs object from provided value of differential (dlatitude, dlongitude, ddistance)
                spherical_differential(double dlat, double dlon, double ddistance)
                {
                    boost::geometry::set<0>(this->diff, dlat);
                    boost::geometry::set<1>(this->diff, dlon);
                    boost::geometry::set<2>(this->diff, ddistance);
                }

                //!constructs object from boost::geometry::model::point object
                template<std::size_t DimensionCount, typename Type>
                spherical_differential(boost::geometry::model::point<double, DimensionCount, Type> const& pointObject)
                {
                    boost::geometry::model::point<double, 3, boost::geometry::cs::cartesian> temp;
                    boost::geometry::transform(pointObject, temp);
                    boost::geometry::transform(temp, this->diff);
                }

                //copy constructor
                spherical_differential(spherical_differential<DegreeOrRadian> const& other)
                {
                    this->diff = other.get_differential();
                }

                //!constructs object from any type of differential
                template <typename Differential>
                spherical_differential(Differential const& other)
                {
                    BOOST_STATIC_ASSERT_MSG((boost::astronomy::detail::is_base_template_of
                        <boost::astronomy::coordinate::base_differential, Differential>::value),
                        "No constructor found with given argument type");

                    boost::geometry::model::point<double, 3, boost::geometry::cs::cartesian> temp;
                    boost::geometry::transform(other.get_differential(), temp);
                    boost::geometry::transform(temp, this->diff);
                }

                //! returns the (dlat, dlon, ddistance) in the form of tuple
                std::tuple<double, double, double> get_dlat_dlon_ddist() const
                {
                    return std::make_tuple(boost::geometry::get<0>(this->diff),
                        boost::geometry::get<1>(this->diff), boost::geometry::get<2>(this->diff));
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

                //!returns the ddistance component of differential
                double get_ddist() const
                {
                    return boost::geometry::get<2>(this->diff);
                }

                //!set value of (dlat, dlon, ddistance) in current object
                void set_dlat_dlon_ddist(double dlat, double dlon, double ddistance)
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

                //!set value of dlon component of differential
                void set_dlon(double dlon)
                {
                    boost::geometry::set<1>(this->diff, dlon);
                }

                //!set value of ddistance component of differential
                void set_ddist(double ddistance)
                {
                    boost::geometry::set<2>(this->diff, ddistance);
                }

                boost::astronomy::coordinate::spherical_differential<DegreeOrRadian>
                    operator +(boost::astronomy::coordinate::spherical_differential<DegreeOrRadian> const& diff) const
                {
                    boost::astronomy::coordinate::spherical_differential<DegreeOrRadian> temp(this->diff);

                    temp.set_dlat(temp.get_dlat() + diff.get_dlat());
                    temp.set_dlon(temp.get_dlon() + diff.get_dlon());
                    temp.set_ddist(temp.get_ddist() + diff.get_ddist());

                    return temp;
                }

                boost::astronomy::coordinate::spherical_differential<DegreeOrRadian>
                    operator *(double multiplier) const
                {
                    boost::astronomy::coordinate::spherical_differential<DegreeOrRadian> temp(this->diff);

                    temp.set_dlat(temp.get_dlat() * multiplier);
                    temp.set_dlon(temp.get_dlon() * multiplier);
                    temp.set_ddist(temp.get_ddist() * multiplier);

                    return temp;
                }
            };
        }//namespace coordinate
    } //namespace astronomy
} //namespace boost
#endif // !BOOST_ASTRONOMY_COORDINATE_SPHERICAL_DIFFERENTIAL_HPP


