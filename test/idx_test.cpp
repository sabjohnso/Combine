/** @file test/idx_test.hpp

    @brief A test for the functionality in the idx.hpp header file.
    
    @author Samuel B. Johnson <sabjohnso@yahoo.com>
*/

//
// ... Combine header files
//

#include <combine/macro_tools.hpp>
#include <combine/type.hpp>
#include <combine/idx.hpp>


int
main( int argc, char** argv )
{
  
  using Combine::Idx;
  using Combine::Gen_Idx;
  using Combine::gen_Idx;

  COMBINE_STATIC_ASSERT_SAME_TYPE( Idx<>, typename Gen_Idx< 0 >::type );
  COMBINE_STATIC_ASSERT_SAME_TYPE( Idx<>, decltype( gen_Idx< 0 >()));
  COMBINE_STATIC_ASSERT_SAME_TYPE( Idx<>, decltype( gen_Idx< >()));

  COMBINE_STATIC_ASSERT_SAME_TYPE( Idx< 0 >, typename Gen_Idx< 1 >::type );
  COMBINE_STATIC_ASSERT_SAME_TYPE( Idx< 0 >, decltype( gen_Idx< 1 >()));
  COMBINE_STATIC_ASSERT_SAME_TYPE( Idx< 0 >, decltype( gen_Idx< int >()));

  COMBINE_STATIC_ASSERT_SAME_TYPE( ARG( Idx< 0, 1, 2 >), typename Gen_Idx< 3 >::type );
  COMBINE_STATIC_ASSERT_SAME_TYPE( ARG( Idx< 0, 1, 2 >), decltype( gen_Idx< 3 >()));
  COMBINE_STATIC_ASSERT_SAME_TYPE( ARG( Idx< 0, 1, 2 >), decltype( gen_Idx< short, int, long long >()));
  
  return 0;
  
}
