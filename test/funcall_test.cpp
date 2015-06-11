//
// ... Combine header files
//
#include <combine/macro_tools.hpp>
#include <combine/funcall.hpp>



constexpr static
struct Square
{
  template< typename X > 
  constexpr auto 
  operator()( X&& x )
  {
    return x*x;
  } 
} square{};


int
main( int arc, char** argv )
{
  using Combine::funcall;
  COMBINE_STATIC_ASSERT_EQUAL( 9, funcall( square, 3 ));
  return 0;
  
}
