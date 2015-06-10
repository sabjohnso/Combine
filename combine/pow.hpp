/**
   @file
   pow.hpp

   @brief
   UNDOCUMENTED

   @author: 
   Samuel Johnson <sabjohnso@yahoo.com>

*/
#ifndef POW_HPP_INCLUDED_144216074111286780
#define POW_HPP_INCLUDED_144216074111286780

//
// ... Combine header files
//
#include <combine/import.hpp>


namespace Combine
{


  
  //
  // ... With context --> template< typename > class
  //

  /** A structure to determine the type for repeatedly
      wrapping a data type in a context.
  */
  template<
    /** The underlying data type that will be 
	placed in the lowest context.
     */
    typename,

    /** The context that will repeatedly
	wrapped around the data type.
     */
    template< typename > class,

    /** The number of timesthe context will
	wrapp the data type.
     */
    size_t 
    >
  struct PowX;


  /** A terminal specialization 
      returning the underlying
      data type
   */
  template< 
    typename X,
    template< typename > class C
    >
  struct PowX< X, C, 0 >
  {
    using type = X;
  };


  /** An Iterate specialization that
      recursively applies a context
      to an underlying data type.
  */
  template<
    typename X,
    template< typename > class C,
    size_t n
    >
  struct PowX
  {
    using type = C< typename PowX< X, C, n-1 >::type >;
  };




  //
  // ... With context --> template< typename, size_t > class
  //

  /** A struct to determine the type resulting from repeated
      wrapping of a underlying data type in a context with a 
      size parameter, where the size parameter varies for
      with with each application.
  */
  template< 
    typename, template< typename, size_t > class, 
    size_t ... 
    >
  struct PowXn;

  /** A terminal specialization that returns the underlying data
      type.
  */
  template< 
    typename X,
    template< typename, size_t > class C
    >
  struct PowXn< X, C >
  {
    using type = X;
  };

  /** An iterate specialization that returns the context applied
      repeatedly through recursion.
  */
  template< 
    typename X,
    template< typename, size_t > class C,
    size_t n,
    size_t ... ns
    >
  struct PowXn< X, C, n, ns ... >
  {
    using type = C< typename PowXn< X, C, ns ... >::type, n >;
  };
  



    
  
} // end of namespace Combine


#endif // ! defined POW_HPP_INCLUDED_144216074111286780
