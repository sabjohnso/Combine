/** @file test/list_test.cpp
    
    @author Samuel B. Johnson <sabjohnso@yahoo.com>

 */


// Combine header files

#include <combine/macro_tools.hpp>
#include <combine/nil.hpp>
#include <combine/cons.hpp>
#include <combine/list.hpp>

int
main( int argc, char** argv )
{
  using Combine::Nil;
  using Combine::List;
  using Combine::Listp;
  using Combine::Consp;
  using Combine::Length;
  using Combine::Reverse;
  using Combine::Car;
  using Combine::Cdr;
  using Combine::Nth_list;
  using Integer_types = typename List< short, int, long long >::type;
  
  
  COMBINE_STATIC_ASSERT_TRUE( Listp< Nil >::value );
  COMBINE_STATIC_ASSERT_TRUE( Consp< Integer_types >::value );
  COMBINE_STATIC_ASSERT_TRUE( Listp< Integer_types >::value );

  COMBINE_STATIC_ASSERT_EQUAL( 0, Length< Nil >::value );
  COMBINE_STATIC_ASSERT_EQUAL( 3, ARG( Length< Integer_types >::value ));
  COMBINE_STATIC_ASSERT_SAME_TYPE( short, Car< Integer_types >:: type );

  COMBINE_STATIC_ASSERT_SAME_TYPE( short, ARG( Nth_list< 0, Integer_types >::type ));
  COMBINE_STATIC_ASSERT_SAME_TYPE( int, ARG( Nth_list< 1, Integer_types >::type ));
  COMBINE_STATIC_ASSERT_SAME_TYPE( long long, ARG( Nth_list< 2, Integer_types >::type ));


  using Integer_types_reversed = typename Reverse< Integer_types >::type;

  COMBINE_STATIC_ASSERT_TRUE( Listp< Integer_types_reversed >::value );
  COMBINE_STATIC_ASSERT_EQUAL( 3, ARG( Length< Integer_types_reversed >::value ));
  COMBINE_STATIC_ASSERT_SAME_TYPE( long long, Car< Integer_types_reversed >::type );

  COMBINE_STATIC_ASSERT_SAME_TYPE( long long, ARG( Nth_list< 0, Integer_types_reversed >::type ));
  COMBINE_STATIC_ASSERT_SAME_TYPE( int, ARG( Nth_list< 1, Integer_types_reversed >::type ));
  COMBINE_STATIC_ASSERT_SAME_TYPE( short, ARG( Nth_list< 2, Integer_types_reversed >::type ));
  
  return 0;

}
