#include <tuple>
#include <array>

//
// ... Combine header files
//
#include <combine/import.hpp>
#include <combine/macro_tools.hpp>
#include <combine/transpose.hpp>

using std::get;

using Combine::decay;
using Combine::Length;
using Combine::length;


constexpr auto transpose = Combine::Transpose{};


int
main( int argc, char** argv )
{
  using std::make_tuple;
  constexpr auto array = Combine::MakeXn<std::array>{};

  {
    COMBINE_STATIC_ASSERT_EQUAL( 2, Length< decltype( make_tuple( make_tuple( 1, 2, 3 ), make_tuple( 4, 5, 6 ))) >::value  );
    COMBINE_STATIC_ASSERT_EQUAL( 2, length< decltype( make_tuple( make_tuple( 1, 2, 3 ), make_tuple( 4, 5, 6 )))>() );

    constexpr auto a = make_tuple( make_tuple( 1, 2, 3), make_tuple( 4, 5, 6 ));
    constexpr auto b = transpose( a );
    constexpr auto c = transpose( make_tuple( make_tuple( 1, 2, 3 ), make_tuple(4, 5, 6 )));

    COMBINE_STATIC_ASSERT_EQUAL( 1, get<0>(get<0>( b )));
    COMBINE_STATIC_ASSERT_EQUAL( get<0>(get<0>( b )), get<0>(get<0>( a )));
    COMBINE_STATIC_ASSERT_EQUAL( get<0>(get<1>( b )), get<1>(get<0>( a )));
    COMBINE_STATIC_ASSERT_EQUAL( get<1>(get<0>( b )), get<0>(get<1>( a )));
    COMBINE_STATIC_ASSERT_EQUAL( get<1>(get<1>( b )), get<1>(get<1>( a )));
    

    COMBINE_STATIC_ASSERT_EQUAL( 1, get<0>(get<0>( c )));
    COMBINE_STATIC_ASSERT_EQUAL( get<0>(get<0>( c )), get<0>(get<0>( a )));
    COMBINE_STATIC_ASSERT_EQUAL( get<0>(get<1>( c )), get<1>(get<0>( a )));
    COMBINE_STATIC_ASSERT_EQUAL( get<1>(get<0>( c )), get<0>(get<1>( a )));
    COMBINE_STATIC_ASSERT_EQUAL( get<1>(get<1>( c )), get<1>(get<1>( a )));
  }


  {
    constexpr auto a = array( array( 1, 2, 3 ), array( 4, 5, 6 ));
    constexpr auto b = transpose( a );
    
    COMBINE_STATIC_ASSERT_EQUAL( 2, length<decltype( a )>());
    COMBINE_STATIC_ASSERT_EQUAL( 3, length<decltype( get<0>( a ))>());

    
    COMBINE_STATIC_ASSERT_EQUAL( 3, length<decltype( b )>());
    COMBINE_STATIC_ASSERT_EQUAL( 2, length<decltype(get<0>( b ))>());

    COMBINE_STATIC_ASSERT_EQUAL( a[0][0], b[0][0] );
    COMBINE_STATIC_ASSERT_EQUAL( a[1][0], b[0][1] );
    COMBINE_STATIC_ASSERT_EQUAL( a[0][1], b[1][0] );
    COMBINE_STATIC_ASSERT_EQUAL( a[1][1], b[1][1] );
    COMBINE_STATIC_ASSERT_EQUAL( a[0][2], b[2][0] );
    COMBINE_STATIC_ASSERT_EQUAL( a[1][2], b[2][1] );
    
  }


  
  return 0;
}
