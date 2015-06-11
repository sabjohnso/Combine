/**

   @file
   operator.hpp

   @brief
   UNDOCUMENTED

   @author: 
   Samuel Johnson <sabjohnso@yahoo.com>

*/
#ifndef OPERATOR_HPP_INCLUDED_2049968923608873682
#define OPERATOR_HPP_INCLUDED_2049968923608873682

//
// ... Combine header files
//
#include <combine/import.hpp>
#include <combine/fold.hpp>


namespace Combine
{

  template< typename Kernel, template< typename > class Fold >
  struct Operator : Kernel, Fold< Operator< Kernel, Fold > >
  {
    using Kernel::operator();
    using Fold< Operator< Kernel, Fold > >::operator ();
  };



#define X( op, name, ...  )						\
  struct name##_kernel							\
  {									\
    template< typename A, typename B >					\
    constexpr auto							\
    operator ()( A&& a, B&& b ) const					\
    {									\
      return forward<A>( a ) op forward<B>( b );			\
    }									\
  }
#include <combine/infix_operator_list.def>
#undef X


#define X( op, name, fold_suffix, ... ) using name = Operator< name##_kernel, Fold##fold_suffix >;
#include <combine/infix_operator_list.def>
#undef X

  
  

  
  constexpr auto sum = Addition{};

  constexpr auto product = Multiplication{};
  constexpr auto subtract = Subtraction{};
  constexpr auto divide = Division{};

  

  
} // end of namespace Combine


#endif // OPERATOR_HPP_INCLUDED_2049968923608873682
