/**
   @file
   affix.hpp

   @brief
   Affix values to a range.

   @author: 
   Samuel Johnson <sabjohnso@yahoo.com>

*/

#ifndef AFFIX_HPP_INCLUDED_793856146328635151
#define AFFIX_HPP_INCLUDED_793856146328635151 1

// Combine header files

#include <combine/import.hpp>
#include <combine/multiple_value.hpp>



namespace Combine
{

  template< 
    typename InputIterator,
    typename OutputIterator,
    typename Infix
    >
  OutputIterator
  infix_copy(
    InputIterator first, 
    InputIterator last,
    OutputIterator result, 
    Infix&& infix )
  {

    if( first != last ){

      InputIterator next_to_last = last-1;
    
      while( first != next_to_last ){
	*(result++) = *first;
	++first;
	*(result++) = forward<Infix>( infix );
      }
      *(result++) = *first;
    }
    
    return result;
    
  }

  template< 
    typename InputIterator, 
    typename OutputIterator,
    typename Prefix,
    typename Suffix
    >
  OutputIterator
  circumfix_copy( 
    InputIterator first, 
    InputIterator last,
    OutputIterator result,
    Prefix&& prefix,
    Suffix&& suffix )
  {
    
    *(result++) = std::forward<Prefix>( prefix );
    result = copy( first, last, result );
    *(result++) = std::forward<Suffix>( suffix );
    
    return result;
    
  }

  template< 
    typename InputIterator, 
    typename OutputIterator,
    typename Prefix
    >
  OutputIterator
  prefix_copy( 
    InputIterator first,
    InputIterator last,
    OutputIterator result,
    Prefix&& prefix )
  {
    if( first != last )
    {
      *(result++) = std::forward<Prefix>( prefix );
      result = copy( first, last, result );
   
    }
    return result;
  }


  template< 
    typename InputIterator, 
    typename OutputIterator,
    typename Suffix
    >
  OutputIterator
  suffix_copy( 
    InputIterator first, 
    InputIterator last,
    OutputIterator result, 
    Suffix&& suffix )
  {
    if( first != last ){
      result = copy( first, last, result );
      *(result++) = std::forward<Suffix>( suffix );

    }
    return result;
  }


  

  template< 
    typename InputIterator, 
    typename OutputIterator,
    typename Prefix,
    typename Infix,
    typename Suffix
    >
  OutputIterator
  affix_copy( 
    InputIterator first, 
    InputIterator last,
    OutputIterator result,
    Prefix&& prefix,
    Infix&& delimeter,
    Suffix&& suffix )
  {
    
    *(result++) = std::forward<Prefix>( prefix );
    result = infix_copy( first, last, result, std::forward<Infix>( delimeter ));
    *(result++) = std::forward<Suffix>( suffix );
    return result;
  }














  template<
    typename InputIterator,
    typename OutputIterator,
    typename Function,
    typename InfixFunction
    >
  OutputIterator
  infix_transform(
    InputIterator first, 
    InputIterator last,
    OutputIterator result,
    Function&& f,
    InfixFunction&& infix )
    

  {
    if( first != last ){
      InputIterator next = first;
      ++next;
      while( next != last ){
	*(result++) = forward<Function>( f )( *( first++ ));
	next++;
	*(result++) = forward<InfixFunction>( infix )();
      }
      *(result++) = forward<Function>( f )( *( first ));
    }
    return result;
  }


  

  template< 
    typename InputIterator, 
    typename OutputIterator,
    typename PrefixFunction,
    typename Function,
    typename SuffixFunction
    >
  OutputIterator
  circumfix_transform( 
    InputIterator first, 
    InputIterator last,
    OutputIterator result,
    PrefixFunction&& prefix,
    Function&& function,
    SuffixFunction&& suffix )
  {
    *(result++) = forward<PrefixFunction>( prefix )();
    result = transform( first, last, result, forward<Function>( function ));
    *(result++) = forward<SuffixFunction>( suffix )();
    return result;
  }
  
  
  template< 
    typename InputIterator,
    typename OutputIterator,
    typename PrefixFunction,
    typename Function
    >
  OutputIterator
  prefix_transform( 
    InputIterator first,
    InputIterator last,
    OutputIterator result,
    PrefixFunction&& prefix,
    Function&& function)
  {
    if( first != last )
    {
      *(result++) = forward<PrefixFunction>( prefix )();
      result = transform( first, last, result, forward<Function>( function ));
    }
    return result;
  }


