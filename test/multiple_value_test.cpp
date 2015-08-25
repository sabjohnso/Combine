


// Standard header files

#include <vector>


// Combine header files

#include <combine/datum.hpp>
#include <combine/macro_tools.hpp>
#include <combine/multiple_value.hpp>


int
main( int argc, char** argv )
{

  auto add_three_items = []( auto a, auto b, auto c ){ return a+b+c; };
  std::vector<int> x = { 1, 2, 3, 4 };

  auto y = Combine::Multiple_value_call{}( Combine::Datum<size_t,3>{}, add_three_items, begin( x ));
  COMBINE_TEST_EQUAL( y, 6 );

  
  return 0;


  
}
