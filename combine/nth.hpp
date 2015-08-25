/** @file combine/nth.hpp

    @brief A header file containing structure templates for
    accessing the nth type in a collection of types.
    
    @author Samuel B. Johnson <sabjohnso@yahoo.com>

 */
#ifndef NTH_HPP_INCLUDED_1410731651909393077
#define NTH_HPP_INCLUDED_1410731651909393077 1


// Standard header files

#include <cstddef>



// Combine header files

#include <combine/macro_tools.hpp>
#include <combine/count.hpp>


namespace Combine
{

  /** A structure template to determine the nth type is the 
      template parameter list.
   */
  template< size_t n, typename ... Xs >
  struct Nth;
  
  /** A structure template to determine the nth type is the 
      template parameter list.
   */
  template<
    size_t n,
    typename X,
    typename ... Xs
    >
  struct Nth< n, X, Xs ... >
  {
    COMBINE_STATIC_ASSERT_TRUE( count_types< X, Xs ... >() > n );
    using type = typename Nth< n-1, Xs ... >::type;
  };


  /** The terminating specialization of the structure template for
      determining the nth type in a template parameter list.
  */
  template<
    typename X,
    typename ... Xs
    >
  struct Nth< 0, X, Xs ... >
  {
    using type = X;
  };

  template< size_t n, typename  >
  struct Nth_in;



  /** A structure template for determining the nth type in the
      template parameter list of the input type.
  */
  template<
    size_t n,
    template< typename ... > class Context,
    typename ... Xs >
  struct Nth_in< n, Context< Xs ... > >
  {
    using type = typename Nth< n, Xs ... >::type;
  };

} // end of namespace Combine



#endif // ! defined NTH_HPP_INCLUDED_1410731651909393077
