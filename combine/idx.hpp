/** @file 
    combine/idx.hpp
    
    @brief 
    A header file containing definitions of struct 
    templates for building a sequence of nonnegative integer 
    values.

    @author Samuel B. Johnson <sabjohnso@yahoo.com>
*/
#ifndef IDX_HPP_INCLUDED_1819216676186183542
#define IDX_HPP_INCLUDED_1819216676186183542 1

//
// ... Standard header files
//
#include <cstddef>

//
// ... Combine header files
//
#include <combine/count.hpp>
#include <combine/datum.hpp>


namespace Combine
{

  template< size_t ... indices >
  struct Idx
  {
    constexpr static size_t size = Count_values< size_t,  indices ... >::value;
  };

  template< typename X >
  struct Is_Idx
  {
    constexpr static bool value = false;
  };

  template< size_t ... indices >
  struct Is_Idx< Idx<indices ...> >
  {
    constexpr static bool value = true;
  };
  

  template< size_t, size_t ... >
  struct Gen_Idx;
  

  template< size_t ... indices >
  struct Gen_Idx< 0, indices ... >
  {
    using type = Idx< indices ... >;
  };


  template< size_t n, size_t ... indices >
  struct Gen_Idx
    : public Gen_Idx< n-1, n-1, indices ... >
  {};


  struct Reverse_Idx
  {
    template< size_t ... indices>
    constexpr auto
    operator ()( Idx< indices ... > ) const
    {
      return aux( Idx< indices ... >{}, Idx<>{} );
    }

  private:

    template< size_t ... indices_reversed >
    constexpr auto
    aux( Idx<>, Idx< indices_reversed ... > ) const
    {
      return Idx< indices_reversed ... >{};
    }

    template< size_t index, size_t ... indices, size_t ... indices_reversed >
    constexpr auto
    aux( Idx< index, indices ... >, Idx< indices_reversed ... > ) const
    {
      return aux( Idx< indices ... >{}, 
		  Idx< index, indices_reversed ... >{} );
    }
    
  };

  template< size_t ... indices >
  constexpr auto
  reverse_Idx( Idx< indices ... > )
  {
    return Reverse_Idx{}( Idx< indices ... >{} );
  }


  template<
    size_t n,
    typename R = typename Gen_Idx< n >::type
    >
  constexpr R
  gen_Idx()
  {
    return R{};
  };


  template<
    typename ... Xs,
    typename R = typename Gen_Idx< count_types< Xs ... >() >::type
    >
  constexpr R
  gen_Idx()
  {
    return R{};
  }

  template< size_t ... indices >
  constexpr auto
  count_Idx( Idx< indices ... > )
  {
    return count_types< Datum< size_t, indices > ...  >();
  }


  template< size_t ... indices >
  constexpr auto
  count_indices()
  {
    return count_types< Datum< size_t, indices > ... >();
  }


  template< size_t ... >
  struct Sum_Idx;

  template<>
  struct Sum_Idx<>
  {
    constexpr static size_t value = 0;
  };

  template< size_t index, size_t ... indices >
  struct Sum_Idx< index, indices ... >
  {
    constexpr static size_t value = index+Sum_Idx< indices ... >::value;
  };


  template< size_t ... indices >
  constexpr auto
  sum_Idx( Idx< indices ... > )
  {
    return Sum_Idx< indices ... >::value;
  }


  template< size_t ... >
  struct Product_Idx;

  template<>
  struct Product_Idx<>
  {
    constexpr static size_t value = 1;
  };

  template< size_t index, size_t ... indices >
  struct Product_Idx< index, indices ... >
  {
    constexpr static size_t value = index*Product_Idx< indices ... >::value;
  };

  template< typename >
  struct Product_of_Idx;

  template< size_t ... indices >
  struct Product_of_Idx< Idx<indices ...> >
  {
    constexpr static size_t value = Product_Idx<indices ... >::value;
  };

  template< size_t, typename >
  struct Scale_Idx;

  template< size_t s, size_t ... indices >
  struct Scale_Idx< s, Idx< indices ... > >
  {
    using type = Idx< 2*indices ... >;
  };

  template< typename, typename, size_t ... >
  struct Add_Idx;


  template< size_t ... indices >
  struct Add_Idx< Idx<>, Idx<>, indices ... >
  {
    using type = Idx< indices ... >;
  };

  template< size_t index_x, size_t ... indices_x, size_t index_y, size_t ... indices_y, size_t ... indices_xy >
  struct Add_Idx< Idx< index_x, indices_x ... >, Idx< index_y, indices_y ... >, indices_xy ... >
    : Add_Idx< Idx<indices_x ...>, Idx<indices_y ... >, indices_xy ..., index_x+index_y >
  {};

  

  template< size_t ... indices >
  constexpr auto
  product_Idx( Idx< indices ... > )
  {
    return Product_Idx< indices ... >::value;
  }


  
  template< size_t n, size_t ... >
  struct Nth_Idx;

  template< size_t index, size_t ... indices >
  struct Nth_Idx< 0, index, indices ... >
  {
    constexpr static size_t value = index;
  };


  template< size_t n, size_t index, size_t ... indices >
  struct Nth_Idx< n, index, indices ... > : Nth_Idx< n-1, indices ... >
  {};
  
  template< size_t n, size_t ... indices >
  constexpr auto
  nth_Idx( Idx< indices ... > )
  {
    return Nth_Idx< n, indices ... >::value;
  }
  

} // end of namespace Combine

#endif // ! defined IDX_HPP_INCLUDED_1819216676186183542
