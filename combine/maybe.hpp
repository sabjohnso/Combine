/**
   
   @file
   maybe.hpp

   @brief
   Maybe a type.

   @author: 
   Samuel Johnson <sabjohnso@yahoo.com>

*/
#ifndef MAYBE_HPP_INCLUDED_1466186034375873898
#define MAYBE_HPP_INCLUDED_1466186034375873898 1


// Combine header files

#include <combine/import.hpp>
#include <combine/nil.hpp>
#include <combine/either.hpp>

namespace Combine
{

  template< typename X >
  class Maybe : private Either<X,Nil>
  {

  public:

    using value_type = X;
    using base_type = Either<value_type,Nil>;

    Maybe( base_type&& arg )
      : base_type( forward<base_type>( arg ))
    {}

    Maybe( const base_type& arg )
      : base_type( arg )
    {}

    Maybe( const Maybe& arg )
      : base_type( static_cast<const base_type&>( arg ))
    {}

    Maybe() : base_type( base_type::make_second())
    {}

    
    template< typename ... Ys >
    static 
    Maybe just( Ys&& ... ys )
    {
      return base_type::make_first( forward<Ys>( ys ) ... );
    }

    static
    Maybe 
    nothing()
    {
      return Maybe( base_type::make_second());
    }

    Maybe&
    operator =( const Maybe& arg )
    {
      static_cast<base_type&>( *this ) = static_cast<const base_type&>( arg );
      return *this;
    }
    
    Maybe&
    operator =( Maybe&& arg )
    {
      static_cast<base_type&>( *this ) = std::move( static_cast<base_type&>( arg ));
      return *this;
    }

    template< typename  Y >
    Maybe&
    operator =( Y&& y )
    {
      static_cast<base_type&>( *this ) = base_type::make_first( std::forward<Y>( y ));
      return *this;
    }
    
    template< typename  Y >
    Maybe&
    operator =( const Y& y )
    {
      static_cast<base_type&>( *this ) = base_type::make_first( std::forward<Y>( y ));
      return *this;
    }

    explicit operator value_type&()
    {
      return static_cast<value_type&>( static_cast<base_type&>( *this ));
    }

    explicit operator const value_type&() const
    {
      return static_cast<const value_type&>( static_cast<const base_type&>( *this ));
    }

    bool
    is() const
    {
      return base_type::is_first();
    }

    value_type&
    operator *()
    {
      return static_cast<value_type&>( *this );
    }

    
    const value_type&
    operator *() const
    {
      return static_cast<const value_type&>( *this );
    }
  };
  
  
} // end of namespace Combine

namespace
{
  
  template< typename Stream, typename X >
  Stream&
  operator <<( Stream& s, const Combine::Maybe<X>& x )
  {
    if( x.is())
    {
      s << *x;
    }
    {
      s << "Nil";
    }
    return s;
  }
}


#endif // ! defined MAYBE_HPP_INCLUDED_1466186034375873898
