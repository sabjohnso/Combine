/**
   @file
   apply_test.cpp

   @brief
   Test the Apply functionality.

   @author: 
   Samuel Johnson <sabjohnso@yahoo.com>

*/

//
// ... Standard header files
//
#include <tuple>

//
// ... Combine header files
//
#include <combine/macro_tools.hpp>
#include <combine/operator.hpp>
#include <combine/funcall.hpp>
#include <combine/apply.hpp>

int
main( int, char** )
{
  
  using std::make_tuple;
  using Combine::sum;
  using Combine::product;
  using Combine::funcall;
  using Combine::apply;
  
  COMBINE_STATIC_ASSERT_EQUAL( 6, apply( sum, make_tuple( 1, 2, 3 )));
  COMBINE_STATIC_ASSERT_EQUAL( 6, apply( product, make_tuple( 1, 2, 3 )));

  constexpr auto expr = make_tuple( sum, 1, 2, 3 );
  constexpr auto res = apply( funcall, make_tuple( sum, 1, 2, 3 ));

  COMBINE_STATIC_ASSERT_EQUAL( 6, res );

  COMBINE_STATIC_ASSERT_EQUAL( 6, apply( funcall, expr ));

  
  return 0;
}
