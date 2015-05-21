/** 
    @file combine/type.hpp
  
    @author Samuel B. Johnson 

*/
#ifndef TYPE_HPP_INCLUDED_657393024844779545
#define TYPE_HPP_INCLUDED_657393024844779545 1


namespace Combine
{

  /** A structure template for holding a single type.
   */
  template< typename X >
  struct Type
  {
    using type = X;
  };

  
  template< typename Stream, typename X >
  Stream& 
  operator <<( Stream& s, Type< X >  )
  {
    return s << typeid( X ).name();
  }


  template< typename ... Xs >
  struct Types;


  
  
} // end of namespace Combine

#endif // ! defined TYPE_HPP_INCLUDED_657393024844779545
