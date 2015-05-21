/** @file test/nth_test.cpp

    @brief A test for the Nth structure template.

    @author Samuel B. Johnson <sabjohnso@yahoo.com>
*/

// Standard header files

#include <type_traits>


// Combine header files

#include <combine/macro_tools.hpp>
#include <combine/nth.hpp>

int
main( int argc, char** argv )
{

  using Combine::Nth;
  
  COMBINE_STATIC_ASSERT_SAME_TYPE( short, ARG( Nth< 0, short, int, long long >::type ));
  COMBINE_STATIC_ASSERT_SAME_TYPE( int, ARG( Nth< 1, short, int, long long >::type ));
  COMBINE_STATIC_ASSERT_SAME_TYPE( long long, ARG( Nth< 2, short, int, long long >::type ));
  
  return 0;
}
