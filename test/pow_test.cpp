/**
   @file
   pow_test.cpp

   @brief
   UNDOCUMENTED

   @author: 
   Samuel Johnson <sabjohnso@yahoo.com>
*/

//
// ... Standard header files
//
#include <array>
#include <vector>

//
// ... Combine header files
//
#include <combine/macro_tools.hpp>
#include <combine/context.hpp>
#include <combine/pow.hpp>

using Combine::PowX;
using Combine::PowXn;



template< typename X >
class Vector
  : public std::vector< X >
{
public:
  using std::vector< X >::vector;
};

template< template< typename ... > class C >
struct Basic
{
  template< typename X >
  class Context
    : public C< X >
  {
  public:
    using C<X>::C;
  };
  
};




int
main( int argc, char** argv )
{

  using array2x2 = typename PowXn< double, std::array, 2, 2 >::type;
  using expected2x2 = std::array< std::array< double, 2 >, 2 >;
  COMBINE_STATIC_ASSERT_SAME_TYPE( array2x2, expected2x2 );

  using array2x2x2 = typename PowXn< double, std::array, 2, 2, 2 >::type;
  using expected2x2x2 = std::array< std::array< std::array< double, 2 >, 2>, 2 >;
  COMBINE_STATIC_ASSERT_SAME_TYPE( array2x2x2, expected2x2x2 );

  using array3D = typename PowX< double, Vector, 3 >::type;
  using expeced3D = Vector< Vector< Vector< double > > >;
  COMBINE_STATIC_ASSERT_SAME_TYPE( array3D, expeced3D );


  using XXX = typename PowX< double, Basic< std::vector >::Context, 3 >::type;
  using YYY = Basic< std::vector >::Context< Basic< std::vector >::Context< Basic< std::vector >::Context< double > > >;

  COMBINE_STATIC_ASSERT_SAME_TYPE( XXX, YYY );
  

  return 0;
  
}



