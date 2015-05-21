#ifndef MACRO_TOOLS_HPP_INCLUDED_1197291527560050376
#define MACRO_TOOLS_HPP_INCLUDED_1197291527560050376 1


// Standard header files

#include <type_traits>


/** A macro for grouping text into a single macro argument.
    This macro is useful in cases where a single argument is
    being broken inappropriately: at the commas in a tempalate
    parameter list.
 */
#define ARG( ... ) __VA_ARGS__ 



/** An auxilliary macro that is used by COMBINE_QUOTE
 */
#define COMBINE_QUOTE_AUX( ... ) #__VA_ARGS__


/** A macro to surround its arguments in quotation marks.
 */
#define COMBINE_QUOTE( ... ) COMBINE_QUOTE_AUX( __VA_ARGS__ )


#define COMBINE_MESSAGE_BOX( TITLE, ... )				\
  "\n\n"								\
  "\n*****************************************************************\n" \
  TITLE									\
  "\n-----------------------------------------------------------------\n\n" \
  __VA_ARGS__								\
  "\n"									\
  "\n-----------------------------------------------------------------\n\n"


#define COMBINE_LOCATION() \
  __FILE__ ":" COMBINE_QUOTE( __LINE__ ) ":0"


/** A static assertion that prints the failed expression.
 */
#define COMBINE_STATIC_ASSERT_TRUE( ... )				\
  static_assert( __VA_ARGS__ ,						\
		   COMBINE_MESSAGE_BOX( "ASSERTION FAILURE",		\
		   __FILE__ ":" COMBINE_QUOTE( __LINE__ )		\
		   ":0 static assertion failure:\n"			\
		   COMBINE_QUOTE( __VA_ARGS__ )				\
		   " was asserted to be true, but it is false.\n" ))

#define COMBINE_STATIC_ASSERT_FALSE( ... )				\
  static_assert(							\
    !( __VA_ARGS__ ),							\
    COMBINE_MESSAGE_BOX(						\
      "ASSERTION FAILURE"						\
      COMBINE_LOCATION()						\
      " static assertion failure:\n"					\
      COMBINE_QUOTE( __VA_ARGS__ )					\
      " was asserted to be false, but it it true.\n" ))

#define COMBINE_STATIC_ASSERT_EQUAL( A, B )				\
  static_assert(							\
    ( A ) == ( B ),							\
    COMBINE_MESSAGE_BOX(						\
      "ASSERTION FAILURE",						\
      COMBINE_LOCATION()						\
      " a static equality assertion failed: \n"				\
      COMBINE_QUOTE( A ) " is not equal to "				\
      COMBINE_QUOTE( B ) ", as was asserted." ))


#define COMBINE_STATIC_ASSERT_SAME_TYPE( A, B )				\
  static_assert(							\
    std::is_same<ARG( A ), B >::value,					\
    COMBINE_MESSAGE_BOX(						\
      "ASSERTION FAILURE",						\
      COMBINE_LOCATION()						\
      " a static type equality assertion failed: \n"			\
      COMBINE_QUOTE( A ) " is not the same type as "			\
      COMBINE_QUOTE( B ) ", as was asserted." ))




#endif // ! defined MACRO_TOOLS_HPP_INCLUDED_1197291527560050376
