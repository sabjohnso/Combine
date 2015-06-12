/**
   @file
   length.hpp

   @brief
   UNDOCUMENTED

   @author: 
   Samuel Johnson <sabjohnso@yahoo.com>
*/


#ifndef LENGTH_HPP_INCLUDED_193428367569659862
#define LENGTH_HPP_INCLUDED_193428367569659862

//
// ... Combine header files
//
#include <combine/import.hpp>
#include <combine/count.hpp>

namespace Combine
{

  template< typename >
  struct Length;

  template< 
    template< typename, size_t > class C,
    typename X,
    size_t n
    >
  struct Length< C<X,n> >
  {
    constexpr static size_t value = n;
  };

  template< 
    template< typename ... > class C,
    typename ... Xs
    >
  struct Length< C<Xs ...> >
  {
    constexpr static size_t value = count_types< Xs ... >();
  };


  
  
  template< typename X >
  constexpr auto
  length()
  {
    return Length<typename decay< X >::type >::value;
  }

  
  

}

#endif // LENGTH_HPP_INCLUDED_193428367569659862
