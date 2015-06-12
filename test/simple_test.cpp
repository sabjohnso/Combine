/**
   @file
   test/simple_test.cpp

   @brief
   UNDOCUMENTED

   @author: 
   Samuel Johnson <sabjohnso@yahoo.com>

*/


//
// ... standard header files
//
#include <stdexcept>
#include <array>
#include <vector>
#include <sstream>
#include <string>

//
// ... Combine header files
//
#include <combine/macro_tools.hpp>
#include <combine/simple.hpp>


using std::logic_error;

using Combine::Simple;
using Combine::ContextX;
using Combine::ContextXn;

template< typename X >
using vector = Simple< ContextX<std::vector> >::context<X>;

template< typename X >
using array3 = Simple< ContextXn<std::array>, 3 >::context<X>;


template< typename A, typename B >
void
check_equal( const A& a , const B& b )
{
  if( a != b )
  {
    throw( logic_error("Bad! Bad! Bad!"));
  }	  
}

int
main( int argc, char** argv )
{
  
  vector<double> x{ 1.0, 2.0, 3.0 };
  check_equal( x[ 0 ], 1.0 );
  check_equal( x[ 1 ], 2.0 );
  check_equal( x[ 2 ], 3.0 );

  constexpr auto  y = array3<double>{1.0,2.0,3.0};

  COMBINE_STATIC_ASSERT_EQUAL( y[ 0 ], 1.0 );
  COMBINE_STATIC_ASSERT_EQUAL( y[ 1 ], 2.0 );
  COMBINE_STATIC_ASSERT_EQUAL( y[ 2 ], 3.0 );

  return 0;
}


