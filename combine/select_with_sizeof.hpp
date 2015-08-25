#ifndef SELECT_WITH_SIZEOF_HPP_INCLUDED_2034297708189183313
#define SELECT_WITH_SIZEOF_HPP_INCLUDED_2034297708189183313 1

// Standard header files

#include <cstddef>
#include <type_traits>


// Combine header files

#include <combine/type.hpp>


namespace Combine
{

  template< size_t n, typename >
  struct Select_with_sizeof;


  template< size_t n >
  struct Select_with_sizeof< n, Types<> >
  {
    using type = void;
  };

  template< size_t n, typename X, typename ... Xs >
  struct Select_with_sizeof< n, Types< X, Xs ... > >
  {
    using type = typename std::conditional< sizeof( X ) == n, X, typename Select_with_sizeof< n, Types< Xs ... > >::type >::type;
  };


  
} // end of namespace Combine



#endif // ! defined SELECT_WITH_SIZEOF_HPP_INCLUDED_2034297708189183313
