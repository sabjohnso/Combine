#ifndef LIST_HPP_INCLUDED_1568740812345049774
#define LIST_HPP_INCLUDED_1568740812345049774 1


// Standard header files

#include <cstddef>


// Combine header files

#include <combine/nil.hpp>
#include <combine/cons.hpp>

namespace Combine
{


  template< typename ... >
  struct List;

  template<>
  struct List<>
  {
    using type = Nil;
  };

  template< typename X >
  struct List< X >
  {
    using type = Cons< X, Nil >;
  };

  template< typename X0, typename X1, typename ... Xs >
  struct List< X0, X1, Xs ... >
  {
    using type = Cons< X0, typename List< X1, Xs ... >::type >;
  };

  
  template< typename >
  struct Listp
  {
    constexpr static bool value = false;
  };

  template<>
  struct Listp< Nil >
  {
    constexpr static bool value = true;
  };

  template< typename X, typename Y >
  struct Listp< Cons< X, Y > >
  {
    constexpr static bool value = Listp< Y >::value;
  };

  template< typename >
  struct Length;

  template< typename X >
  struct Length
  {
    COMBINE_STATIC_ASSERT_TRUE( Listp< X >::value );
    constexpr static size_t value = 1+Length< typename Cdr< X >::type >::value;
  };

  template<>
  struct Length< Nil >
  {
    constexpr static size_t value = 0;
  };


  template< typename X >
  struct Reverse
  {

    COMBINE_STATIC_ASSERT_TRUE( Listp< X >::value );
    
    template< typename Y, typename Accum >
    struct Aux
    {
      COMBINE_STATIC_ASSERT_TRUE( Listp< Y >::value );
      COMBINE_STATIC_ASSERT_TRUE( Listp< Accum >::value );

      using type = typename Aux< typename Cdr< Y >::type, Cons< typename Car< Y >::type, Accum > >::type;
      
    };

    template< typename Accum >
    struct Aux< Nil, Accum >
    {
      COMBINE_STATIC_ASSERT_TRUE( Listp< Accum >::value );
      using type = Accum;
    };

    using type = typename Aux< X, Nil >::type;

  }; // end of struct reverse


  template< typename X, typename Y >
  struct Append
  {
    COMBINE_STATIC_ASSERT_TRUE( Listp< X >::value );
    COMBINE_STATIC_ASSERT_TRUE( Listp< Y >::value );

    template< typename Z, typename Accum >
    struct Aux
    {
      COMBINE_STATIC_ASSERT_TRUE( Listp< Z >::value );
      COMBINE_STATIC_ASSERT_TRUE( Listp< Accum >::value );
      using type = typename Aux< typename Cdr< Z >::type, Cons< typename Car< Z >::type, Accum > >::type;
    };

    template< typename Accum >
    struct Aux< Nil, Accum >
    {
      COMBINE_STATIC_ASSERT_TRUE( Listp< Accum >::value );
      using type = Accum;
    };
    
  }; // end of struct Append


  template< size_t n, typename X >
  struct Nth_list
  {
    COMBINE_STATIC_ASSERT_TRUE( Listp< X >::value );
    COMBINE_STATIC_ASSERT_TRUE( Length< X >::value > n );

    template< size_t m, typename Y >
    struct Aux
    {
      COMBINE_STATIC_ASSERT_TRUE( Listp< Y >::value );
      using type = typename Aux< m-1, typename Cdr< Y >::type >::type;
    };

    template< typename Y >
    struct Aux< 0, Y >
    {
      COMBINE_STATIC_ASSERT_TRUE( Listp< Y >::value );
      using type = typename Car< Y >::type;
    };
      
    using type = typename Aux< n, X >::type;
    
  };





  

} // end of namespace Combine

#endif // ! defined LIST_HPP_INCLUDED_1568740812345049774
