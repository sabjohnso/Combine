#ifndef FUNCALL_HPP_INCLUDED
#define FUNCALL_HPP_INCLUDED

//
// ... Combine header files
//
#include <combine/import.hpp>



namespace Combine
{
  
  struct Funcall
  {
    template< typename F, typename ... Xs >
    constexpr auto
    operator()( F&& f, Xs&& ... xs ) const
    {
      return f( forward< Xs >( xs ) ... );
    }

    template< typename F, typename ... Xs >
    constexpr auto
    operator ()( const F& f, const Xs& ... xs ) const
    {
      return f( xs ... );
    }
    
  }; // end of struct Funcall


  constexpr auto funcall = Funcall{};
  
} // end of namespace Combine


#endif // FUNCALL_HPP_INCLUDED
