
//
// ... Standard header files
//
#include <array>

//
// .. Combine header files
//
#include <combine/macro_tools.hpp>
#include <combine/import.hpp>
#include <combine/make.hpp>
#include <combine/mdarray.hpp>


using Combine::MakeXn;
using Combine::MDArray;
using Combine::get;
  

template< typename X, size_t ... sizes >
using Array = MDArray< X, std::array, sizes ... >;

constexpr auto make_array = MakeXn<std::array>{};


int
main( int argc, char** argv )
{
  
  // Construction from rvalues
  {
    constexpr Array< double, 2, 2 > x =
      make_array( make_array( 1.0, 2.0 ),
		  make_array( 3.0, 4.0 ));

    COMBINE_STATIC_ASSERT_EQUAL( 1.0, x[ 0 ][ 0 ] );
    COMBINE_STATIC_ASSERT_EQUAL( 2.0, x[ 0 ][ 1 ] );
    COMBINE_STATIC_ASSERT_EQUAL( 3.0, x[ 1 ][ 0 ] );
    COMBINE_STATIC_ASSERT_EQUAL( 4.0, x[ 1 ][ 1 ] );
  }

  // Construction from lvalues
  {
    constexpr auto a = 1.0;
    constexpr auto b = 2.0;
    constexpr auto c = 3.0;
    constexpr auto d = 4.0;

    constexpr auto ab = make_array( a, b );
    constexpr auto cd = make_array( c, d );
    constexpr auto abcd = make_array( ab, cd );

    constexpr auto x = Array< double, 2, 2 >( abcd );


    COMBINE_STATIC_ASSERT_EQUAL( 1.0, x[ 0 ][ 0 ] );
    COMBINE_STATIC_ASSERT_EQUAL( 2.0, x[ 0 ][ 1 ] );
    COMBINE_STATIC_ASSERT_EQUAL( 3.0, x[ 1 ][ 0 ] );
    COMBINE_STATIC_ASSERT_EQUAL( 4.0, x[ 1 ][ 1 ] );

    COMBINE_STATIC_ASSERT_EQUAL( 1.0, ( get<0,0>( x )));
    COMBINE_STATIC_ASSERT_EQUAL( 2.0, ( get<0,1>( x )));
    COMBINE_STATIC_ASSERT_EQUAL( 3.0, ( get<1,0>( x )));
    COMBINE_STATIC_ASSERT_EQUAL( 4.0, ( get<1,1>( x )));
    
  }


  // Addition
  {
    constexpr auto x = Array< double, 2, 2 >(
      make_array( make_array( 1.0, 2.0 ),
		  make_array( 3.0, 4.0 )));
    constexpr auto y = Array< double, 2, 2 >(
      make_array( make_array( 5.0, 6.0 ),
		  make_array( 7.0, 8.0 )));

    constexpr auto z = x+y;

    COMBINE_STATIC_ASSERT_EQUAL( 6.0,  (get<0,0>( z )));
    COMBINE_STATIC_ASSERT_EQUAL( 8.0,  (get<0,1>( z )));
    COMBINE_STATIC_ASSERT_EQUAL( 10.0, (get<1,0>( z )));
    COMBINE_STATIC_ASSERT_EQUAL( 12.0, (get<1,1>( z )));
    
  }

  
  // Subtraction
  {
    constexpr auto x = Array< double, 2, 2 >(
      make_array( make_array( 1.0, 2.0 ),
		  make_array( 3.0, 4.0 )));
    constexpr auto y = Array< double, 2, 2 >(
      make_array( make_array( 5.0, 6.0 ),
		  make_array( 7.0, 8.0 )));

    constexpr auto z = x-y;

    COMBINE_STATIC_ASSERT_EQUAL( -4.0, (get<0,0>( z )));
    COMBINE_STATIC_ASSERT_EQUAL( -4.0, (get<0,1>( z )));
    COMBINE_STATIC_ASSERT_EQUAL( -4.0, (get<1,0>( z )));
    COMBINE_STATIC_ASSERT_EQUAL( -4.0, (get<1,1>( z )));
    
  }

  // Multiplication
  {
    constexpr auto x = Array< double, 2, 2 >(
      make_array( make_array( 1.0, 2.0 ),
		  make_array( 3.0, 4.0 )));
    constexpr auto y = Array< double, 2, 2 >(
      make_array( make_array( 5.0, 6.0 ),
		  make_array( 7.0, 8.0 )));

    constexpr auto z = x*y;

    COMBINE_STATIC_ASSERT_EQUAL( 5.0,  (get<0,0>( z )));
    COMBINE_STATIC_ASSERT_EQUAL( 12.0, (get<0,1>( z )));
    COMBINE_STATIC_ASSERT_EQUAL( 21.0, (get<1,0>( z )));
    COMBINE_STATIC_ASSERT_EQUAL( 32.0, (get<1,1>( z )));
    
  }

  // Division
  {
    constexpr auto x = Array< double, 2, 2 >(
      make_array( make_array( 1.0, 2.0 ),
		  make_array( 3.0, 4.0 )));
    constexpr auto y = Array< double, 2, 2 >(
      make_array( make_array( 2.0, 4.0 ),
		  make_array( 6.0, 8.0 )));

    constexpr auto z = x/y;

    COMBINE_STATIC_ASSERT_EQUAL( 0.5, (get<0,0>( z )));
    COMBINE_STATIC_ASSERT_EQUAL( 0.5, (get<0,1>( z )));
    COMBINE_STATIC_ASSERT_EQUAL( 0.5, (get<1,0>( z )));
    COMBINE_STATIC_ASSERT_EQUAL( 0.5, (get<1,1>( z )));
  }


  // Modulo
  {
    constexpr auto x = Array< int, 2, 2 >(
      make_array( make_array( 4, 5 ),
		  make_array( 6, 7 )));
    constexpr auto y = Array< int, 2, 2 >(
      make_array( make_array( 1, 2 ),
		  make_array( 3, 4 )));

    constexpr auto z = x % y;

    COMBINE_STATIC_ASSERT_EQUAL( 0, (get<0,0>( z )));
    COMBINE_STATIC_ASSERT_EQUAL( 1, (get<0,1>( z )));
    COMBINE_STATIC_ASSERT_EQUAL( 0, (get<1,0>( z )));
    COMBINE_STATIC_ASSERT_EQUAL( 3, (get<1,1>( z )));
  }
  

  return 0;
  
}
