/** @file test/count_test.cpp
    
    @brief Source file for a test type counting
    functionality in the count.hpp header file.

    @author Samuel B. Johnson <sabjohnso@yahoo.com>
 */


// Combine header files

#include <combine/macro_tools.hpp>
#include <combine/count.hpp>

int
main( int argc, char** argv )
{
  using Combine::Count_types;
  using Combine::count_types;

  COMBINE_STATIC_ASSERT_EQUAL( Count_types<>::value, 0 );
  COMBINE_STATIC_ASSERT_EQUAL( Count_types< int >::value, 1 );
  COMBINE_STATIC_ASSERT_EQUAL( ARG( Count_types< short, int, long long >::value ), 3 );

  COMBINE_STATIC_ASSERT_EQUAL( count_types<>(), 0 );
  COMBINE_STATIC_ASSERT_EQUAL( count_types< int >(), 1 );
  COMBINE_STATIC_ASSERT_EQUAL( ARG( count_types< short, int, long long >()), 3 );
  
  return 0;
}
