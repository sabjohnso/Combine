#ifndef SELECT_WITH_SIZEOF_HPP_INCLUDED_2034297708189183313
#define SELECT_WITH_SIZEOF_HPP_INCLUDED_2034297708189183313 1

#include <cstddef>
#include <type_traits>


namespace Combine
{

  template< size_t n, typename >
  struct Select_with_sizeof;

  template< size_t n, typename X, typename ... Xs >
  struct Select_with_sizeof< n, Types< X, Xs ... > >
  {
    using type = typename std::conditional< sizeof( X ) == n, Type< X >, Select_with_sizeof< n, Types< Xs ... > > >::type::type;
  };
  
} // end of namespace Combine



#endif // ! defined SELECT_WITH_SIZEOF_HPP_INCLUDED_2034297708189183313
