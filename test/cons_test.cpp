/**
 */

// Combine header files

#include <combine/macro_tools.hpp>
#include <combine/cons.hpp>

int
main( int argc, char** argv )
{
  using Combine::Cons;
  using Combine::Car;
  using Combine::Cdr;
  using Combine::Nil;
  using Combine::Consp;

  
  using P = Cons< int, Nil >;

  COMBINE_STATIC_ASSERT_TRUE( Consp< P >::value  );
  COMBINE_STATIC_ASSERT_SAME_TYPE( int, Car< P >::type );
  COMBINE_STATIC_ASSERT_SAME_TYPE( Nil, Cdr< P >::type );

  COMBINE_STATIC_ASSERT_FALSE( Consp< int >::value );

  return 0;
  
}
