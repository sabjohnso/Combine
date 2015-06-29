/**
   
   @file
   error_signal.hpp

   @brief
   Error Signals

   @author: 
   Samuel Johnson <sabjohnso@yahoo.com>

*/


#ifndef ERROR_SIGNAL_HPP_INCLUDED_2204451516911388277
#define ERROR_SIGNAL_HPP_INCLUDED_2204451516911388277


namespace Combine
{



  /** A static error signal returns the signal embedded in its template parameter list, when cast as an int.
   */
  template< int signal >
  struct Error_signal_static
  {
  public:
    constexpr 
    operator int() const
    {
      return  signal;
    }
  };



  /** A dynamic error signal will return the signal which is member data when cast as an int.
   */
  struct Error_signal
  {
  public:
    constexpr
    operator int() const
    {
      return signal;
    }

    void
    set_signal( int arg )
    {
      signal = arg;
    }
    
  protected:

    constexpr
    Error_signal( int signal ) : signal( signal ){}

  protected:
    int signal;
  };
  


  
  
} // end of namespace Combine


#endif // ERROR_SIGNAL_HPP_INCLUDED_2204451516911388277
