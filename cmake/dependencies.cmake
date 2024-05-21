# tests dependency
if (ENABLE_BUILD_TEST)
  add_subdirectory(extern/catch2)
endif()

add_subdirectory(extern/libcurl)
include_directories(extern/libcurl/include)
