#ifndef COUNT_HPP_INCLUDED_861747834602917032
#define COUNT_HPP_INCLUDED_861747834602917032 1

// Standard header files

#include <cstddef>

namespace Combine
{

  /** A structure template that is used to count types.
      Recursive specialization of this is used to count the
      number of types is the template parameter list until the
      terminating specialization is reached: Count<>
   */
  template< typename ... >
  struct Count_types;


  /** A terminating specialization of the data structure template
      for counting types.
  */
  template<>
  struct Count_types<>
  {
    constexpr static size_t value = 0;
  };

  /** Iterate speialization of teh data structure template for
      counting types.
  */
  template< typename X, typename ... Xs >
  struct Count_types< X, Xs ... >
  {
    constexpr static size_t value = 1+Count_types< Xs ... >::value;
  };


  template< typename ... Xs >
  constexpr size_t
  count_types()
  {
    return Count_types< Xs ... >::value;
  }

  template< typename X, X ... >
  struct Count_values;

  template< typename X >
  struct Count_values< X >
  {
    constexpr static size_t value = 0;
  };

  template< typename X, X x, X ... xs >
  struct Count_values< X, x, xs ... >
  {
    constexpr static size_t value = 1+Count_values<X, xs ... >::value;
  };

  
} // end of namespace Combine


#endif // ! defined COUNT_HPP_INCLUDED_861747834602917032
