SET(LIB_PREFIX tools_)

ADD_LIBRARY(program_options
  program_options.h
  program_options.hpp
  program_options.cpp
)

TARGET_LINK_LIBRARIES(program_options   
  #boost_system
  boost_program_options
  #boost_filesystem
)

SET_TARGET_PROPERTIES(program_options PROPERTIES OUTPUT_NAME ${LIB_PREFIX}program_options)

INSTALL(TARGETS program_options
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
  LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
  ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
)

FILE(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")
INSTALL(FILES ${headers} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME}/program_options)