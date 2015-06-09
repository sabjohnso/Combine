//
// ... Standard header files
//
#include <iostream>


//
// ... Combine header files
//
#include <combine/macro_tools.hpp>
#include <combine/meta_kanren.hpp>

using namespace Combine;
using namespace Combine::Meta_Kanren;


#define _( ... ) typename __VA_ARGS__::type


struct Test0
{
  
  template< typename ... >
  struct F;

  template< typename Q >
  struct F< Q >
  {
    using type = _(Equate< Q, Datum<size_t,5> >);
  };
  using type = _(Apply<_(Call_fresh< Procedure<F> >), Empty_state >);

  using type0 = _( Car< type > );
  using type1 = _( Cdr< type > );


};


template< typename ... >
struct F;

template< typename A >
struct F< A >
{
  using type = typename Equate<  A, Datum< size_t, 7 > >::type;
};

template< typename ... >
struct G;

template< typename B >
struct G< B >
{
  using type = typename Disj<
    typename Equate< B, Datum< size_t, 5 > >::type,
    typename Equate< B, Datum< size_t, 6 > >::type >::type;
};

  
  
using A_and_B = typename Conj<
  typename Call_fresh< Procedure< F > >::type,
  typename Call_fresh< Procedure< G > >::type
  >::type;



using Output = typename Apply< A_and_B, Empty_state >::type;





int
main()
{
  
  COMBINE_STATIC_ASSERT_SAME_TYPE( ARG( And< Nil, int >::type ), Nil );
  COMBINE_STATIC_ASSERT_TRUE( Consp< Empty_state >::value );

  using Expected_0_0 = Cons< Cons< Cons< Var< 0 >, Datum< size_t, 5 > >, Nil >, Datum< size_t, 1 > >;
  COMBINE_STATIC_ASSERT_SAME_TYPE( Test0::type0, Expected_0_0 );
  
  using Expected_0_1 = Nil;
  COMBINE_STATIC_ASSERT_SAME_TYPE( Test0::type1, Expected_0_1 );

  std::cout << "******************************************************************" << std::endl
	    << "Test0 " << std::endl
	    << "******************************************************************" << std::endl
	    << Type< Test0::type >()  << std::endl
            << Type< Test0::type0 >() << std::endl
	    << Type< Test0::type1 >() << std::endl << std::endl << std::endl;

  
  return 0;
}
