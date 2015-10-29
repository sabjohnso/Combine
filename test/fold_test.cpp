/**

   @file
   fold_test.cpp

   @brief
   UNDOCUMENTED

   @author: 
   Samuel Johnson <sabjohnso@yahoo.com>

*/

//
// ... Combine header files
//
#include <combine/macro_tools.hpp>
#include <combine/fold.hpp>

using Combine::FoldL;
using Combine::FoldR;
using Combine::FoldDC;

struct AddKernel
{
  template< typename A, typename B >
  constexpr auto
  operator ()( A&& a, B&& b ) const
  {
    return a+b;
  }
};

struct AddL : AddKernel, FoldL< AddL >{ using AddKernel::operator(); using FoldL<AddL>::operator(); };
struct AddR : AddKernel, FoldR< AddR >{ using AddKernel::operator(); using FoldR<AddR>::operator(); };
struct AddDC : AddKernel, FoldDC< AddDC >{ using AddKernel::operator(); using FoldDC<AddDC>::operator(); };

constexpr auto addL = AddL{};
constexpr auto addR = AddR{};
constexpr auto addDC = AddDC{};



int
main( int argc, char** argv )
{

  
  COMBINE_STATIC_ASSERT_EQUAL( addL( 1, 2 ), 3 );
  COMBINE_STATIC_ASSERT_EQUAL( addR( 1, 2 ), 3 );
  COMBINE_STATIC_ASSERT_EQUAL( addDC( 1, 2 ), 3 );
  
  COMBINE_STATIC_ASSERT_EQUAL( addL( 1, 2, 3 ), 6 );
  COMBINE_STATIC_ASSERT_EQUAL( addR( 1, 2, 3 ), 6 );
  COMBINE_STATIC_ASSERT_EQUAL( addDC( 1, 2, 3 ), 6 );

  
  COMBINE_STATIC_ASSERT_EQUAL( addL( 1, 2, 3, 4 ), 10 );
  COMBINE_STATIC_ASSERT_EQUAL( addR( 1, 2, 3, 4 ), 10 );
  COMBINE_STATIC_ASSERT_EQUAL( addDC( 1, 2, 3, 4 ), 10 );


  COMBINE_STATIC_ASSERT_EQUAL( addL( 1, 2, 3, 4, 5 ), 15 );
  COMBINE_STATIC_ASSERT_EQUAL( addR( 1, 2, 3, 4, 5 ), 15 );
  COMBINE_STATIC_ASSERT_EQUAL( addDC( 1, 2, 3, 4, 5 ), 15 );

  
  return 0;
  
}