  template< 
    typename InputIterator, 
    typename OutputIterator,
    typename Function,
    typename SuffixFunction
    >
  OutputIterator
  suffix_transform( 
    InputIterator first, 
    InputIterator last,
    OutputIterator result,
    Function&& function,
    SuffixFunction&& suffix )
  {
    if( first != last ){
      result = transform( first, last, result, forward<Function>( function ));
      *(result++) = forward<SuffixFunction>( suffix )();
    }
    return result;
  }


  



  /** An overload of the affix_transform function where elements are copied from the range [first, last)
      into th range starting at result. 
  
      @return
      An iterator to the terminating position of the output range.
  */
  template<

    /** The type of iterator specifying the input range. */
    typename InputIterator,

    /** The type of iterator specifying the output range. */
    typename OutputIterator
    
    >
  OutputIterator
  affix_transform(

    /** An iterator to the beginning of the input range. */
    InputIterator first,

    /** An iterator to the terminating position of the input range. */
    InputIterator last,

    /** An iterator to the beginning position of the input range. */
    OutputIterator result )
  {
    
    // Just use the copy function imported from the standard library.
    return copy( first, last, result );
  }


  /** An overload of the affix_transform where the elements in the output range are assigned
      transformed values from the input range.

      @return
      An iterator to the terminating position of the output range.

  */
  template<

    /** The type of iterator specifying the input range. */
    typename InputIterator,

    /** The type of iterator specifying the output range. */
    typename OutputIterator,

    /** The unary function type. */
    typename UnaryFunction
    
    >
  OutputIterator
  affix_transform(

    /** An iterator to the beginning of the input range. */
    InputIterator first,

    /** An iterator to the terminating position of the input range. */
    InputIterator last,

    /** An iterator to the beginning position of the input range. */
    OutputIterator result,

    /** An unary function. */
    UnaryFunction&& function )
  {
    
    // Just use the copy function imported from the standard library.
    return transform( first, last, result, forward<UnaryFunction>( function ));
  }


  /** An overload of the affix_transform where the first element in the output range is generated with
      a nullary prefix function and the remaining elements are trasformed from the elements in the input range.

      @return
      An iterator to the terminating position of the output range.

  */
  template<

    /** The type of iterator specifying the input range. */
    typename InputIterator,

    /** The type of iterator specifying the output range. */
    typename OutputIterator,


    /** The nullary prefix function type. */
    typename NullaryPrefix,

    /** The unary function type. */
    typename UnaryFunction
    
    >
  OutputIterator
  affix_transform(

    /** An iterator to the beginning of the input range. */
    InputIterator first,

    /** An iterator to the terminating position of the input range. */
    InputIterator last,

    /** An iterator to the beginning position of the input range. */
    OutputIterator result,

    /** A nullary prefix function. */
    NullaryPrefix&& nullary_prefix,

    /** An unary function. */
    UnaryFunction&& function )
  {

    return prefix_transform( 
      first, last, result, 
      forward<NullaryPrefix>( nullary_prefix ), 
      forward<UnaryFunction>( function ));
  }


  /** An overload of the affix_transform where the first element in the output range is generated with
      a nullary prefix function and the remaining elements are trasformed from the elements in the input range and
      a value generated from the nullary suffix function.

      @return
      An iterator to the terminating position of the output range.

  */
  template<

    /** The type of iterator specifying the input range. */
    typename InputIterator,

    /** The type of iterator specifying the output range. */
    typename OutputIterator,


    /** The nullary prefix function type. */
    typename NullaryPrefix,

    /** The unary function type. */
    typename UnaryFunction,

    /** The nullary suffix function type. */
    typename NullarySuffix
    
    >
  OutputIterator
  affix_transform(

    /** An iterator to the beginning of the input range. */
    InputIterator first,

    /** An iterator to the terminating position of the input range. */
    InputIterator last,

    /** An iterator to the beginning position of the input range. */
    OutputIterator result,

    /** A nullary prefix function. */
    NullaryPrefix&& nullary_prefix,

    /** An unary function. */
    UnaryFunction&& function ,

    /** A nullary suffix function. */
    NullarySuffix&& nullary_suffix )
  {

    return circumfix_transform( 
      first, last, result, 
      forward<NullaryPrefix>( nullary_prefix ), 
      forward<UnaryFunction>( function ),
      forward<NullarySuffix>( nullary_suffix ));
  }


  
  /** An overload of the affix_transform where the first element in the output range is generated with
      a nullary prefix function and the remaining elements are trasformed from the elements in the input range and
      a value generated from the nullary suffix function.

      @return
      An iterator to the terminating position of the output range.

  */
  template<

