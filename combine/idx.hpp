/** @file 
    combine/idx.hpp
    
    @brief 
    A header file containing definitions of struct 
    templates for building a sequence of nonnegative integer 
    values.

    @author Samuel B. Johnson <sabjohnso@yahoo.com>
*/
#ifndef IDX_HPP_INCLUDED_1819216676186183542
#define IDX_HPP_INCLUDED_1819216676186183542 1

//
// ... Standard header files
//
#include <cstddef>

//
// ... Combine header files
//
#include <combine/count.hpp>


namespace Combine
{

  template< size_t ... >
  struct Idx
  {};
  

  template< size_t, size_t ... >
  struct Gen_Idx;
  

  template< size_t ... indices >
  struct Gen_Idx< 0, indices ... >
  {
    using type = Idx< indices ... >;
  };


  template< size_t n, size_t ... indices >
  struct Gen_Idx
    : public Gen_Idx< n-1, n-1, indices ... >
  {};


  template<
    size_t n,
    typename R = typename Gen_Idx< n >::type
    >
  constexpr R
  gen_Idx()
  {
    return R{};
  };


  template<
    typename ... Xs,
    typename R = typename Gen_Idx< count_types< Xs ... >() >::type
    >
  constexpr R
  gen_Idx()
  {
    return R{};
  }

} // end of namespace Combine

#endif // ! defined IDX_HPP_INCLUDED_1819216676186183542
