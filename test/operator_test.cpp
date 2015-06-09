/**

   @file
   test/operator_test.cpp

   @brief
   UNDOCUMENTED

   @author: 
   Samuel Johnson <sabjohnso@yahoo.com>

*/


//
// ... Combine header files
//
#include <combine/macro_tools.hpp>
#include <combine/operator.hpp>


int
main( int argc, char** argv )
{

  using Combine::sum;
  using Combine::product;

  COMBINE_STATIC_ASSERT_EQUAL( sum( 1, 2 ), 3 );
  COMBINE_STATIC_ASSERT_EQUAL( sum( 1, 2, 3 ), 6 );

  COMBINE_STATIC_ASSERT_EQUAL( product( 1, 2 ), 2 );
  COMBINE_STATIC_ASSERT_EQUAL( product( 1, 2, 3 ), 6 );
  
  return 0;
}



