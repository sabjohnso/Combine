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

namespace Combine
{

  template< template< typename ... > class C >
  struct Simple
  {
    template< typename X >
    class context : public C<X>
    {
    public:
      using C<X>::C;
    };
  };

  
  template< template< typename, size_t > class C, size_t n >
  struct Simple
  {

    template< typename X >
    class context : public C<X,n>
    {
    public:
      using C<X,n>::C;
    };
    
  };

} // end of namespace Combine



#endif // SIMPLE_HPP_INCLUDED_276115949462084280
