#
# combine/cmake/simple_test.cmake -- A macro definition for simple test creation
#
# Author: Samuel B. Johnson
#
macro( add_simple_test NAME_TEST NAME_EXECUTABLE PATH_SOURCE_FILE )
  add_executable( ${NAME_EXECUTABLE} ${PATH_SOURCE_FILE} )
  add_test( ${NAME_TEST} ${NAME_EXECUTABLE} )
endmacro()
