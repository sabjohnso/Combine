#include <utility>
#include <utility>



#include <combine/apply.hpp>
#include <combine/composite.hpp>
#include <combine/macro_tools.hpp>
#include <combine/make.hpp>
#include <combine/operator.hpp>



using std::pair;
using std::make_pair;
using std::get;


using Combine::MakeXn;
using Combine::MakeXs;
using Combine::Addition;

using Combine::SequentialComposite;
using Combine::ParallelComposite;
using Combine::StrangeComposite;
using Combine::WeirdComposite;

using Combine::apply;

constexpr auto comp  = MakeXs< SequentialComposite >{};
constexpr auto split = MakeXs< ParallelComposite >{};
constexpr auto trans = MakeXs< StrangeComposite >{};
constexpr auto quark = MakeXs< WeirdComposite >{};







struct Twice
{
  template< typename X >
  constexpr auto
  operator ()( X&& x ) const
  {
    return x+x;
  }
};

struct Square
{
  template< typename X >
  constexpr auto
  operator ()( X&& x ) const
  {
    return x*x;
  }
};

struct Dup
{
  constexpr static auto array = MakeXn<std::array>{};
  
  template< typename X >
  constexpr auto
  operator ()( X&& x ) const
  {
    return array( x, x );
  }
};




int
main( int argc, char** argv )
{

  constexpr auto square_twice = comp( Square{}, Twice{} );
  COMBINE_STATIC_ASSERT_EQUAL( 36, square_twice( 3 ));

  constexpr auto twice_square = comp( Twice{}, Square{} );
  COMBINE_STATIC_ASSERT_EQUAL( 18, twice_square( 3 ));

  constexpr auto square_sum = comp( Square{}, Addition{} );
  COMBINE_STATIC_ASSERT_EQUAL( 9, square_sum( 1, 2 ));

  constexpr auto square_and_twice = split( Square{}, Twice{} );
  COMBINE_STATIC_ASSERT_EQUAL( 9, get< 0 >( square_and_twice( make_pair( 3, 4 ))));
  COMBINE_STATIC_ASSERT_EQUAL( 8, get< 1 >( square_and_twice( make_pair( 3, 4 ))));

  constexpr auto add_squares = trans( Addition{}, Square{} );
  COMBINE_STATIC_ASSERT_EQUAL( 25, add_squares( 3, 4 ));



  constexpr auto add = Addition{};
  constexpr auto dup = Dup{};

  constexpr auto twice = quark( Addition{}, Dup{} );

  COMBINE_STATIC_ASSERT_EQUAL( 4, twice( 2 ));
  
  constexpr auto twice_ = quark( add, dup );

  



  
  

  
  return 0;
}
