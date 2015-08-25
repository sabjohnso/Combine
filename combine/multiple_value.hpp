/**
 */

#ifndef MULTIPLE_VALUE_HPP_INCLUDED_223145455877848627
#define MULTIPLE_VALUE_HPP_INCLUDED_223145455877848627 1


// Combine header files

#include <combine/import.hpp>
#include <combine/idx.hpp>

namespace Combine
{

  struct Multiple_value_call
  {

    template< size_t n, typename Function, typename Iterator >
    auto 
    operator()( Datum< size_t, n >, Function&& function, Iterator it )
    {
      return exe<n>( forward<Function>( function ), it );
    }

    template< size_t n, typename Function, typename Iterator >
    auto 
    operator()( Datum< size_t, n >, Function&& function, Iterator first, Iterator last )
    {
      return exe<n>( forward<Function>( function ), first, last );
    }

    
    template< size_t n, typename Function, typename Iterator >
    static auto
    exe( Function&& function, Iterator it )
    {
      return aux( gen_Idx<n>(), forward<Function>( function ), it );
    }


    
    template< size_t n, typename Function, typename Iterator >
    static auto
    exe( Function&& function, Iterator first, Iterator last )
    {

      if( distance( first, last ) < n )
      {
	throw std::range_error(
	  "The size of the input range for a multiple value call is insufficient "
	  "for the specified arity." );	
      }
      return exe<n>( forward<Function>( function ), first );
    }

  private:

    template< size_t ... indices, typename Function, typename Iterator >
    static auto
    aux( Idx< indices ... >, Function&& function, Iterator it )
    {
      return forward<Function>( function )( *(it+indices) ... );
    }

  };

  constexpr static auto multiple_value_call = Multiple_value_call{};
    

  
} // end of namespace Combine



# endif // ! defined MULTIPLE_VALUE_HPP_INCLUDED_223145455877848627
