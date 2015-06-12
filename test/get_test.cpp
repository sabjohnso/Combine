
//
// ... Standard header files
//
#include <utility>

//
// ... Combine header files
//
#include <combine/macro_tools.hpp>
#include <combine/funcall.hpp>
#include <combine/get.hpp>


using std::make_pair;

using Combine::getget;
constexpr auto funcall = Combine::Funcall{};


int
main( int argc, char** argv )
{
  COMBINE_STATIC_ASSERT_EQUAL( 1, funcall( getget< 0 >(), make_pair( 1, 2 )));
  COMBINE_STATIC_ASSERT_EQUAL( 2, funcall( getget< 1 >(), make_pair( 1, 2 )));

  return 0;
  
}
