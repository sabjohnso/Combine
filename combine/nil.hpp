#ifndef NIL_HPP_INCLUDED_921336238296976139
#define NIL_HPP_INCLUDED_921336238296976139 1

//
// ... Combine header files
//
#include <combine/type.hpp>
#include <combine/nil.hpp>

namespace Combine
{

  struct Nil{};

  template< typename >
  struct Null
  {
    constexpr static bool value = false;
  };

  template<>
  struct Null< Nil >
  {
    constexpr static bool value = true;
  };


  template< typename Stream >
  Stream&
  operator <<( Stream& s, Type< Nil > )
  {
    return s << "Nil";
  }
  
} // end of namespace Combine


#endif // ! defined NIL_HPP_INCLUDED_921336238296976139
