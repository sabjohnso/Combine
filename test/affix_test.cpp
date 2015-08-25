


// standard header files

#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>


// Combine header files

#include <combine/macro_tools.hpp>
#include <combine/affix.hpp>


void check( const std::vector<int>& x, const std::vector<int>& y ){
  COMBINE_TEST_EQUAL( x.size(), y.size());
  COMBINE_TEST_TRUE( std::equal( begin( x ), end( x ), begin( y )));
}


int
main( int argc, char** argv )
{

  {
    std::vector< int > a { 0, 0 };
    std::vector<int> aout;
    Combine::prefix_copy( begin( a ), end( a ), std::back_inserter( aout ), 1 );
    check( a, { 0, 0 });
    check( aout, { 1, 0, 0 });
  }
    
  {
    std::vector< int > a { 0, 0 };
    std::vector<int> aout;
    Combine::suffix_copy( begin( a ), end( a ), std::back_inserter( aout ), 1 );
    check( a, { 0, 0 });
    check( aout, { 0, 0, 1 });
  }

   
  {
    std::vector< int > a { 0, 0 };
    std::vector<int> aout;
    Combine::infix_copy( begin( a ), end( a ), std::back_inserter( aout ), 1 );
    check( a, { 0, 0 });
    check( aout, { 0, 1, 0 });
  }


  {
    std::vector< int > a { 0, 0 };
    std::vector<int> aout;
    Combine::circumfix_copy( begin( a ), end( a ), std::back_inserter( aout ), 1, 2 );
    check( a, { 0, 0 });
    check( aout, { 1, 0, 0, 2 });
  }
  

  {
    std::vector< int > a { 0, 0 };
    std::vector<int> aout;
    Combine::affix_copy( begin( a ), end( a ), std::back_inserter( aout ), 1, 2, 3 );
    check( a, { 0, 0 });
    check( aout, { 1, 0, 2, 0, 3 });
  }



  {
    std::vector< int > a {};
    std::vector<int> aout;
    Combine::prefix_copy( begin( a ), end( a ), std::back_inserter( aout ), 1 );
    check( a, {});
    check( aout, {});
  }
    
  {
    std::vector< int > a {};
    std::vector<int> aout;
    Combine::suffix_copy( begin( a ), end( a ), std::back_inserter( aout ), 1 );
    check( a, {});
    check( aout, {});
  }

   
  {
    std::vector< int > a {};
    std::vector<int> aout;
    Combine::infix_copy( begin( a ), end( a ), std::back_inserter( aout ), 1 );
    check( a, {});
    check( aout, {});
  }


  {
    std::vector< int > a {};
    std::vector<int> aout;
    Combine::circumfix_copy( begin( a ), end( a ), std::back_inserter( aout ), 1, 2 );
    check( a, {});
    check( aout, { 1, 2 });

  }
  

  {
    std::vector< int > a {};
    std::vector<int> aout;
    Combine::affix_copy( begin( a ), end( a ), std::back_inserter( aout ), 1, 2, 3 );
    check( a, {});
    check( aout, { 1, 3 });
  }


  {
    std::vector<std::string> a { "a", "b", "c" };
    std::stringstream ss;
    Combine::affix_copy( 
      begin( a ), end( a ),
      std::ostream_iterator<std::string>( ss ),
      "{ ", ", ", " }" );
    COMBINE_TEST_EQUAL( ss.str(), "{ a, b, c }" );
  }

  {
    std::vector<std::string> a{ "Samuel", " B. ", "Johnson" };
    std::stringstream ss;
    Combine::prefix_copy(
      begin( a ), end( a ),
      std::ostream_iterator<std::string>( ss ),
      "Dr. " );
    COMBINE_TEST_EQUAL( ss.str(), "Dr. Samuel B. Johnson" );
     
	
  }



  {
    std::vector<double> a;
    std::generate_n( std::back_inserter( a ), 10, [i = 0]() mutable { return i++; });

    Combine::affix_transform( 
      begin( a ), end( a ),
      std::ostream_iterator<std::string>( std::cout ),
      [](){ return std::string("#{");},
      [](auto a){ return std::to_string( a ); },
      [](){ return std::string(" "); },
      [](){ return std::string( "}" ); });
  }


  
  {
    std::vector<double> a;
    std::generate_n( std::back_inserter( a ), 10, [i = 0]() mutable { return i++; });

    Combine::affix_transform( 
      begin( a ), end( a ),
      std::ostream_iterator<std::string>( std::cout << std::endl ),
      [](){ return std::string("#{");},
      [index = 'a', index_repr = std::string("a")](auto a) mutable 
      {
	index_repr[0] = index++;
	return ":" + index_repr  + " " + std::to_string( a ); },
      [](){ return std::string("\n  "); },
      [](){ return std::string( "}" ); });
  }

  
  {
    std::vector<double> a;
    std::generate_n( std::back_inserter( a ), 11, []()mutable{ return 0; });
    std::vector<double> b;

    Combine::circumfix_transform<1,3, 1>(
      begin( a ), end( a ), std::back_inserter( b ),
      []( auto x ){ return x; },
      []( auto xim, auto xi, auto xip ){ return (xim-2*xi+xip); },
      []( auto x ){ return x-1; });

    std::vector<double> expect = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1 };

    auto printfn = []( auto c ){
      Combine::affix_transform(
	begin( c ), end ( c ),
	std::ostream_iterator<std::string>( std::cout ),
	[](){ return std::string( "[" ); },
	[]( auto x ){ return std::to_string( x ); },
	[](){ return std::string( ", " ); },
	[](){ return std::string( "]" ); });
      std::cout << std::endl; };

    std::cout << std::endl;
    printfn( a );
    printfn( b );
    printfn( expect );
	
      

    COMBINE_TEST_TRUE( std::equal( begin( b ), end( b ), begin( expect )));


    
  }



      
  

  return 0;
  
}
