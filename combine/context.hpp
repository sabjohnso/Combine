/**
   @file
   context.hpp

   @brief
   UNDOCUMENTED

   @author: 
   Samuel Johnson <sabjohnso@yahoo.com>
*/


#ifndef CONTEXT_HPP_INCLUDED_2108403464684159461
#define CONTEXT_HPP_INCLUDED_2108403464684159461


//
// ... Combine header files
//
#include <combine/import.hpp>

namespace Combine
{

  
  template< template< typename ... > class T >
  struct ContextXs
  {};


  template< template< typename, size_t > class T  >
  struct ContextXn
  {};
  

  template< template< typename ... > class T >
  struct ContextX
  {};


  template< typename X, typename Y >
  struct is_same_context
  {
    template< typename A, typename B >
    struct Aux
    {
      constexpr static bool value = false;
    };

    template< template< typename ... > class C >
    struct Aux< ContextX<C>, ContextX<C> >
    {
      constexpr static bool value = true;
    };

    template< template< typename, size_t > class C >
    struct Aux< ContextXn<C>, ContextXn<C> >
    {
      constexpr static bool value = true;
    };

    template< template< typename ... > class C >
    struct Aux< ContextXs<C>, ContextXs<C> >
    {
      constexpr static bool value = true;
    };

    constexpr static bool value =  Aux< 
      typename decay< X >::type, 
      typename decay< Y >::type >::value;
  };

  

  

  
} // end of namespace Combine


#endif // CONTEXT_HPP_INCLUDED_2108403464684159461
