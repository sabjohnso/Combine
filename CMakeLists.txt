cmake_minimum_required( VERSION 2.8.4 )
project( COMBINE )


#
# ... Options
#
option( BUILD_TESTS "Build the test suite?" ON )



set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
  "${CMAKE_CURRENT_SOURCE_DIR}/combine/cmake"
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include( combineVersion )
set( COMBINE_VERSION
  "${COMBINE_MAJOR_VERSION}.${COMBINE_MINOR_VERSION}.${COMBINE_BUILD_VERSION}" )

if( NOT COMBINE_INSTALL_INCLUDE_DIR )
  set( COMBINE_INSTALL_INCLUDE_DIR include/combine-${COMBINE_MAJOR_VERSION}.${COMBINE_MINOR_VERSION}/combine )
endif()

if( NOT COMBINE_INSTALL_DOC_DIR)
  set( COMBINE_INSTALL_DOC_DIR share/doc/combine-${COMBINE_MAJOR_VERSION}-${COMBINE_MINOR_VERSION} )
endif()

configure_file( 
  ${CMAKE_CURRENT_SOURCE_DIR}/combine/config.hpp.in
  ${CMAKE_CURRENT_BINARY_DIR}/combine/config.hpp )

include_directories( 
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR} )


install( FILES
  combine/apply.hpp
  combine/base_types.hpp
  combine/combine.hpp
  ${CMAKE_CURRENT_BINARY_DIR}/combine/config.hpp
  combine/cons.hpp
  combine/composite.hpp
  combine/context.hpp
  combine/count.hpp
  combine/datum.hpp
  combine/fold.hpp
  combine/funcall.hpp
  combine/get.hpp
  combine/idx.hpp
  combine/infix_operator_list.def
  combine/import.hpp
  combine/length.hpp
  combine/list.hpp
  combine/macro_tools.hpp
  combine/make.hpp
  combine/nil.hpp
  combine/nth.hpp
  combine/operator.hpp
  combine/partial.hpp
  combine/pow.hpp
  combine/select_with_sizeof.hpp
  combine/simple.hpp
  combine/symbol.hpp
  combine/traits.hpp
  combine/transpose.hpp
  combine/type.hpp
  DESTINATION ${COMBINE_INSTALL_INCLUDE_DIR} )

install( FILES
  combine/cmake/simple_test.cmake
  DESTINATION ${COMBINE_INSTALL_INCLUDE_DIR}/cmake )



if( BUILD_TESTS )
  enable_testing()

  include( simple_test )

  add_simplest_test( apply )
  add_simplest_test( base_types )
  add_simplest_test( composite )
  add_simplest_test( cons )
  add_simplest_test( count )
  add_simplest_test( datum )
  add_simplest_test( easy )
  add_simplest_test( fold )
  add_simplest_test( funcall )
  add_simplest_test( get )
  add_simplest_test( idx )
  add_simplest_test( list )
  add_simplest_test( make )
  add_simplest_test( nth )
  add_simplest_test( operator )
  add_simplest_test( pow )
  add_simplest_test( simple )
  add_simplest_test( traits )
  add_simplest_test( transpose )
  add_simplest_test( length )
  
endif()

