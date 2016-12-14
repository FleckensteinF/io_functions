SET(LIB_PREFIX tools_)

ADD_LIBRARY(string_processing
  string_mod.h 
  string_mod.cpp
  string_ana.h
  string_ana.cpp
  type_conversion.h
  type_conversion.cpp
  func.h
  func.cpp
)

#TARGET_LINK_LIBRARIES(io_functions   
#  boost_system
#  boost_filesystem)

SET_TARGET_PROPERTIES(string_processing PROPERTIES OUTPUT_NAME ${LIB_PREFIX}string_processing)

INSTALL(TARGETS string_processing
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
  LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
  ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
)

FILE(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")
INSTALL(FILES ${headers} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME}/string_processing)