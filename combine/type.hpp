/** 
    @file combine/type.hpp
  
    @author Samuel B. Johnson 

*/
#ifndef TYPE_HPP_INCLUDED_657393024844779545
#define TYPE_HPP_INCLUDED_657393024844779545 1


// Standard header files

#include <typeinfo>


// Combine header files

#include <combine/count.hpp>
#include <combine/nth.hpp>

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
  struct Types
  {

    constexpr static size_t size = count_types< Xs ... >();
     
    template< size_t index >
    using type = typename Nth< index, Xs ... >::type;
  };



  struct Write_Types
  {
    
    template< typename Stream, typename X, typename ... Xs >
    Stream&
    operator ()( Stream& s, Types< X, Xs ... > )
    {
      return s << '<' << Type< X >{}, aux( s, Types< X, Xs ... >{});
    }

  private:

    template< typename Stream >
    Stream& 
    aux( Stream& s, Types<> )
    {
      return s << '>';
    }

    template< typename Stream, typename X, typename ... Xs >
    Stream&
    aux( Stream& s, Types< X, Xs ... > )
    {
      return s << ',' << Type< X >{} << aux( s,  Types< Xs ... >{} );
    }
  };

  template< typename Stream, typename ... Xs >
  Stream&
  write_types( Stream& s, Types< Xs ... > )
  {
    return s << Write_Types()( s, Types< Xs ... >{} );
  }


  template< typename Stream, typename X, typename ... Xs >
  Stream&
  operator <<( Stream& s, Types< X, Xs ... > )
  {
    return s;
  }


  
  
} // end of namespace Combine

#endif // ! defined TYPE_HPP_INCLUDED_657393024844779545
