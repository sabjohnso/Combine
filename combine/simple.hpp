/**
   @file
   simple.hpp

   @brief
   UNDOCUMENTED

   @author: 
   Samuel Johnson <sabjohnso@yahoo.com>
*/
#ifndef SIMPLE_HPP_INCLUDED_276115949462084280
#define SIMPLE_HPP_INCLUDED_276115949462084280

//
// ... Combine header files
//
#include <combine/import.hpp>
#include <combine/context.hpp>


namespace Combine
{


  template< typename, size_t ... >
  struct Simple;

  template< template< typename ... > class C >
  struct Simple< ContextX<C> >
  {
    template< typename X >
    class context : public C<X>
    {
    public:

      template< typename ... Xs >
      constexpr
      context( Xs&& ... xs ) : C<X>({ forward<Xs>( xs ) ... }){}
      using C<X>::C;
    };
  };
  
  template< template< typename, size_t > class C, size_t n >
  struct Simple< ContextXn<C>, n >
  {

    template< typename X >
    class context : public C<X,n>
    {
    public:
      
      template< typename ... Xs >
      constexpr
      context( Xs&& ... xs ) : C<X,n>({ forward<Xs>( xs ) ... }){}
      using C<X,n>::C;
    };
    
  };

} // end of namespace Combine



#endif // SIMPLE_HPP_INCLUDED_276115949462084280
