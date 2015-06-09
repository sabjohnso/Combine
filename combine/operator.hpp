/**

   @file
   operator.hpp

   @brief
   UNDOCUMENTED

   @author: 
   Samuel Johnson <sabjohnso@yahoo.com>

*/
#ifndef OPERATOR_HPP_INCLUDED_2049968923608873682
#define OPERATOR_HPP_INCLUDED_2049968923608873682

//
// ... Combine header files
//
#include <combine/fold.hpp>


namespace Combine
{

  
  struct Add : FoldL< Add >
  {
  
    using FoldL< Add >::operator();

    template< typename A, typename B >
    constexpr auto
    operator ()( A&& a, B&& b )
    {
      return std::forward< A >( a )+std::forward< B >( b );
    }

  };



  struct Multiply : FoldL< Multiply >
  {
  
    using FoldL< Multiply >::operator();

    template< typename A, typename B >
    constexpr auto
    operator ()( A&& a, B&& b )
    {
      return std::forward< A >( a )*std::forward< B >( b );
    }

  };


  
  constexpr auto sum = Add{};
  constexpr auto product = Multiply{};
  

  
} // end of namespace Combine


#endif // OPERATOR_HPP_INCLUDED_2049968923608873682
