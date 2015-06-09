/**
   @file
   make_test.cpp

   @brief
   UNDOCUMENTED

   @author: 
   Samuel Johnson <sabjohnso@yahoo.com>
*/

//
// ... Standard header files
//
#include <utility>
#include <tuple>
#include <array>

//
// ... Combine header files
//
#include <combine/macro_tools.hpp>
#include <combine/make.hpp>


constexpr auto pair  = Combine::MakeXs< std::pair >();
constexpr auto tuple = Combine::MakeXs< std::tuple >();

constexpr auto array = Combine::MakeXn< std::array >();


int
main( int argc, char** argv )
{
  using std::get;
  
  // Check the pair constructor
  {
    constexpr auto a = pair( 1, 2 );
    COMBINE_STATIC_ASSERT_EQUAL( get< 0 >( a ), 1 );
    COMBINE_STATIC_ASSERT_EQUAL( get< 1 >( a ), 2 );
  }

  // Check the tuple constructor
  {
    constexpr auto a = tuple( 1, 2, 3,4 );
    COMBINE_STATIC_ASSERT_EQUAL( get< 0 >( a ), 1 );
    COMBINE_STATIC_ASSERT_EQUAL( get< 1 >( a ), 2 );
    COMBINE_STATIC_ASSERT_EQUAL( get< 2 >( a ), 3 );
    COMBINE_STATIC_ASSERT_EQUAL( get< 3 >( a ), 4 );
  }

  // Check the array constructor
  {

    constexpr auto a  = array( 1, 2, 3, 4);
    COMBINE_STATIC_ASSERT_EQUAL( get< 0 >( a ), 1 );
    COMBINE_STATIC_ASSERT_EQUAL( get< 1 >( a ), 2 );
    COMBINE_STATIC_ASSERT_EQUAL( get< 2 >( a ), 3 );
    COMBINE_STATIC_ASSERT_EQUAL( get< 3 >( a ), 4 );
  }
  
  return 0;
}



