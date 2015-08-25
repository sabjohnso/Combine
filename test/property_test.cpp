/**
   @file
   test/property_test.cpp

   @brief
   UNDOCUMENTED

   @copyright	
   2015 Samuel B. Johnson

   @author: 
   Samuel Johnson <sabjohnso@yahoo.com>

*/


// Standard header files
#include <array>

// Combine header files

#include <combine/base_types.hpp>
#include <combine/make.hpp>
#include <combine/macro_tools.hpp>
#include <combine/property.hpp>


using namespace Combine;


template< typename T = float64, size_t n = 2, template< typename, size_t > class Array = std::array >
struct GeoObj_I
{
  Property< Array<T,n> > Centroid;
};



template< typename T = double, size_t n = 2, template< typename, size_t > class Array = std::array >
struct Circle_I : public GeoObj_I< T, n, Array >
{
  using base_type = GeoObj_I< T, n, Array >;
  
  Property<T> Radius;
  template< typename C, typename R >
  Circle_I( C&& c, R&& r )
    : base_type{ std::forward<C>( c )} 
    , Radius( std::forward<R>( r ))
  {}
  
};


template< typename T = double, size_t n = 2, template< typename, size_t > class Array = std::array >
class Circle_D
{
public:
  using circle_type = Circle_I<T,n,Array>;
  
  template< typename C, typename R >
  Circle_D( C&& c, R&& r )
    : centroid( std::forward<C>( c ))
    , radius( std::forward<R>( r ))
  {}

  
  circle_type operator *() { return  circle_type( *this ); }

  operator circle_type()
  {
    return circle_type{ make_property( this->centroid ), make_property( this->radius )};
  }



  
  
private:
  
  Array< T, n > centroid;
  T radius;
  
  
};


template< typename T, size_t n, template< typename, size_t > class Array, typename Tr >
auto
make_circle( Array<T,n>&& c, Tr&& r )
{
  using value_type   = typename std::decay<T>::type;
  using value_type_r = typename std::decay<T>::type;
  COMBINE_STATIC_ASSERT_TRUE( is_same< value_type, value_type_r>::value );
  
  return Circle_D< value_type, n, Array >( std::forward< Array<T,n> >( c ), std::forward<Tr>( r ));
}



template< typename T, size_t n, template< typename, size_t > class Array >
auto
circle_radius( Circle_I<T,n,Array>&& c )
{
  return *std::forward< Circle_I<T,n,Array> >( c ).Radius;
}

template< typename T, size_t n, template< typename, size_t > class Array >
auto
circle_centroid( Circle_I<T,n,Array>&& c )
{
  return *std::forward<Circle_I<T,n,Array> >( c ).Centroid;
}



template< typename T >
decltype( auto ) _( T&& arg ){ return *std::forward<T>( arg ); }


int
main( int argc, char** argv )
{

  {
    constexpr auto make_array = MakeXn<std::array>{};
    auto origin = make_array( 0.0, 0.0 );
    auto Origin = make_property( origin );

    COMBINE_TEST_EQUAL( std::get<0>( *Origin ), 0.0 );
    COMBINE_TEST_EQUAL( std::get<1>( *Origin ), 0.0 );

    Origin = make_array( 1.0, 2.0 );

    COMBINE_TEST_EQUAL( std::get<0>( *Origin ), 1.0 );
    COMBINE_TEST_EQUAL( std::get<1>( *Origin ), 2.0 );
  }


  {
    auto make_array = MakeXn<std::array>{};
    auto c = make_circle( make_array( 0.0, 0.0 ), 1.0 );
    COMBINE_TEST_EQUAL( (*c).Radius, 1.0 );
    COMBINE_TEST_EQUAL( std::get<0>( *(*c).Centroid ), 0.0 );
    COMBINE_TEST_EQUAL( std::get<1>( *(*c).Centroid ), 0.0 );

    COMBINE_TEST_EQUAL( circle_radius( *c ), 1.0 );
    COMBINE_TEST_EQUAL( std::get<0>( circle_centroid( *c )), 0.0 );
    COMBINE_TEST_EQUAL( std::get<1>( circle_centroid( *c )), 0.0 );
    
  } 


  
  
  
  return 0;

  
};

