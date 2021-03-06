#ifndef BOOST_ASTRONOMY_DETAIL_IS_BASE_TEMPLATE_OF_HPP
#define BOOST_ASTRONOMY_DETAIL_IS_BASE_TEMPLATE_OF_HPP

#include <cstddef>
#include <type_traits>


namespace boost
{
    namespace astronomy
    {
        namespace detail
        {
            ///@cond INTERNAL
            // structure to provide support like std::is_base_of for template base classes
            template <template <std::size_t, typename...> class Base, typename Derived>
            struct base_template
            {
                //using U = typename std::remove_cv<Derived>::type;

                template <std::size_t T, typename... Args>
                static std::true_type test(const Base<T, Args...>*);

                static std::false_type test(...);

                using type = decltype(test(std::declval<Derived*>()));
            };

            template <template <std::size_t, typename...> class Base, typename Derived>
            using is_base_template_of = typename base_template<Base, Derived>::type;
            ///@endcond
        } //namespace detail
    } //namespace astronomy
} //namespace boost

#endif // !BOOST_ASTRONOMY_DETAIL_IS_BASE_TEMPLATE_OF_HPP

