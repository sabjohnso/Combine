/** @file combine/cons.hpp
    
    @brief Constructs

    @author Samuel B. Johnson
*/
#ifndef CONS_HPP_INCLUDED_1055377043033551256
#define CONS_HPP_INCLUDED_1055377043033551256 1

// Combine header files

#include <combine/macro_tools.hpp>
#include <combine/type.hpp>
#include <combine/nil.hpp>


namespace Combine
{

  
  template< typename X, typename Y >
  struct Cons
  {
    using car = X;
    using cdr = Y;
  }; // end of struct Cons


  template< typename Stream, typename X, typename Y >
  Stream&
  operator <<( Stream& s, Type< Cons< X, Y > > )
  {
    return s << "Cons< " << Type< X >{} << ", " << Type< Y >{} << " >";
  }

  
  template< typename >
  struct Consp
  {
    constexpr static bool value = false;
  };

  template< typename X, typename Y >
  struct Consp< Cons< X, Y > >
  {
    constexpr static bool value = true;
  };


  
  template< typename ... >
  struct Car
  {
    using type = Nil;
  };

  template< typename X, typename Y >
  struct Car< Cons< X, Y > >
  {
    using type = X;
  };

  

  

  template< typename ... >
  struct Cdr
  {
    using type = Nil;
  };
  
  template< typename X, typename Y >
  struct Cdr< Cons< X, Y > >
  {
    using type = Y;
  };


  

  template< typename X >
  struct Caar
  {
    COMBINE_STATIC_ASSERT_TRUE( Consp< X >::value );
    COMBINE_STATIC_ASSERT_TRUE( Consp< typename Car< X >::type >::value );

    using type = typename X::car::car;
  };

  template< typename X >
  struct Cadr
  {
    COMBINE_STATIC_ASSERT_TRUE( Consp< X >::value );
    COMBINE_STATIC_ASSERT_TRUE( Consp< typename Car< X >::type >::value );
    using type = typename X::car::cdr;
  };






  
 

 
} // end of namespace Combine



#endif // ! defined CONS_HPP_INCLUDED_1055377043033551256
