find_package(k4a REQUIRED)

add_executable(sandbox main.cpp)

target_link_libraries(sandbox PRIVATE sandbox_lib k4a::k4a)
