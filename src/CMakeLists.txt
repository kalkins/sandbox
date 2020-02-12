find_package(k4a REQUIRED)

add_library(sandbox_lib
  k4a_helper.cpp
  pipe_helper.cpp
  )

target_include_directories(sandbox_lib PUBLIC ../include/)
target_link_libraries(sandbox_lib PUBLIC k4a::k4a)
