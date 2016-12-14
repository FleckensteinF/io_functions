
########################
## TEST ################
########################

ADD_EXECUTABLE(io_functions_test 
  io_functions_test.cpp
)
TARGET_LINK_LIBRARIES(io_functions_test gtest_main io_functions)
ADD_TEST(test_io_functions ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/io_functions_test)


ADD_EXECUTABLE(program_options_test
  program_options_test.cpp
)
TARGET_LINK_LIBRARIES(program_options_test gtest_main program_options)
ADD_TEST(test_program_options ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/program_options_test)

ADD_EXECUTABLE(integral_test
  integral_test.cpp
)
TARGET_LINK_LIBRARIES(integral_test gtest_main integral)
ADD_TEST(test_integral ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/integral_test)

ADD_EXECUTABLE(eigen_helper_test
  eigen_helper_test.cpp
)
TARGET_LINK_LIBRARIES(eigen_helper_test gtest_main eigen_helper)
ADD_TEST(test_eigen_helper ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/eigen_helper_test)

ADD_EXECUTABLE(bit_parser_test
  bit_parser_test.cpp
)
TARGET_LINK_LIBRARIES(bit_parser_test gtest_main bit_parser)
ADD_TEST(test_bit_parser ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/bit_parser_test)

#INSTALL(TARGETS io_functions_test program_options_test
#  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
#  LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
#  ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
#)

ADD_CUSTOM_COMMAND(TARGET io_functions_test POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/binaries/testmap.txt $<TARGET_FILE_DIR:io_functions_test>
  COMMENT "copying test file testmap.txt")
ADD_CUSTOM_COMMAND(TARGET io_functions_test POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/binaries/test.txt $<TARGET_FILE_DIR:io_functions_test>
  COMMENT "copying test file test.txt")

ADD_CUSTOM_COMMAND(TARGET io_functions_test POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/binaries/testmap.txt .
  COMMENT "copying test file testmap.txt")
ADD_CUSTOM_COMMAND(TARGET io_functions_test POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/binaries/test.txt .
  COMMENT "copying test file test.txt")