    /** The type of iterator specifying the input range. */
    typename InputIterator,

    /** The type of iterator specifying the output range. */
    typename OutputIterator,


    /** The nullary prefix function type. */
    typename NullaryPrefix,

    /** The unary function type. */
    typename UnaryFunction,

    /** The nullary infix function type. */
    typename NullaryInfix,

    /** The nullary suffix function type. */
    typename NullarySuffix
    
    >
  OutputIterator
  affix_transform(

    /** An iterator to the beginning of the input range. */
    InputIterator first,

    /** An iterator to the terminating position of the input range. */
    InputIterator last,

    /** An iterator to the beginning position of the input range. */
    OutputIterator result,

    /** A nullary prefix function. */
    NullaryPrefix&& nullary_prefix,

    /** An unary function. */
    UnaryFunction&& function,

    /** A nullary infix function. */
    NullaryInfix&& nullary_infix,

    /** A nullary suffix function. */
    NullarySuffix&& nullary_suffix )
  {
    
    *(result++) = std::forward<NullaryPrefix>( nullary_prefix )();
    result = infix_transform( 
      first, last, result, 
      forward<UnaryFunction>( function ), 
      forward<NullaryInfix>( nullary_infix ));
    
    *(result++) = std::forward<NullarySuffix>( nullary_suffix )();
    
    return result;
    
  }




  /** An overload of the affix_transform where the elements in the output range are assigned
      transformed values from the input range.

      @return
      An iterator to the terminating position of the output range.

  */
  template<

    /** The arity of the transform operator. */
    size_t operator_arity,

    /** The type of iterator specifying the input range. */
    typename InputIterator,

    /** The type of iterator specifying the output range. */
    typename OutputIterator,

    /** The transformation function type. */
    typename NAryOperator
    
    >
  OutputIterator
  affix_transform(

    /** An iterator to the beginning of the input range. */
    InputIterator first,

    /** An iterator to the terminating position of the input range. */
    InputIterator last,

    /** An iterator to the beginning position of the input range. */
    OutputIterator result,

    /** An unary function. */
    NAryOperator&& nary_operator )
  {
    static_assert( 
      operator_arity > 0,
      "The function affix_transform does "
      "not accept a nullary operator." );

    using signed_size = typename make_signed<size_t>::type;
		   
    if( distance( first, last ) >= signed_size( operator_arity ))
    {
      auto terminator = last+1-operator_arity;
      while( first != terminator )
      {
	*(result++) = Multiple_value_call::exe<operator_arity>( forward<NAryOperator>( nary_operator ), first++ );
      }
    }
    
    return result;
  }


    /** An overload of the affix_transform where the elements in the output range are assigned
      transformed values from the input range.

      @return
      An iterator to the terminating position of the output range.

  */
  template<

    /** The arity of the prefix operator. */
    size_t prefix_arity,

    /** The arity of the transform operator. */
    size_t operator_arity,

    /** The type of iterator specifying the input range. */
    typename InputIterator,

    /** The type of iterator specifying the output range. */
    typename OutputIterator,

    /** The n-ary prefix operator type. */
    typename NAryPrefix,

    /** The transformation function type. */
    typename NAryOperator
    
    >
  OutputIterator
  prefix_transform(

    /** An iterator to the beginning of the input range. */
    InputIterator first,

    /** An iterator to the terminating position of the input range. */
    InputIterator last,

    /** An iterator to the beginning position of the input range. */
    OutputIterator result,

    /** An n-ary prefix function. */
    NAryPrefix&& nary_prefix,

    /** An n-ary function. */
    NAryOperator&& nary_operator )
  {
    static_assert( 
      operator_arity > 0,
      "The function affix_transform does "
      "not accept a nullary operator." );
    using signed_size = typename make_signed<size_t>::type;
    
    if(( distance( first, last ) > signed_size( prefix_arity ))
       && ( distance( first, last ) > signed_size( operator_arity )))
    {
      *(result++) = Multiple_value_call::exe<prefix_arity>( forward<NAryPrefix>( nary_prefix ), first );
      result = affix_transform<operator_arity>( first, last, result, forward<NAryOperator>( nary_operator ));
    }
    return result;
  }


  /** UNDOCUMENTED

      @return
      An iterator to the terminating position of the output range.

  */
  template<

    /** The arity of the prefix operator. */
    size_t prefix_arity,

    /** The arity of the transform operator. */
    size_t operator_arity,

    /** The type of iterator specifying the input range. */
    typename InputIterator,

