/**
   
   @file
   Exception_handler.hpp

   @brief
   Handle exceptions.

   @author: 
   Samuel Johnson <sabjohnso@yahoo.com>

*/


#ifndef EXCEPTION_HANDLER_HPP_INCLUDED
#define EXCEPTION_HANDLER_HPP_INCLUDED

//
// ... Combine header files
//
#include <combine/import.hpp>
#include <combine/error_signal.hpp>



namespace Combine
{

  template< typename ... >
  class Exception_handler;



  template<>
  class Exception_handler<> : public Error_signal
  {
  public:
    Exception_handler( exception_ptr eptr, int sig = 1 )
      : Error_signal( sig )
    {
      if( eptr )
      {
	try{ rethrow_exception( eptr ); }
	catch( exception e )
	{
	  cerr << e.what() << endl;
	}
      }
    }
  };
  

  template< typename E, typename ... Es >
  class Exception_handler< E, Es ... > : public Error_signal
  {
  public:
    Exception_handler( exception_ptr eptr, int sig = 1 )
      : Error_signal( sig )
    {
      if( eptr )
      {
	try{ rethrow_exception( eptr ); }
	catch( E& e )
	{
	  cerr << e.what() << endl;
	}
	catch( ... )
	{
	  signal = Exception_handler<Es ...>( current_exception(), sig+1 );
	}
      }
    }
  };
  
  

}// end of namespace Combine


  




#endif // EXCEPTION_HANDLER_HPP_INCLUDED
