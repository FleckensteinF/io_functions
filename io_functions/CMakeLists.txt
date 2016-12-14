SET(LIB_PREFIX tools_)

ADD_LIBRARY(io_functions
  io_functions.h 
  io_functions.hpp
  io_functions.cpp
)

TARGET_LINK_LIBRARIES(io_functions   
  boost_system
  boost_filesystem)

SET_TARGET_PROPERTIES(io_functions PROPERTIES OUTPUT_NAME ${LIB_PREFIX}io_functions)

INSTALL(TARGETS io_functions
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
  LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
  ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
)

FILE(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")
INSTALL(FILES ${headers} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME}/io_functions)