
#include <exception>
#include <iostream>
#include <sstream>


#include <combine/macro_tools.hpp>
#include <combine/either.hpp>



int
main( int argc, char** argv )
{
  using  bool_or_int = Combine::Either<bool,int>;

  {
    auto x = bool_or_int::make_first( 0 );
    std::stringstream ss;
    ss << std::boolalpha << static_cast<bool&>( x );
    COMBINE_TEST_EQUAL( ss.str(), "false" );
  }

  {
    auto x = bool_or_int::make_second( 0 );
    std::stringstream ss;
    ss << std::boolalpha << static_cast<int&>( x );
    COMBINE_TEST_EQUAL( ss.str(), "0" );
  }



  {
    auto x = Combine::Either<int, std::string>();
    static_cast<int&>( x ) = 2;
    std::cout << static_cast<int&>( x )  << std::endl;
    auto y = Combine::Either<int, std::string>::make_second( "Hello, World!" );
    std::cout << static_cast<std::string&>( y ) << std::endl;

    x = y;
    std::cout << static_cast<std::string&>( x ) << std::endl;
  }
      

  return 0;
};
