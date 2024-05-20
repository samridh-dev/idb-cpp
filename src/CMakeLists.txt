cmake_minimum_required(VERSION 3.18)

if (ENABLE_BUILD_EXAMPLE)

  file(GLOB SOURCE_EXEC "*.cpp")
  if (NOT SOURCE_EXEC)
    message(FATAL_ERROR "no source files for example executable found.")
  endif()

  add_executable(idb ${SOURCE_EXEC})
  # target_link_libraries(idb PRIVATE hdf5 hdf5_cpp)
  if (ENABLE_BINARY_FOLDER)
    set_target_properties(idb 
      PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
    )
  endif()

endif()
