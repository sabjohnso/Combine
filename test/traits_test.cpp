/**
   @file
   traits_test.cpp

   @brief
   A header test of the functionality in the
   combine/traits.hpp file.

   @author: 
   Samuel Johnson <sabjohnso@yahoo.com>
   
*/

//
// ... Combine header files
//
#include <combine/macro_tools.hpp>
#include <combine/traits.hpp>


int
main( int argc, char** argv )
{
  using Combine::is_homogeneous;

  COMBINE_STATIC_ASSERT_TRUE( is_homogeneous< int, int, int >::value );
  COMBINE_STATIC_ASSERT_TRUE( is_homogeneous< long, long, long >::value );
  COMBINE_STATIC_ASSERT_TRUE( is_homogeneous< double, double >::value );
  COMBINE_STATIC_ASSERT_TRUE( is_homogeneous< double >::value );


  COMBINE_STATIC_ASSERT_FALSE( is_homogeneous< int, double, double >::value );
  COMBINE_STATIC_ASSERT_FALSE( is_homogeneous< double, int, double >::value );
  COMBINE_STATIC_ASSERT_FALSE( is_homogeneous< double, double, int >::value );
  COMBINE_STATIC_ASSERT_FALSE( is_homogeneous<>::value );
  COMBINE_STATIC_ASSERT_FALSE( is_homogeneous< double, double& >::value );
  COMBINE_STATIC_ASSERT_FALSE( is_homogeneous< double, double&& >::value );
  COMBINE_STATIC_ASSERT_FALSE( is_homogeneous< double&, double&& >::value );
  COMBINE_STATIC_ASSERT_FALSE( is_homogeneous< const double, double >::value );
  COMBINE_STATIC_ASSERT_FALSE( is_homogeneous< volatile double, double >::value );
  
  return 0;
}




