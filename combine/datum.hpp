#ifndef DATUM_HPP_INCLUDED_752112223423518829
#define DATUM_HPP_INCLUDED_752112223423518829 1


//
// ... Combine header files
//
#include <combine/type.hpp>

namespace Combine
{

  template< typename X, X x >
  struct Datum
  {
    constexpr static X value = x;
  };

  using True = Datum< bool, true >;
  using False = Datum< bool, false >;

  using Zero = Datum< int, 0 >;
  using One = Datum< int, 1 >;



  template< typename Stream, typename X, X x >
  Stream&
  operator <<( Stream& s, Type< Datum< X, x > >)
  {
    return s << "Datum< " << Type< X >{} << ", " << x << " >";
  }




  
} // end of namespace Combine



#endif // ! defined DATUM_HPP_INCLUDED_752112223423518829
