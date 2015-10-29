

//
// ... Standard header files
//
#include <exception>


// ... Combine header files
//
#include <combine/import.hpp>
#include <combine/macro_tools.hpp>
#include <combine/exception_handler.hpp>


class MyNewException : public std::exception
{
public:

  MyNewException( std::string&&  message )
    : msg( message )
  {}
  
  virtual const char*
  what() const noexcept
  {
    return msg.c_str();
  }
  
private:

  std::string msg;
};



int
main( int argc, char** argv )
{
  using Combine::Exception_handler;

  // The exception handler should catch with the first template parameter and return an error signal of 1.
  try{ throw std::logic_error( "Oops!" );  }
  catch( ... )
  { 
    COMBINE_TEST_EQUAL( 1, int( Exception_handler< std::logic_error, std::runtime_error >( std::current_exception())));
  }

  // The exception handler should catch with the second template parameter and return an error signal of 2.
  try{ throw std::runtime_error( "Dang!" ); }
  catch( ... )
  {
    COMBINE_TEST_EQUAL( 2, int( Exception_handler< std::logic_error, std::runtime_error >( std::current_exception())));
  }

  // The exception handler should catch with a std::exception because the exceptions in the template parameter
  // list are not being thrown, but the exception that is being thrown is derived from std::exception.
  try{ throw MyNewException( "Eeeaak!" ); }
  catch( ... )
  {
    COMBINE_TEST_EQUAL( 3, int( Exception_handler< std::logic_error, std::runtime_error >( std::current_exception())));
  }
      
  
  return 0;
}
