/**
   
   @file
   length_test.cpp

   @brief
   UNDOCUMENTED

   @author: 
   Samuel Johnson <sabjohnso@yahoo.com>

*/

//
// ... Standard header files
//
#include <tuple>
#include <array>


//
// ... Combine header files
//
#include <combine/macro_tools.hpp>
#include <combine/length.hpp>



int
main( int argc, char** argv )
{
  using Combine::length;
  using std::array;
  using std::tuple;

  using darray2 = array< double, 2 >;

  COMBINE_STATIC_ASSERT_EQUAL( 2, length< darray2 >());

  using dtuple2 = tuple< double, double >;

  COMBINE_STATIC_ASSERT_EQUAL( 2, length< dtuple2 >());

  return 0;
}
