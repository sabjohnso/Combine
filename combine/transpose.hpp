/**
   @file
   transpose.hpp

   @brief
   UNDOCUMENTED

   @author: 
   Samuel Johnson <sabjohnso@yahoo.com>
*/
#ifndef TRANSPOSE_HPP_INCLUDED_569582321808901826
#define TRANSPOSE_HPP_INCLUDED_569582321808901826

//
// ... Combine header files
//
#include <combine/apply.hpp>
#include <combine/composite.hpp>
#include <combine/get.hpp>
#include <combine/import.hpp>
#include <combine/datum.hpp>
#include <combine/idx.hpp>
#include <combine/make.hpp>
#include <combine/length.hpp>
#include <combine/traits.hpp>



namespace Combine
{

  struct Transpose
  {
    template< 
      template< typename ... > class Co,
      template< typename ... > class Ci,
      typename ... Xs,
      typename ... Ys
      >
    constexpr auto 
    operator()( Co< Ci<Xs ... >, Ys ... >&& xs ) const
    {
      static_assert( 
	is_homogeneous< 
	Datum< size_t, length< Ci<Xs ...> >() >, 
	Datum< size_t, length< Ys >() > ... >::value,
	"The lengths of the inner contexts are not uniform." );
      
      return aux0( gen_Idx< Xs ... >(), MakeXs<Ci>{}, MakeXs<Co>{}, forward< Co< Ci< Xs ... >, Ys ... > >( xs ));
    }


    template< 
      template< typename ... > class Co,
      template< typename ... > class Ci,
      typename ... Xs,
      typename ... Ys
      >
    constexpr auto 
    operator()( const Co< Ci<Xs ... >, Ys ... >& xs ) const
    {
      static_assert( 
	is_homogeneous< 
	Datum< size_t, length< Ci<Xs ...> >() >, 
	Datum< size_t, length< Ys >() > ... >::value,
	"The lengths of the inner contexts are not uniform." );
      
      return aux0( gen_Idx< Xs ... >(), MakeXs<Ci>{}, MakeXs<Co>{}, xs );
    }
    
    template< 
      template< typename, size_t > class Co,
      template< typename, size_t > class Ci,
      typename X,
      size_t m, 
      size_t n
      >
    constexpr auto
    operator ()( Co< Ci<X,n>, m >&& xs ) const
    {
      return aux0( gen_Idx< n >(), MakeXn<Ci>{}, MakeXn<Co>{}, forward< Co< Ci<X,n>, m > >( xs ));
    }


    template< 
      template< typename, size_t > class Co,
      template< typename, size_t > class Ci,
      typename X,
      size_t m, 
      size_t n
      >
    constexpr auto
    operator ()( const Co< Ci<X,n>, m >& xs ) const
    {
      return aux0( gen_Idx< n >(), MakeXn<Ci>{}, MakeXn<Co>{}, xs );
    }

  private:
    
    template< size_t ... indices, typename MakeI, typename MakeO, typename Xs >
    constexpr auto
    aux0( Idx< indices ... >, MakeI&& makei, MakeO&& makeo, Xs&& xs ) const
    {
      return makei( apply( MakeXs<StrangeComposite>{}( makeo, getget<indices>() ), forward<Xs>( xs )) ... );
    }

    
    template< size_t ... indices, typename MakeI, typename MakeO, typename Xs >
    constexpr auto
    aux0( Idx< indices ... >, MakeI&& makei, MakeO&& makeo, const Xs& xs ) const
    {
      return makei( apply( MakeXs<StrangeComposite>{}( makeo, getget<indices>() ), xs ) ... );
    }

    
  };



  
} // end of namespace Combine


#endif // TRANSPOSE_HPP_INCLUDED_569582321808901826
