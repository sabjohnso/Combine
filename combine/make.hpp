/**

   @file
   make.hpp

   @brief
   Generic constructors

   @author: 
   Samuel Johnson <sabjohnso@yahoo.com>
   
*/

#ifndef MAKE_HPP_INCLUDED_232832640776382888
#define MAKE_HPP_INCLUDED_232832640776382888

//
// ... Combine header files
//
#include <combine/import.hpp>
#include <combine/count.hpp>
#include <combine/context.hpp>
#include <combine/traits.hpp>




namespace Combine
{


  template< template< typename ... > class T >
  struct MakeXs
  {
    template< 
      typename ... Xs,
      typename R = T< typename decay< Xs >::type ... >
      >
    constexpr R
    operator ()( Xs&& ... xs ) const
    {
      return R{ std::forward< Xs >( xs ) ... };
    }
    
  };



  /** A generic constructor for contexts similar to std::array:
      a fixed size collection with values of the same type.
   */
  template< template< typename, size_t > class T >
  struct MakeXn
  {
    template< 
      typename X,
      typename ... Xs,
      typename R = T< typename decay< X >::type, count_types< X, Xs ... >() >
      >
    constexpr R
    operator ()( X&& x, Xs&& ... xs ) const
    {
      static_assert( is_homogeneous< X, Xs ... >::value, 
		     "The arguments to the MakeXn constructor must all have the same type." );	
      return R{{std::forward< X >( x ), std::forward< Xs >( xs ) ... }};
    }
  }; // end of struct MakeXn



  
  /** A generic constructor for contexts similar to std::vector:
      a collection of values with a homogeneous type.
  */
  template< template< typename ... > class T >
  struct MakeX
  {
    template<
      typename X,
      typename ... Xs,
      typename R = T< typename decay< X >::type >
      >
    constexpr R
    operator ()( X&& x, Xs&& ... xs ) const
    {
      return R{ std::forward< X >( x ), std::forward< Xs >( xs ) ... };
    }
  };
  

  
  /** A generic constructor for generic constructors.
   */
  struct MakeMake
  {

    template< template< typename ... > class T >
    constexpr auto
    xs() const noexcept
    {
      return MakeXs<T>();
    }

    template< template< typename, size_t > class T >
    constexpr auto
    xn() const noexcept
    {
      return MakeXn<T>();
    }

    template< template< typename > class T >
    constexpr auto
    x() const
    {
      return MakeX<T>();
    }

    template<
      template< template< typename ... > class > class C,
      template< typename ... > class T
      >
    constexpr auto
    operator()( C<T> ) const noexcept
    {
      return xs<T>();
    }


    template<
      template< template< typename, size_t > class > class C,
      template< typename, size_t > class T
      >
    constexpr auto
    operator()( C<T> ) const noexcept
    {
      return xn< T >();
    }
    
    template< 
      template< typename ... > class T,
      typename ... Xs
      >
    constexpr auto
    operator()( T< Xs ... > ) const noexcept
    {
      return xs< T >();
    }

    template<
      template< typename, size_t > class T,
      typename X,
      size_t n
      >
    constexpr auto
    operator()( T< X, n > ) const noexcept
    {
      return xn< T >();
    }

    
  }; // end of struct MakeMake

  constexpr auto make_make = MakeMake{};
  
  

} // end of namespace Combine


#endif // MAKE_HPP_INCLUDED
