# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License.

find_package(k4a REQUIRED)

include_directories(
    .
)

add_executable(sandbox
    main.cpp
    )

target_link_libraries(sandbox PRIVATE
    k4a::k4a)
