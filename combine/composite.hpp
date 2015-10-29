/**
   @file
   composite.hpp

   @brief
   UNDOCUMENTED

   @author: 
   Samuel Johnson <sabjohnso@yahoo.com>
*/


#ifndef COMPOSITE_HPP_INCLUDED
#define COMPOSITE_HPP_INCLUDED

//
// ... Combine header files
//
#include <combine/import.hpp>

namespace Combine
{

  template< 
    typename CompositeKernel,
    template< typename  ... > class C,
    typename ... Fs 
    >
  class AbstractComposite;

  
  template< 
    typename  Kernel,
    template< typename ... > class C,
    typename F,
    typename G
    >
  class AbstractComposite< Kernel, C, F, G >
    : public C< typename decay< F >::type , typename decay<G>::type>
  {
  public:
    using data_type = C<F,G>;

    template< typename ... Gs >
    constexpr
    AbstractComposite( Gs&& ... gs ) : data_type( forward<Gs>( gs ) ... ) {}

    template< typename ... Gs >
    constexpr
    AbstractComposite( const Gs& ... gs ) : data_type( gs ... ) {}

    template< typename ... Xs >
    constexpr auto 
    operator()( Xs&& ... xs ) const
    {
      return Kernel{}( data_type::first, data_type::second, forward<Xs>( xs ) ... );
    }

    template< typename ... Xs >
    constexpr auto 
    operator()( const Xs& ... xs ) const
    {
      return Kernel{}( data_type::first, data_type::second, xs ... );
    }
   
    
  };

  template<
    typename Kernel,
    template< typename ... > class C,
    typename F0,
    typename F1,
    typename F2,
    typename ... Fs >
  class AbstractComposite< Kernel, C, F0, F1, F2, Fs ... >
    : public AbstractComposite< Kernel, C, F0, AbstractComposite< Kernel, C, F1, F2, Fs ... > >
  {
    
  public:
    
    using inner_type = AbstractComposite< Kernel, C, F1, F2, Fs ... >;
    using outer_type = AbstractComposite< Kernel, C, F0, inner_type >;

    using outer_type::operator();

    template< typename G, typename ... Gs >
    AbstractComposite( G&& g, Gs&& ... gs ) : outer_type( forward<G>( g ), inner_type( forward<Gs>( gs ) ... )) {}

    template< typename G, typename ... Gs >
    AbstractComposite( const G& g, const Gs& ... gs ) : outer_type( g, inner_type( gs  ... )) {}
    
  };


  struct SequentialKernel
  {
    template< typename F, typename G, typename ... Xs >
    constexpr auto
    operator ()( const F& f, const G& g, Xs&& ... xs )
    {
      return f( g( forward<Xs>( xs ) ... ));
    }

    template< typename F, typename G, typename ... Xs >
    constexpr auto
    operator ()( const F& f, const G& g, const Xs& ... xs )
    {
      return f( g( xs ... ));
    }
  };


  struct ParallelKernel
  {
    template< typename F, typename G, typename Xs >
    constexpr auto
    operator()( const F& f, const G& g, Xs&& xs )
    {
      return make_pair( f( get<0>( forward<Xs>( xs ))), g( get<1>( forward<Xs>( xs ))));
    }

    
    template< typename F, typename G, typename Xs >
    constexpr auto
    operator()( const F& f, const G& g, const Xs& xs )
    {
      return make_pair( f( get<0>( xs )), g( get<1>( xs )));
    }
  };

  

  struct StrangeKernel
  {
    template< typename F, typename G, typename ... Xs >
    constexpr auto
    operator ()( const F& f, const G& g, Xs&& ... xs )
    {
      return f( g( forward<Xs>( xs )) ... );
    }

    template< typename F, typename G, typename ... Xs >
    constexpr auto
    operator ()( const F& f, const G& g, const Xs& ... xs )
    {
      return f( g( xs ) ... );
    }

  };


  struct WeirdKernel
  {
    
    template< typename F, typename G, typename ... Xs >
    constexpr auto
    operator ()( const F& f, const G& g, Xs&& ... xs )
    {
      return apply( f, g( forward<Xs>( xs ) ... ));
    }

    template< typename F, typename G, typename ... Xs >
    constexpr auto
    operator ()( const F& f, const G& g, const Xs& ... xs )
    {
      return f( g( xs ) ... );
    }
    
  };
  


  template< typename ... Fs >
  using SequentialComposite = AbstractComposite< SequentialKernel, pair, Fs ... >;

  template< typename ... Fs >
  using ParallelComposite = AbstractComposite< ParallelKernel, pair, Fs ... >;

  template< typename ... Fs >
  using StrangeComposite = AbstractComposite< StrangeKernel, pair, Fs ... >;

  template< typename ... Fs >
  using WeirdComposite = AbstractComposite< WeirdKernel, pair, Fs ... >;
    
    



  
} // end of namespace Combine


#endif // COMPOSITE_HPP_INCLUDED
