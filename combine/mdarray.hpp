/**
   @file
   mdarray.hpp

   @brief
   Multi-dimensional arrays.

   @author: 
   Samuel Johnson <sabjohnso@yahoo.com>
*/


#ifndef MDARRAY_HPP_INCLUDED_2216789799080984289
#define MDARRAY_HPP_INCLUDED_2216789799080984289 1

//
// ... Combine header files
//
#include <combine/import.hpp>
#include <combine/pow.hpp>
#include <combine/idx.hpp>
#include <combine/operator.hpp>



namespace Combine
{

  template< typename X, template< typename, size_t n > class C, size_t ... sizes >
  class MDArray : public PowXn< X, C, sizes ... >::type 
  {
  public:


    using base_type = typename PowXn< X, C, sizes ... >::type;
    using base_type::base_type;

    template< typename ... Ys >
    constexpr
    MDArray( Ys&& ... ys )
      : base_type( forward<Ys>( ys ) ... )
    {}

    template< typename ... Ys >
    constexpr
    MDArray( const Ys& ... ys )
      : base_type( ys ... )
    {}

    template< typename Y >
    constexpr auto
    operator +( const MDArray<Y,C,sizes ... >& y ) const
    {
      using Z = typename decay< decltype(declval<X>()+declval<Y>()) >::type;
      return MDArray<Z,C,sizes ... >( add_aux0( Idx< sizes ... >{}, *this, y, Addition{}));
    }

    template< typename Y >
    constexpr auto
    operator -( const MDArray< Y, C,sizes ... >& y ) const
    {
      using Z = typename decay< decltype(declval<X>()+declval<Y>()) >::type;
      return MDArray<Z,C,sizes ... >( add_aux0( Idx< sizes ... >{}, *this, y, Subtraction{}));
    }

    
    template< typename Y >
    constexpr auto
    operator *( const MDArray< Y, C,sizes ... >& y ) const
    {
      using Z = typename decay< decltype(declval<X>()+declval<Y>()) >::type;
      return MDArray<Z,C,sizes ... >( add_aux0( Idx< sizes ... >{}, *this, y, Multiplication{}));
    }

    
    template< typename Y >
    constexpr auto
    operator /( const MDArray< Y, C,sizes ... >& y ) const
    {
      using Z = typename decay< decltype(declval<X>()+declval<Y>()) >::type;
      return MDArray<Z,C,sizes ... >( add_aux0( Idx< sizes ... >{}, *this, y, Division{}));
    }

    
    template< typename Y >
    constexpr auto
    operator %( const MDArray< Y, C,sizes ... >& y ) const
    {
      using Z = typename decay< decltype(declval<X>()+declval<Y>()) >::type;
      return MDArray<Z,C,sizes ... >( add_aux0( Idx< sizes ... >{}, *this, y, Modulo{}));
    }


    constexpr static
    size_t
    size()
    {
      return product_Idx( Idx< sizes ... >());
    }

    template< size_t index >
    constexpr static size_t
    size()
    {
      return nth_Idx< index >( Idx< sizes ... >{});
    }
    
    

  private:

    template< size_t size_dim0, size_t size_dim1, size_t ... sizes_dim, typename A, typename B, typename Op >
    constexpr static auto
    add_aux0( Idx< size_dim0, size_dim1, sizes_dim ... >, const A& a, const B& b, const Op& op )
    {
      return add_aux1( gen_Idx< size_dim0 >(), Idx< size_dim1, sizes_dim ... >{}, a, b, op );
    }

    

    template< size_t size_dim, typename A, typename B, typename Op >
    constexpr static auto
    add_aux0( Idx< size_dim >, const A& a, const B& b, const Op& op )
    {
      return add_aux2( gen_Idx< size_dim >(), a, b, op );
    }

    


    template< size_t ... indices, size_t ... sizes_dim, typename A, typename B, typename Op >
    constexpr static auto
    add_aux1( Idx< indices ... >, Idx< sizes_dim ... >, const A& a, const B& b, const Op& op )
    {
      return MakeXn<C>{}( add_aux0( Idx< sizes_dim ... >{}, a[ indices ], b[ indices ], op ) ... );
    }


    

    template< size_t ... indices, typename A, typename B, typename Op >
    constexpr static auto
    add_aux2( Idx< indices ... >, const A& a, const B& b, const Op& op )
    {
      return MakeXn<C>{}( op( a[ indices ], b[ indices ]) ... );
    }

    

  };

  


  struct Get_MDArray
  {
    template< size_t ... indices, typename X, template< typename, size_t n > class C, size_t ... sizes >
    constexpr auto&
    operator()( Idx< indices ... >, const MDArray<X, C, sizes ...>& x )
    {
      using base_type = typename MDArray<X, C, sizes ...>::base_type;
      return aux( Idx< indices ...  >{}, static_cast<const base_type& >( x ));
    }

  private:

    template< typename Array >
    constexpr auto&
    aux( Idx<>, const Array& x )
    {
      return x;
    }

    template< size_t index, size_t ... indices_reversed, typename Array >
    constexpr auto&
    aux( Idx< index, indices_reversed ... >, const Array& x )
    {
      return aux( Idx< indices_reversed ... >{}, get< index >( x ));
    }
    
  };

  template< size_t ... indices, typename X, template< typename, size_t n > class C, size_t ... sizes >
  constexpr auto&
  get( const MDArray<X,C,sizes ...>& x )
  {
    return Get_MDArray{}( Idx< indices ... >{}, x );
  }

  
  
} // end of namespace Combine


#endif // ! define MDARRAY_HPP_INCLUDED_2216789799080984289
