/** @file combine/meta_kanren.hpp
    
    @brief Template implementation of microKanren.

    @author Samuel B. Johnson

*/
#ifndef META_KANREN_HPP_INCLUDED_1504389316913040494
#define META_KANREN_HPP_INCLUDED_1504389316913040494 1


//
// ... Standard header files
//
#include <cstddef>
#include <type_traits>

//
// ... Combine header files
//
#include <combine/type.hpp>
#include <combine/nil.hpp>
#include <combine/cons.hpp>
#include <combine/datum.hpp>


namespace Combine
{

  namespace Meta_Kanren
  {
    
    template< template< typename ... > class >
    struct Procedure
    {};





    

    /** Mplus
     */
    template< typename, typename >
    struct Mplus;

    template< typename Y >
    struct Mplus< Nil, Y >
    {
      using type = Y;
    };

    template< template< typename ... > class F, typename Y >
    struct Mplus< Procedure< F >, Y >
    {
      template< typename ... >
      struct Local
      {
	using type = typename Mplus< Y, typename F<>::type >::type;
      };
      using type = Procedure< Local >;
    };

    template< typename X0, typename X1, typename Y >
    struct Mplus< Cons< X0, X1 >, Y >
    {
      using type = Cons< X0, typename Mplus< X1, Y >::type >;
    };

    template< typename Stream, typename X, typename Y >
    Stream&
    operator <<( Stream& s, Type< Mplus< X, Y >> )
    {
      return s << "Mplus<" << Type<X>{} << "," << Type< Y >{} << ">";
    }
    

    
    /** Unit
     */
    template< typename ... >
    struct Unit;

    template< typename X >
    struct Unit< X >
    {
      using type = Cons< X, Nil >;
    };


    template< typename Stream, typename X >
    Stream&
    operator <<( Stream& s, Type< Unit< X > > )
    {
      return s << "Unit<" << Type< X >{} << ">";
    }
    

    
    template< typename, typename  >
    struct Bind;

    template< template< typename ... > class F >
    struct Bind< Nil, Procedure< F > >
    {
      using type = Nil;
    };
    
    template< template< typename ... > class X, template< typename ... > class F >
    struct Bind< Procedure< X >, Procedure< F > >
    {
      template< typename ... >
      struct Local
      {
	using type = typename Bind< typename X<>::type, Procedure< F > >::type;
      };
      using type = Procedure< Local >;
    };

    template< typename X, typename Y, template< typename ... > class F >
    struct Bind< Cons< X, Y >, Procedure< F > >
    {
      using type = typename Mplus< typename F< X >::type, typename Bind< Y, Procedure< F > >::type >::type;
    };


    template< typename ... >
    struct And;

    template< typename X, typename ... Xs >
    struct And< Nil,  X, Xs ... >
    {
      using type = Nil;
    };

    template< typename X, typename Y, typename ... Ys >
    struct And< X, Y, Ys ... >
    {
      using type = typename And< Y, Ys ... >::type;
    };

    template< typename X >
    struct And< X >
    {
      using type = X;
    };

    template<>
    struct And< Nil >
    {
      using type = Nil;
    };


    template< typename, typename >
    struct Assp;

    template< template< typename ... > class P >
    struct Assp< Procedure< P >, Nil >
    {
      using type = Nil;
    };

    template< template< typename ... > class P, typename X1, typename X2, typename Y >
    struct Assp< Procedure< P >, Cons< Cons< X1, X2 >, Y > >
    {
      using type = typename std::conditional< ! Null< P< X1 > >::value,
					      Cons< X1, X2 >,
					      typename Assp< Procedure< P >, Y >::type >::type;
    };


        
    template< size_t i >
    struct Var
    {};

    template< typename Stream, size_t i >
    Stream&
    operator <<( Stream& s, Type< Var< i > > )
    {
      return s << "Var<" << i << ">";
    }

    

    template< typename >
    struct is_Var
    {
      constexpr static bool value = false;
    };

    template< size_t i >
    struct is_Var< Var< i > >
    {
      constexpr static bool value = true;
    };

    template< typename, typename >
    struct equal_Var;

    template< size_t i, size_t j >
    struct equal_Var< Var< i >, Var< j > >{ constexpr static bool value = false; };

    template< size_t i >
    struct equal_Var< Var< i >, Var< i > >{ constexpr static bool value = true; };


    template< typename ... >
    struct Extend_state;

    template< typename X, typename V, typename S >
    struct Extend_state< X, V, S >
    {
      using type =  Cons< Cons< X, V >, S >;
    };

    /** Walk
     */
    template< typename ... >
    struct Walk;

    template< typename U, typename S >
    struct Walk< U, S >
    {

    private:
      
      template< typename ... >
      struct Local;

      template< typename V >
      struct Local< V >
      {
	using type = typename std::conditional< equal_Var< U, V >::value, V, Nil >::type;
      };
      
