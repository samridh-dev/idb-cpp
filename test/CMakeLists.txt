cmake_minimum_required(VERSION 3.18)

if (ENABLE_BUILD_TESTS)

  file(GLOB SOURCE_EXEC "*.cpp")
  if (NOT SOURCE_EXEC)
    message(FATAL_ERROR "no source files for test found.")
  endif()

  add_executable(hdf5daq_test ${SOURCE_EXEC})
  target_link_libraries(hdf5daq_test PRIVATE hdf5 hdf5_cpp Catch2::Catch2)

  if (ENABLE_BINARY_FOLDER)
    set_target_properties(hdf5daq_test 
      PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
    )
  endif()

endif()
