#include <iostream>
#include <string>
#include <sstream>


#include <combine/maybe.hpp>



int
main( int argc, char** argv )
{

  {
    auto x = Combine::Maybe<int>::nothing();
    std::stringstream ss{};

    ss << x;

    COMBINE_TEST_EQUAL( ss.str(), "Nil" );
    COMBINE_TEST_FALSE( x.is());
    x = 2;
    COMBINE_TEST_TRUE( x.is());

    

    
  }
  

  
  
  
  
  

  



  
  return 0;
}