      using Pr = typename And< typename std::conditional< is_Var< U >::value, U, Nil >::type,
			       typename Assp< Procedure< Local >, S >::type >::type;

      COMBINE_STATIC_ASSERT_TRUE( Consp< Pr >::value || std::is_same< Pr, Nil >::value );

      

    public:
      
      using type = typename std::conditional< ! std::is_same< Pr, Nil >::value,
					      Walk< typename Cdr< Pr >::type, S >,
					      Type< U > >::type::type;
				     
    }; // end of struct template Walk


    template< typename ... >
    struct Unify;

    template< typename U, typename V, typename S >
    struct Unify< U, V, S >
    {
      using Ux = typename Walk< U, S >::type;
      using Vx = typename Walk< V, S >::type;

      template< typename ... >
      struct Aux;

      template< size_t i >
      struct Aux< Var< i >, Var< i > >
      {
	using type = S;
      };

      template< size_t i, typename Vy >
      struct Aux< Var< i >, Vy >
      {
	using type = typename Extend_state< Var< i >, Vy, S >::type;
      };

      template< typename Uy, size_t j >
      struct Aux< Uy, Var< j > >
      {
	using type = typename Extend_state< Var< j >, Uy, S >::type;
      };

      template< typename U0, typename U1, typename V0, typename V1 >
      struct Aux< Cons< U0, U1 >, Cons< V0, V1 > >
      {
	using Sy = typename Unify< U0, V0, S >::type;
	using type = typename And< Sy, typename Unify< U1, V1, Sy >::type >::type;
      };

      template< typename Uy >
      struct Aux< Uy, Uy >
      {
	using type = S;
      };

      template< typename Uy, typename Vy >
      struct Aux< Uy, Vy >
      {
	using type = Nil;
      };

      using type = typename Aux< Ux, Vx >::type;

      
    };


    template< typename ... >
    struct Equate;

    template< typename U, typename V >
    struct Equate< U, V >
    {
      template< typename ... >
      struct Local;

      template< typename S >
      struct Local< S >
      {
	COMBINE_STATIC_ASSERT_TRUE( Consp< S >::value );
	using Sx = typename Unify< U, V, typename Car< S >::type >::type;
	using type = typename std::conditional< ! std::is_same< Nil, Sx >::value,
						typename Unit<  Cons< Sx, typename Cdr< S >::type > >::type,
						Nil >::type;
      };

      using type = Procedure< Local >;
      
    };


    /** Apply a procedure. 
     */
    template< typename ... >
    struct Apply;

    template<
      template< typename ... > class F,
      typename ... Xs
      >
    struct Apply< Procedure< F >, Xs ... >
    {
      using type = typename F< Xs ... >::type;
    }; // end of struct template Apply



    /** 
     */
    template< typename ... >
    struct Call_fresh;

    
    template< template< typename ... > class F >
    struct Call_fresh< Procedure< F > >
    {
      template< typename ... >
      struct G;

      template< typename SC>
      struct G< SC >
      {
	COMBINE_STATIC_ASSERT_TRUE( Consp< SC >::value );
	
	using C = typename Cdr< SC >::type;

	using type = typename Apply<
	  typename F< Var< C::value > >::type,
	  Cons< typename Car< SC >::type, Datum< size_t, 1+C::value > > >::type;
      };

      using type = Procedure< G >;
      
    }; // end of struct template Call_fresh



    template< typename ... >
    struct Disj;

    template<
      template< typename ... > class G1,
      template< typename ... > class G2
      >
    struct Disj< Procedure< G1 >, Procedure< G2 > >
    {
      
      template< typename ... >
      struct F;

      template< typename SC >
      struct F< SC >
      {
	using type = typename Mplus<
	  typename G1< SC >::type,
	  typename G2< SC >::type >::type;
      };
      
      using type = Procedure< F >;
      
    };
    


    template< typename ... >
    struct Conj;

    template<
      template< typename ... > class G1,
      template< typename ... > class G2
      >
    struct Conj< Procedure< G1 >, Procedure< G2 > >
    {
      template< typename ... >
      struct F;

      template< typename SC >
      struct F< SC >
      {
	using type = typename Bind< typename G1< SC >::type, Procedure< G2 > >::type;
      };

      using type = Procedure< F >;
	
    };
    	  

    using Empty_state = Cons< Nil, Datum< size_t, 0 > >;
    
    template< typename ... >
    struct Zzz;

    template< template< typename ... > class F >
    struct Zzz< Procedure< F > >
    {
      
      template< typename ... >
      struct G;

      template< typename SC >
      struct G< SC >
      {

	template< typename ... >
	struct H;

	template< typename ... >
	struct H
	{
	  using type = typename F< SC >::type;
	};
	
	using type = Procedure< G >;
	
      };
      
      using type = Procedure< G >;
    };

    template< typename ... >
    struct Conj_plus;

    template< template< typename ... > class G >
    struct Conj_plus< Procedure< G > >
    {
      using type = typename Zzz< Procedure< G > >::type;
    };

