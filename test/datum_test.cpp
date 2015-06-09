
//
// ... Standard header files
//
#include <cstddef>

//
// ... Combine header files
//
#include <combine/macro_tools.hpp>
#include <combine/datum.hpp>


int
main()
{
  using Combine::Datum;
  COMBINE_STATIC_ASSERT_EQUAL( ARG( Datum< size_t, 1 >::value ), 1 );
  COMBINE_STATIC_ASSERT_SAME_DECAY( decltype( Datum< size_t, 1 >::value ), size_t );
  return 0;
}
