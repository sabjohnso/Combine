/**
   @file
   traits.hpp

   @brief
   UNDOCUMENTED

   @author: 
   Samuel Johnson <sabjohnso@yahoo.com>

*/
#ifndef TRAITS_HPP_INCLUDED_1905796359601175806
#define TRAITS_HPP_INCLUDED_1905796359601175806

//
// ... Combine header files
//
#include <combine/import.hpp>


namespace Combine
{
  
  template< typename ... >
  struct is_homogeneous
  {
    constexpr static bool value = false;
  };

  template< typename X >
  struct is_homogeneous< X >
  {
    constexpr static bool value = true;
  };

  template< typename X, typename ... Xs >
  struct is_homogeneous< X, X, Xs ... > : is_homogeneous< X, Xs ... >
  {};

  
} // end of namespace Combine


#endif // TRAITS_HPP_INCLUDED_1905796359601175806
