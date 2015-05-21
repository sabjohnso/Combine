#ifndef NTH_HPP_INCLUDED_1410731651909393077
#define NTH_HPP_INCLUDED_1410731651909393077 1


namespace Combine
{

  /** A structure template to determine the nth type is the 
      template parameter list.
   */
  template<
    size_t n,
    typename X,
    typename ... Xs
    >
  struct Nth
  {
    COMBINE_STATIC_ASSERT_TRUE( count_types< X, Xs ... >() > n );
    using type = typename Nth< n-1, Xs ... >::type;
  };


  /** The terminating specialization of the structure template for
      determining the nth type in a template parameter list.
  */
  template<
    template< typename ... > class Context,
    typename X,
    typename Xs
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
    template< typename ... > Context
    typename ... Xs >
  struct Nth_in< Context< Xs ... >
  {
    using type = typename Nth< n, Xs ... >::type;
  }

} // end of namespace Combine



#endif // ! defined NTH_HPP_INCLUDED_1410731651909393077