    /** The type of iterator specifying the output range. */
    typename OutputIterator,

    /** The n-ary prefix operator type. */
    typename NAryPrefix,

    /** The transformation function type. */
    typename NAryOperator
    
    >
  OutputIterator
  affix_transform(

    /** An iterator to the beginning of the input range. */
    InputIterator first,

    /** An iterator to the terminating position of the input range. */
    InputIterator last,

    /** An iterator to the beginning position of the input range. */
    OutputIterator result,

    /** An n-ary prefix function. */
    NAryPrefix&& nary_prefix,

    /** An n-ary function. */
    NAryOperator&& nary_operator )
  {
    static_assert( 
      operator_arity > 0,
      "The function affix_transform does "
      "not accept a nullary operator." );
    
    return prefix_transform<prefix_arity, operator_arity>( 
      first, last, result,
      forward<NAryPrefix>( nary_prefix ),
      forward<NAryOperator>( nary_operator ));
  }









  
  /** UNDOCUMENTED

      @return
      An iterator to the terminating position of the output range.

  */
  template<

    /** The arity of the prefix operator. */
    size_t prefix_arity,

    /** The arity of the transform operator. */
    size_t operator_arity,

    /** The arity of the suffix operator. */
    size_t suffix_arity,

    /** The type of iterator specifying the input range. */
    typename InputIterator,

    /** The type of iterator specifying the output range. */
    typename OutputIterator,

    /** The n-ary prefix operator type. */
    typename NAryPrefix,

    /** The transformation function type. */
    typename NAryOperator,

    /** The n-ary suffix operator type. */
    typename NArySuffix
    
    >
  OutputIterator
  circumfix_transform(

    /** An iterator to the beginning of the input range. */
    InputIterator first,

    /** An iterator to the terminating position of the input range. */
    InputIterator last,

    /** An iterator to the beginning position of the input range. */
    OutputIterator result,

    /** An n-ary prefix function. */
    NAryPrefix&& nary_prefix,

    /** An n-ary function. */
    NAryOperator&& nary_operator,

    /** An n-ary suffix function. */
    NArySuffix&& nary_suffix )
  {
    static_assert(
      operator_arity > 0,
      "The function affix_transform does "
      "not accept a nullary operator." );

    using signed_size = typename make_signed<size_t>::type;
    
    if(( distance( first, last ) >= signed_size( prefix_arity )) 
       && ( distance( first, last ) >= signed_size( operator_arity ))
       && ( distance( first, last ) >= signed_size( suffix_arity )))
    {
      result = prefix_transform<prefix_arity,operator_arity>(
	first, last, result, 
	forward<NAryPrefix>( nary_prefix ),
	forward<NAryOperator>( nary_operator ));
      
      *(result++) = Multiple_value_call::exe<suffix_arity>( forward<NArySuffix>( nary_suffix ), last-suffix_arity );	
    }
    return result;
  }


    /** UNDOCUMENTED

      @return
      An iterator to the terminating position of the output range.

  */
  template<

    /** The arity of the prefix operator. */
    size_t prefix_arity,

    /** The arity of the transform operator. */
    size_t operator_arity,

    /** The arity of the suffix operator. */
    size_t suffix_arity,

    /** The type of iterator specifying the input range. */
    typename InputIterator,

    /** The type of iterator specifying the output range. */
    typename OutputIterator,

    /** The n-ary prefix operator type. */
    typename NAryPrefix,

    /** The transformation function type. */
    typename NAryOperator,

    /** The n-ary suffix operator type. */
    typename NArySuffix
    
    >
  OutputIterator
  affix_transform(

    /** An iterator to the beginning of the input range. */
    InputIterator first,

    /** An iterator to the terminating position of the input range. */
    InputIterator last,

    /** An iterator to the beginning position of the input range. */
    OutputIterator result,

    /** An n-ary prefix function. */
    NAryPrefix&& nary_prefix,

    /** An n-ary function. */
    NAryOperator&& nary_operator,

    /** An n-ary suffix function. */
    NArySuffix&& nary_suffix )
  {
    static_assert(
      operator_arity > 0,
      "The function affix_transform does "
      "not accept a nullary operator." );

    return circumfix_transform<prefix_arity, operator_arity, suffix_arity>(
      first, last, result,
      forward<NAryPrefix>( nary_prefix ),
      forward<NAryOperator>( nary_operator ),
      forward<NArySuffix>( nary_suffix ));
  }



  

} // end of namespace combine

#endif // ! defined AFFIX_HPP_INCLUDED_793856146328635151
