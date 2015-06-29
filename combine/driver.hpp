/**
   @file
   driver.hpp

   @brief
   Simple application driver.

   @author: 
   Samuel Johnson <sabjohnso@yahoo.com>

*/


#ifndef DRIVER_HPP_INCLUDED_1225874022323118372
#define DRIVER_HPP_INCLUDED_1225874022323118372

//
// ... Combine header files
//
#include <combine/import.hpp>
#include <combine/error_signal.hpp>



namespace Combine
{



  
  template< typename ... Xs >
  class DriverPipeline;


  
  template< typename X >
  class DriverPipeline<X>  : public Error_signal_static<0>
  {
  public:
    template< typename ... Ys >
    constexpr
    DriverPipeline( Ys&& ... ys )
      : x( forward<Ys>( ys ) ... )
    {}
  private:
    X x;
  };


  template< typename X0, typename X1, typename ... Xs >
  class DriverPipeline< X0, X1, Xs ... > : public Error_signal_static<0>
  {
  public:
    template< typename ... Ys >
    constexpr
    DriverPipeline( Ys&& ... ys )
      : x( forward<Ys>( ys ) ... )
      , xs( x )
    {}

    X0 x;
    DriverPipeline< X1, Xs ... > xs;
  };


  



    
  
  
} // end of namespace Combine


#endif // DRIVER_HPP_INCLUDED
