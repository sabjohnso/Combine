#ifndef LIST_HPP_INCLUDED_1568740812345049774
#define LIST_HPP_INCLUDED_1568740812345049774 1


// Combine header files

#include <combine/nil.hpp>
#include <combine/cons.hpp>

namespace Combine
{


  template< typename ... >
  struct List;

  template<>
  struct List<>
  {
    using type = Nil;
  };

  template< typename X, typename ... Xs >
  struct List< X, Xs ... >
  {
    using type = Cons< X, List< Xs ... > >;
  };

  
  template< typename >
  struct Listp
  {
    constexpr static bool value = false;
  };

  template<>
  struct Listp< Nil >
  {
    constexpr static bool value = true;
  };

  template< typename X, typename Y >
  struct Listp
  {
    constexpr static bool value = Listp< Y >::value;
  };

} // end of namespace Combine

#endif // ! defined LIST_HPP_INCLUDED_1568740812345049774
