/**
   @file
   fold.hpp

   @brief
   UNDOCUMENTED

   @author: 
   Samuel Johnson <sabjohnso@yahoo.com>

*/
#ifndef FOLD_HPP_INCLUDED_2114771976841162984
#define FOLD_HPP_INCLUDED_2114771976841162984

//
// ... Combine header files
//
#include <combine/partial.hpp>


namespace Combine
{ 

  template< typename F >
  struct Binary
  {

    template< typename A >
    constexpr auto
    operator()( A&& a )
    {
      return partialL( F(), std::forward< A >( a ));
    }

    template< typename A >
    constexpr auto
    right( A&& a )
    {
      return partialR( F(), std::forward< A >( a ));
    }
    
  };


  
  template< typename F >
  struct FoldL : Binary< F>
  {
    using Binary< F >::operator();

    template< typename A, typename B, typename C >
    constexpr auto
    operator()( A&& a, B&& b, C&& c )
    {
      return F{}( F{}( std::forward< A >( a ), std::forward< B >( b )), std::forward< C >( c ));
    }

    template< typename A, typename B, typename C, typename D, typename ... Es >
    constexpr auto
    operator()( A&&a, B&& b, C&& c, D&& d, Es&& ... es )
    {
      return ( *this( *this( std::forward< A >( a ),
			     std::forward< B >( b ) ),
		      std::forward< C >( c ),
		      std::forward< D >( d ),
		      std::forward< Es >( es ) ...));
    }

  
  }; // end of struct FoldL



  
} // end of namespace Combine


#endif // ! defined FOLD_HPP_INCLUDED__2114771976841162984

