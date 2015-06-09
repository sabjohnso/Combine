/**
   @file
   make.hpp

   @brief
   Generic constructors

   @author: 
   Samuel Johnson <sabjohnso@yahoo.com>
   
   @ref
   
*/

#ifndef MAKE_HPP_INCLUDED_232832640776382888
#define MAKE_HPP_INCLUDED_232832640776382888

//
// ... Combine header files
//
#include <combine/import.hpp>
#include <combine/count.hpp>
#include <combine/traits.hpp>



namespace Combine
{


  template< template< typename ... > class T >
  struct MakeXs
  {
    template< 
      typename ... Xs,
      typename R = T< typename decay< Xs >::type ... >
      >
    constexpr R
    operator ()( Xs&& ... xs )
    {
      return R{ std::forward< Xs >( xs ) ... };
    }
  };


  template< template< typename, size_t > class T >
  struct MakeXn
  {
    template< 
      typename X,
      typename ... Xs,
      typename R = T< typename decay< X >::type, count_types< X, Xs ... >() >
      >
    constexpr R
    operator ()( X&& x, Xs&& ... xs )
    {
      static_assert(
	is_homogeneous< X, Xs ... >::value,
	"The arguments to the MakeXn constructor must all have the same type." );
      
      return R{ std::forward< X >( x ), std::forward< Xs >( xs ) ... };
    }
  };


  

} // end of namespace Combine


#endif // MAKE_HPP_INCLUDED
