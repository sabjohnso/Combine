/**
   @file
   fold.hpp

   @brief
   UNDOCUMENTED

   @author: 
   Samuel Johnson <sabjohnso@yahoo.com>

*/
#ifndef FOLD_HPP_INCLUDED_2114771976841162984
#define FOLD_HPP_INCLUDED_2114771976841162984

//
// ... Combine header files
//
#include <combine/import.hpp>
#include <combine/partial.hpp>
#include <combine/datum.hpp>





namespace Combine
{ 

  template< typename F >
  struct Binary
  {

    template< typename A >
    constexpr auto
    operator()( A&& a ) const
    {
      return partialL( F(), forward< A >( a ));
    }

    template< typename A >
    constexpr auto
    right( A&& a ) const
    {
      return partialR( F(), forward< A >( a ));
    }
    
  };


  
  template< typename F >
  struct FoldL : Binary< F>
  {
    using Binary< F >::operator();

    template< typename A, typename B, typename C >
    constexpr auto
    operator()( A&& a, B&& b, C&& c ) const
    {
      return F{}( F{}( forward< A >( a ), forward< B >( b )), forward< C >( c ));
    }

    template< typename A, typename B, typename C, typename D, typename ... Es >
    constexpr auto
    operator()( A&&a, B&& b, C&& c, D&& d, Es&& ... es ) const
    {
      return F{}( F{}( forward< A >( a ),
		       forward< B >( b )),
		  forward< C >( c ),
		  forward< D >( d ),
		  forward< Es >( es ) ... );
    }

  
  }; // end of struct FoldL



  template< typename F >
  struct FoldR : Binary< F >
  {
    using Binary< F >::operator();


    template< typename A, typename B, typename C >
    constexpr auto
    operator ()( A&& a, B&& b, C&& c ) const
    {
      return F{}( std::forward<A>( a ), F{}( std::forward<B>( b ), std::forward<C>( c )));
    }

    template< typename A, typename B, typename C, typename D, typename ... Es >
    constexpr auto
    operator ()( A&&a , B&& b, C&& c, D&& d, Es&& ... es ) const
    {
      return F{}( forward<A>( a ),
		  forward<B>( b ),
		  F{}( forward<C>( c ), 
		       forward<D>( d ), 
		       forward<Es>( es ) ... ));
    }

  };

  
  /** Fold using a divide an conquere method
   */
  template< typename F >
  struct FoldDC : Binary< F >
  {
    using Binary< F >::operator();

    template< typename A, typename B, typename C >
    constexpr auto
    operator ()( A&& a, B&& b, C&& c ) const
    {
      return F{}( F{}( forward<A>( a ), 
		       forward<B>( b )),
		  forward<C>( c ));
    }

    template< typename A, typename B, typename C, typename D, typename ... Es >
    constexpr auto
    operator()( A&& a, B&& b, C&& c, D&& d, Es&& ... es ) const
    {
      return aux( Datum< bool, count_types< A, B, C, D, Es ... >() % 2 == 0 >{},
		  forward<A>( a ), forward<B>( b ), forward<C>( c ), forward<D>( d ),
		  forward<Es>( es ) ... );
    }

  private:

    template< typename ... Xs >
    constexpr auto
    aux( True, Xs&& ... xs ) const
    {
      return aux_even( 
	gen_Idx< count_types< Xs ... >()/2 >(),
	make_tuple( forward< Xs >( xs ) ... ));
    }

    template< typename X, typename ... Xs >
    constexpr auto
    aux( False, X&& x, Xs&& ... xs ) const
    {
      return F{}( forward<X>( x ), 
		  aux_even( gen_Idx< count_types< Xs ... >()/2 >(), 
			    make_tuple( forward< Xs >( xs ) ... )));
    }

    template< size_t ... indices, template< typename ... > class C, typename ... Xs >
    constexpr auto
    aux_even( Idx< indices ... >, C<Xs...>&& xs ) const
    {
      return F{}( F{}( get< indices >( xs ) ... ),
		  F{}( get< indices+count_types<Xs ... >()/2 >( xs ) ... ));
			  
    }

	  
  }; // end of struct FoldDC
    
			     



  
} // end of namespace Combine


#endif // ! defined FOLD_HPP_INCLUDED__2114771976841162984