    template<
      template< typename ... > class G0,
      template< typename ... > class G1,
      template< typename ... > class ... Gs >
    struct Conj_plus< Procedure< G0 >, Procedure< G1 >, Procedure< Gs > ... >
    {
      using type =  typename Conj<
	typename Zzz< Procedure< G0 > >::type,
	typename Conj_plus< Procedure< G1 >, Procedure< Gs > ... >::type
	>::type;
    };


    template< typename ... >
    struct Disj_plus;

    template< template< typename ... > class G >
    struct Disj_plus< Procedure< G > >
    {
      using type = typename Zzz< Procedure< G > >::type;
    };

    template<
      template< typename ... > class G0,
      template< typename ... > class G1,
      template< typename ... > class ... Gs
      >
    struct Disj_plus< Procedure< G0 >, Procedure< G1 >, Procedure< Gs > ... >
    {
      using type = typename Disj<
	typename Zzz< Procedure< G0 > >::type,
	typename Disj_plus< Procedure< G1 >, Procedure< Gs > ... >::type
	>::type;
    };


    template< typename ... >
    struct Fresh;

    template<
      template< typename ... > class G,
      template< typename ... > class ... Gs >
    struct Fresh< Procedure< G >, Procedure< Gs > ... >
    {
      using type = typename Conj_plus< Procedure< G >, Procedure< Gs > ... >::type;
    };

    template<
      typename X,
      typename Y,
      template< typename ... > class G,
      template< typename ... > class ... Gs
      >
    struct Fresh< Cons< X, Y >, Procedure< G >, Procedure< Gs > ... >
    {

      template< typename ... >
      struct F
      {
    	using type = typename Fresh< Y, Procedure< G >, Procedure< Gs > ... >::type;
      };
      
      using type = typename Call_fresh< Procedure< F > >::type;
      
    };


    template< typename ... >
    struct Pull;

    template< template< typename ... > class F >
    struct Pull< Procedure< F > >
    {
      using type = typename Pull< typename F<>::type >::type;
    };

    template< typename X >
    struct Pull< X >
    {
      using type = X;
    };

    


    template< size_t, typename ... >
    struct Take;

    template<  typename Ignored >
    struct Take< 0, Ignored >
    {
      using type = Nil;
    };

    template< size_t n, typename LG >
    struct Take< n, LG >
    {
      using  F = typename Pull< LG >::type;
      using type = typename std::conditional<
	Null< F >::value,
	Nil,
	Cons< typename Car< F >::type,
	      typename Take< n-1, typename Cdr< F >::type >::type
	      >
	>::type;
    };



    template< typename ... >
    struct Take_all;

    template< typename LG >
    struct Take_all< LG >
    {
      using F = typename Pull< LG >::type;
      using Type = typename std::conditional<
	Null< F >::value,
	Nil,
	Cons<
	  typename Car< F >::type,
	  typename Take_all< typename Cdr< F >::type >::type
	  >
	>::type;
    };

    
    template< typename ... >
    struct Conde;

    template<
      typename X,
      typename Y,
      typename ... Xs,
      typename ... Ys >
    struct Conde< Cons< X, Y >, Cons< Xs, Ys > ... >
    {
      using type = typename Disj_plus<
	typename Conj_plus< X, Y >::type,
	typename Conj_plus< Xs, Ys >::type ...
	>::type;
    };


    template< typename ... >
    struct Walk_star;

    template< typename V, typename S  >
    struct Walk_star< V, S >
    {
      using U = typename Walk< V, S >::type;

      template< typename ... >
      struct Aux;

      template< size_t i >
      struct Aux< Var< i > >
      {
	using type = Var< i >;
      };

      template< typename X, typename Y >
      struct Aux< Cons< X, Y > >
      {
	using type = Cons< typename Walk_star< X, S >::type,
			   typename Walk_star< Y, S >::type >;
      };

      template< typename W >
      struct Aux< W >
      {
	using type = W;
      };

      using type = typename Aux< U >::type;
      
    };


    template< typename ... >
    struct Reify_name;

    

    
    // template< typename ... >
    // struct Reify_S;

    // template< typename V, typename S >
    // struct Reify_S< V, S >
    // {

    //   using U = typename Walk< V, S >::type;

    //   template< typename ... >
    //   struct Aux;

    //   template< size_t i >
    //   struct Aux< Var< i > >
    //   {
    // 	using N typename Reify_name< Length<
    //   }

      

      
    // };

    


    // template< typename ... >
    // struct Reify_first;

    // template< typename SC >
    // struct Reify_first< SC >
    // {
    //   using V = typename Walk_star< Var< 0 >, typename Car< SC >::type >::type;
    //   using type = typename Walk_star<
    // 	V,
    // 	typename Reify_S< V, Nil > >::type
    // 	>::type;
    // };





	      


    
  } // end of namespace Meta_Kanren
    




  
} // end of namespace Combine



#endif // ! define META_KANREN_HPP_INCLUDED_1504389316913040494
