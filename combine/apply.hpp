/**
   @file
   apply.hpp

   @brief
   Apply a function with arguments taken from a
   collection.

   @author: 
   Samuel Johnson <sabjohnso@yahoo.com>
*/
#ifndef APPLY_HPP_INCLUDED_995287732558119082
#define APPLY_HPP_INCLUDED_995287732558119082

//
// ... Combine header files
//
#include <combine/import.hpp>
#include <combine/idx.hpp>
#include <combine/length.hpp>


namespace Combine
{

  struct Apply
  {
    template< typename F, typename Xs >
    constexpr auto 
    operator ()( F&& f, Xs&& xs )
    {
      return aux( gen_Idx< length<Xs>() >(), forward<F>( f ) , forward<Xs>( xs ));
    }

    
    template< typename F, typename Xs >
    constexpr auto 
    operator ()( const F& f, const Xs& xs )
    {
      return aux( gen_Idx< length<Xs>() >(), f,  xs );
    }
    
  private:

    template< size_t ... indices, typename F, typename Xs >
    constexpr auto
    aux( Idx< indices ... > , F&& f, Xs&& xs )
    {
      return f( get< indices >( xs ) ... );
    }
  };

  constexpr static auto apply = Apply{};

  
  
} // end of namespace Combine


#endif // APPLY_HPP_INCLUDED_995287732558119082
