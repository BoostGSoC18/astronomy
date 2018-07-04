#ifndef BOOST_ASTRONOMY_DETAIL_IS_BASE_TEMPLATE_OF_HPP
#define BOOST_ASTRONOMY_DETAIL_IS_BASE_TEMPLATE_OF_HPP

#include <boost/type_traits.hpp>

namespace boost
{
    namespace astronomy
    {
        namespace detail
        {
            // structure to provide support like std::is_base_of for template base classes
            template <template <int, typename...> class Base, typename Derived>
            struct base_template
            {
                using U = typename std::remove_cv<Derived>::type;

                template <int T, typename... Args>
                static std::true_type test(Base<T, Args...>*);

                static std::false_type test(void*);

                using type = decltype(test(std::declval<U*>()));
            };

            template <template <int, typename...> class Base, typename Derived>
            using is_base_template_of = typename base_template<Base, Derived>::type;

        } //namespace detail
    } //namespace astronomy
} //namespace boost

#endif // !BOOST_ASTRONOMY_DETAIL_IS_BASE_TEMPLATE_OF_HPP

