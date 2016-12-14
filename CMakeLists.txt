cmake_minimum_required(VERSION 2.8)

#project name
project(tools)

FIND_PACKAGE(Eigen3 REQUIRED)

SET(LIB_PREFIX ${PROJECT_NAME}_)
SET(${PROJECT_NAME}_LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib CACHE PATH "Output path for libraries")
SET(${PROJECT_NAME}_EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin CACHE PATH "Output path for executables")
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${${PROJECT_NAME}_LIBRARY_OUTPUT_PATH})
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${${PROJECT_NAME}_EXECUTABLE_OUTPUT_PATH})
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${${PROJECT_NAME}_LIBRARY_OUTPUT_PATH})
SET(BUILD_SHARED_LIBS ON)

# activate warnings !!!
SET(${PROJECT_NAME}_C_FLAGS "${${PROJECT_NAME}_C_FLAGS} -Wall -W")
SET(${PROJECT_NAME}_CXX_FLAGS "${${PROJECT_NAME}_CXX_FLAGS} -Wall -W")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${${PROJECT_NAME}_C_FLAGS}")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${${PROJECT_NAME}_CXX_FLAGS}")

# C++11 support
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
  MESSAGE("Found C++11 support")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
  ADD_DEFINITIONS(-DCXX11_SUPPORT)
elseif(COMPILER_SUPPORTS_CXX0X)
  MESSAGE("Found C++0x support")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
  message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

# add openmp support
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")

#####################
#### gtest ##########
#####################
# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in
               googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
 
# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
 
# Add googletest directly to our build. This adds
# the following targets: gtest, gtest_main, gmock
# and gmock_main
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                 ${CMAKE_BINARY_DIR}/googletest-build)
 
# The gtest/gmock targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include"
                      "${gmock_SOURCE_DIR}/include")
endif()
 
# Now simply link your own targets against gtest, gmock,
# etc. as appropriate

# build and run tests
enable_testing()

# Set up the top-level include directories
INCLUDE_DIRECTORIES(
  ${${PROJECT_NAME}_SOURCE_DIR}
  ${EIGEN3_INCLUDE_DIR}
)

ADD_SUBDIRECTORY(io_functions)
ADD_SUBDIRECTORY(program_options)
ADD_SUBDIRECTORY(sampler)
ADD_SUBDIRECTORY(image_processing)
ADD_SUBDIRECTORY(eigen_helper)
ADD_SUBDIRECTORY(tests)
ADD_SUBDIRECTORY(string_processing)
ADD_SUBDIRECTORY(integral)
ADD_SUBDIRECTORY(math_functions)
ADD_SUBDIRECTORY(bit_parsing)