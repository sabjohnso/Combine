/**
 */
#ifndef BASE_TYPES_HPP_INCLUDED_591562540968500389
#define BASE_TYPES_HPP_INCLUDED_591562540968500389 1

#include <combine/macro_tools.hpp>
#include <combine/type.hpp>
#include <combine/select_with_sizeof.hpp>



namespace Combine
{

  using Integer_types = Types< short, int, long, long long >;
  using Unsigned_integer_types = Types< unsigned short, unsigned int, unsigned long, unsigned long long >;
  using Floating_point_types  = Types< float, double, long double >;

  using int16 = typename Select_with_sizeof< 2, Integer_types >::type;
  
  COMBINE_STATIC_ASSERT_EQUAL( sizeof( int16 ), 2 );
  COMBINE_STATIC_ASSERT_TRUE( std::is_fundamental< int16 >::value );
  COMBINE_STATIC_ASSERT_TRUE( std::is_arithmetic< int16 >::value );
  COMBINE_STATIC_ASSERT_TRUE( std::is_signed< int16 >::value );
  COMBINE_STATIC_ASSERT_TRUE( std::is_integral< int16 >::value );

    
  using int32 = typename Select_with_sizeof< 4, Integer_types >::type;
  
  COMBINE_STATIC_ASSERT_EQUAL( sizeof( int32 ), 4 );
  COMBINE_STATIC_ASSERT_TRUE( std::is_fundamental< int32 >::value );
  COMBINE_STATIC_ASSERT_TRUE( std::is_arithmetic< int32 >::value );
  COMBINE_STATIC_ASSERT_TRUE( std::is_signed< int32 >::value );
  COMBINE_STATIC_ASSERT_TRUE( std::is_integral< int32 >::value );

  
  using int64 = typename Select_with_sizeof< 8, Integer_types >::type;

  COMBINE_STATIC_ASSERT_EQUAL( sizeof( int64 ), 8 );
  COMBINE_STATIC_ASSERT_TRUE( std::is_fundamental< int64 >::value );
  COMBINE_STATIC_ASSERT_TRUE( std::is_arithmetic< int64 >::value );
  COMBINE_STATIC_ASSERT_TRUE( std::is_signed< int64 >::value );
  COMBINE_STATIC_ASSERT_TRUE( std::is_integral< int64 >::value ); 



  using uint16 = typename Select_with_sizeof< 2, Unsigned_integer_types >::type;

  COMBINE_STATIC_ASSERT_EQUAL( sizeof( uint16 ), 2 );
  COMBINE_STATIC_ASSERT_TRUE( std::is_fundamental< uint16 >::value );
  COMBINE_STATIC_ASSERT_TRUE( std::is_arithmetic< uint16 >::value );
  COMBINE_STATIC_ASSERT_TRUE( std::is_unsigned< uint16 >::value );
  COMBINE_STATIC_ASSERT_TRUE( std::is_integral< uint16 >::value );
  COMBINE_STATIC_ASSERT_TRUE( std::is_same< int16, std::make_signed< uint16 >::type >::value );

  using uint32 = typename Select_with_sizeof< 4, Unsigned_integer_types >::type;

  COMBINE_STATIC_ASSERT_EQUAL( sizeof( uint32 ), 4 );
  COMBINE_STATIC_ASSERT_TRUE( std::is_fundamental< uint32 >::value );
  COMBINE_STATIC_ASSERT_TRUE( std::is_arithmetic< uint32 >::value );
  COMBINE_STATIC_ASSERT_TRUE( std::is_unsigned< uint32 >::value );
  COMBINE_STATIC_ASSERT_TRUE( std::is_integral< uint32 >::value );
  COMBINE_STATIC_ASSERT_TRUE( std::is_same< int32, std::make_signed< uint32 >::type >::value );

  
  
  using uint64 = typename Select_with_sizeof< 8, Unsigned_integer_types >::type;
  
  COMBINE_STATIC_ASSERT_EQUAL( sizeof( uint64 ), 8 );
  COMBINE_STATIC_ASSERT_TRUE( std::is_fundamental< uint64 >::value );
  COMBINE_STATIC_ASSERT_TRUE( std::is_arithmetic< uint64 >::value );
  COMBINE_STATIC_ASSERT_TRUE( std::is_unsigned< uint64 >::value );
  COMBINE_STATIC_ASSERT_TRUE( std::is_integral< uint64 >::value );
  COMBINE_STATIC_ASSERT_TRUE( std::is_same< int64, std::make_signed< uint64 >::type >::value );
  

  using float32 = typename Select_with_sizeof< 4, Floating_point_types >::type;

  COMBINE_STATIC_ASSERT_EQUAL( sizeof( float32 ), 4 );
  COMBINE_STATIC_ASSERT_TRUE( std::is_fundamental< float32 >::value );
  COMBINE_STATIC_ASSERT_TRUE( std::is_arithmetic< float32 >::value );
  COMBINE_STATIC_ASSERT_TRUE( std::is_floating_point< float32 >::value );

  
  using float64 = typename Select_with_sizeof< 8, Floating_point_types>::type;

  COMBINE_STATIC_ASSERT_EQUAL( sizeof( float64 ), 8 );
  COMBINE_STATIC_ASSERT_TRUE( std::is_fundamental< float64 >::value );
  COMBINE_STATIC_ASSERT_TRUE( std::is_arithmetic< float64 >::value );
  COMBINE_STATIC_ASSERT_TRUE( std::is_floating_point<  float64 >:: value );

  
  using float128 = typename Select_with_sizeof< 16, Floating_point_types >::type;

  COMBINE_STATIC_ASSERT_EQUAL( sizeof( float128 ), 16 );
  COMBINE_STATIC_ASSERT_TRUE( std::is_fundamental< float128 >::value );
  COMBINE_STATIC_ASSERT_TRUE( std::is_arithmetic< float128 >::value );
  COMBINE_STATIC_ASSERT_TRUE( std::is_floating_point< float128 >::value );


  
} // end of namespace Combine



#endif // ! defined BASE_TYPES_HPP_INCLUDED_591562540968500389
