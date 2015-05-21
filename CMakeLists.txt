cmake_minimum_required( VERSION 2.8.4 )

project( COMBINE )

option( BUILD_TESTS "Build the test suite?" ON )

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/combine/cmake/" )


include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR} )




if( BUILD_TESTS )
  include( simple_test )
  
  enable_testing()
  add_simple_test( easy easy_test test/easy_test.cpp )
  add_simple_test( count count_test test/count_test.cpp )

  
endif()

