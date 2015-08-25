/**
   
   @file
   either.hpp

   @brief
   Either of two types.

   @author: 
   Samuel Johnson <sabjohnso@yahoo.com>

*/

#ifndef EITHER_HPP_INCLUDED_1647005271982147475
#define EITHER_HPP_INCLUDED_1647005271982147475 1


#include <combine/import.hpp>


namespace Combine
{

  
  template< typename First, typename Second >
  class Either
  {
  public:    
    struct first_tag{};
    struct second_tag{};

    using first_type = First;
    using second_type = Second;

    template< typename ... Xs >
    static Either
    make_first( Xs&& ... xs )
    {
      return Either( first_tag{}, forward< Xs >( xs ) ... );
    }


    Either() : first_flag( true ), first()
    {}

    ~Either()
    {}



    template< typename ... Xs >
    static Either
    make_second( Xs&& ... xs )
    {
      return Either( second_tag{}, forward< Xs >( xs ) ... );
    }

    template< typename ... Xs >
    Either( first_tag, Xs&& ... xs ) 
      : first_flag( true )
      , first( std::forward<Xs>( xs ) ... )
    {}
    
    template< typename ... Xs >
    Either( second_tag, Xs&& ... xs ) 
      : first_flag( false )
      , second( std::forward<Xs>( xs ) ... )
    {}

    Either( const Either& arg )
      : first_flag( arg.is_first())
    {
      if( is_first())
      {
	first = static_cast<const first_type&>( arg );
      }
      else
      {
	second = static_cast<const second_type&>( arg );
      }
    }




    Either&
    operator =( const Either& arg )
    {
      if( first_flag )
      {
	if( arg.first_flag )
	{
	  first = arg.first;
	}
	else
	{
	  first_flag = false;
	  new( &second ) second_type( arg.second );
	}
      }
      else
      {
	if( arg.first_flag )
	{
	  first_flag = true;
	  new( &first ) first_type( arg.first );
	}
	else
	{
	  second = arg.second;
	}
      }
      
      return* this;
    }


    Either&
    operator =( Either&& arg )
    {
      if( first_flag )
      {
	if( arg.first_flag )
	{
	  first = std::move( arg.first );
	}
	else
	{
	  first_flag = false;
	  new( &second ) second_type( std::move( std::forward<Either>( arg ).second ));
	}
      }
      else
      {
	if( arg.first_flag )
	{
	  first_flag = true;
	  new( &first ) first_type( std::move( std::forward<Either>( arg ).first ));
	}
	else
	{
	  second = arg.second;
	}
      }
      
      return* this;
    }

    

    bool
    is_first() const
    {
      return first_flag;
    }

    bool
    is_second () const
    {
      return ! is_first();
    }


    explicit operator first_type&()
    {
      validate_first();
      return first;
    }

    
    explicit operator const first_type&() const
    {
      validate_first();
      return first;
    }

 
    explicit operator second_type&()
    {
      validate_second();
      return second;
    }

    
    explicit operator const second_type&() const
    {
      validate_second();
      return second;
    }

  private:

    void
    validate_first() const
    {
      if( ! is_first())
      {
	throw logic_error( "Invalid access of first_type" );
      }
    }

    
    void
    validate_second() const
    {
      if( ! is_second())
      {
	throw logic_error( "Invalid access of second_type" );
      }
    }

    bool first_flag;
    
    union
    {
      First first;
      Second second;
    };
    

  };



  
} // end of namespace Combine







namespace 
{

  template< typename Stream, typename First, typename Second >
  Stream&
  operator <<( Stream& s, const Combine::Either<First,Second>& x )
  {
    if( x.is_first())
    {
      s << static_cast<const First&>( x );
    }
    else
    {
      s << static_cast<const Second&>( x );
    }
    return s;
  }

} // end of anonymous namespace 

#endif // ! defined EITHER_HPP_INCLUDED_1647005271982147475
