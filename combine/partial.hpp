/**
   @file
   partial.hpp

   @brief
   Partial function application

   @author: 
   Samuel Johnson <sabjohnso@yahoo.com>

   @ref
   http://yapb-soc.blogspot.com/2012/09/partial-application-in-c.html
*/

#ifndef PARTIAL_HPP_INCLUDED_1723360070574759208
#define PARTIAL_HPP_INCLUDED_1723360070574759208


//
// ... Combine header files
//
#include <combine/import.hpp>
#include <combine/idx.hpp>
#include <combine/make.hpp>


namespace Combine
{

  /** Partial function application, packing arguments on the left.
   */
  template< typename F, typename ... Xs >
  class PartialL
  {
  public:
    template< typename G, typename ... Ys >
    constexpr
    PartialL( G&& g, Ys&& ... ys )
      : f( std::forward< G >( g ))
      , xs( std::forward< Ys >( ys ) ... )
    {}

    template< typename ... Ys >
    constexpr auto
    operator ()( Ys&& ... ys ) const
    {
      return aux( gen_Idx< Xs ... >(), std::forward< Ys >( ys ) ... );
    }
      
  
  private:


    template< size_t ... indices,  typename ... Ys >
    constexpr auto
    aux( Idx< indices ... >, Ys&& ... ys )
    {
      return f(  std::get< indices >( xs ) ..., std::forward< Ys >( ys ) ... );
    }

    const F f;
    const std::tuple< Xs ... > xs;
  };




  /** Partial function application, packing arguments on the right.
   */
  template< typename F, typename ... Xs >
  class PartialR
  {
    template< typename G, typename ... Ys >
    constexpr
    PartialR( G&& g, Ys&& ... ys )
      : f( std::forward< G >( g ))
      , Xs( std::forward< Ys >( ys ) ... )
    {}

    template< typename ... Ys >
    constexpr auto
    operator ()( Ys&& ... ys )
    {
      return aux( gen_Idx< Xs ... >(), std::forward< Ys >( ys ) ... );
    }
  
  private:

    template< size_t ... indices, typename ... Ys >
    constexpr auto
    aux( Idx< indices ... >, Ys&& ... ys )
    {
      using std::get;
      return f( std::forward< Ys >( ys ) ..., get< indices >( xs ) ... );
    }
  
    const F f;
    const std::tuple< Xs ... > xs;
  };

  constexpr static auto partialR = MakeXs< PartialR >{};
  constexpr static auto partialL = MakeXs< PartialL >{};
  
} // end of namespace Combine



#endif // ! defined PARTIAL_HPP_INCLUDED_1723360070574759208
