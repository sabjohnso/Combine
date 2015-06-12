/**

   @file
   get.hpp

   @brief
   UNDOCUMENTED

   @author: 
   Samuel Johnson <sabjohnso@yahoo.com>
*/


#ifndef GET_HPP_INCLUDED_1497131594954610387
#define GET_HPP_INCLUDED_1497131594954610387

//
// ... Combine header files
//
#include <combine/import.hpp>



namespace Combine
{


  
  template< size_t index >
  struct Get
  {

    
    template< typename X >
    constexpr auto
    operator()( X&& x ) const
    {
      return get<index>( forward<X>( x ));
    }

    
    template< typename X >
    constexpr auto
    operator()( const X& x) const
    {
      return get<index>( x );
    }

    
  };


  template< size_t index >
  constexpr auto
  getget()
  {
    return Get<index>{};
  }
  
} // end of namespace Combine


#endif // GET_HPP_INCLUDED_1497131594954610387
