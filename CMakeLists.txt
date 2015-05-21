cmake_minimum_required( VERSION 2.8.4 )

project( COMBINE )

option( BUILD_TESTS "Build the test suite?" ON )

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/combine/cmake/" )


include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR} )




if( BUILD_TESTS )
  include( simple_test )

  macro( add_simplest_test NAME )
    add_simple_test(${NAME} ${NAME}_test test/${NAME}_test.cpp )
  endmacro()
  
  enable_testing()
  add_simplest_test( easy )
  add_simplest_test( count )
  add_simplest_test( base_types )
  add_simplest_test( nth )
  add_simplest_test( cons )
  add_simplest_test( list )

  
endif()

