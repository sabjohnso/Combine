
//
// ... Combine header files
//
#include <combine/macro_tools.hpp>
#include <combine/driver.hpp>




int
test_main0()
{
  return Combine::DriverPipeline< int, double >( 1.0 );
}

int
main( int argc, char** argv )
{
  COMBINE_TEST_EQUAL( test_main0(), 0 );
  return 0;
}
