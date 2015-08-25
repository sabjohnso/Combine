/**
   @file
   property.hpp

   @brief
   UNDOCUMENTED

   @copyright	
   2015 Samuel B. Johnson

   @author: 
   Samuel Johnson <sabjohnso@yahoo.com>

*/
#ifndef PROPERTY_HPP_INCLUDED_1135359298046836928
#define PROPERTY_HPP_INCLUDED_1135359298046836928


// Combine header files

#include <combine/import.hpp>
#include <combine/nil.hpp>


namespace Combine
{




  

  template< typename T, class Function = function<const T&()> >
  struct Getter : public Function
  {
    static_assert( std::is_function<Function()>::value, "Invalid template parameter: Function() is not a function." );
    static_assert( std::is_same< typename std::result_of<Function()>::type, const T& >::value,
		   "Invalid template parameter: Function() does not return const T&." );
    using value_type = T;
    using function_type = Function;
    using function_type::function_type;
  };
  

  template< typename T >
  auto
  make_getter( T&& x )
  {
    using value_type = typename std::decay<T>::type;
    return Getter<value_type>( [&x]() mutable -> const value_type& { return x; });
  }



  
  template< typename T, class Function = std::function<T&(T&&)> >
  struct Setter : public Function
  {
    static_assert( std::is_function<Function(T&&)>::value, "Invalid template parameter: Function() is not a function." );
    static_assert( std::is_same< typename std::result_of<Function(T&&)>::type, T& >::value,
		   "Invalid template parameter: Function() does not return const T&." );
    using value_type = T;
    using function_type = Function;
    using function_type::function_type;
  };



  template< typename T >
  auto
  make_setter( T&& x )
  {
    using value_type = typename std::decay<T>::type;
    return Setter<value_type>( [&x]( value_type&& arg ) mutable -> value_type&
      {
	x = std::forward<value_type>( arg );
	return x;
      });
  }



  
  enum class access_flag{ READ_WRITE, READ_ONLY };
  template< 
    typename T, 
    access_flag flag = access_flag::READ_WRITE, 
    template< typename ... > class G = Getter, 
    template< typename ... > class S = Setter
    >
  class Property
  {
  public:
  
    using getter_type = G<T>;
    using setter_type = S<T>;

    Property( getter_type&& getter, setter_type&& setter )
      : get( std::forward<getter_type>( getter ))
      , set( std::forward<setter_type>( setter ))
    {}
	    

    Property
    operator =( T&& arg )
    {
      set( std::forward<T>( arg ));
      return *this; 
    }

    const T& operator*() { return static_cast<const T&>( *this ); }
    operator const T&() const { return get(); }
  private:
    getter_type get;
    setter_type set;
  };


  template< 
    typename T,
    template< typename ... > class G 
    >
  class Property< T, access_flag::READ_ONLY, G, NilT >
  {
  public:
  
    using getter_type = G<T>;

    Property( getter_type&& getter )
      : get( std::forward<getter_type>( getter ))
    {}

    operator const T&() const
    {
      return get();
    }
  private:
    getter_type get;
  };

  template< typename T >
  using ReadProperty = Property< T, access_flag::READ_ONLY, Getter, NilT >;



  template< typename T >
  auto
  make_property( T&& x )
  {
    using value_type = typename decay<T>::type;
    return Property<value_type>( make_getter( forward<T>( x )), make_setter( forward<T>( x )));
  }


};



#endif // PROPERTY_HPP_INCLUDED_1135359298046836928
