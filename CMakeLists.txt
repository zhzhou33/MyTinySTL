cmake_minimum_required (VERSION 3.15.0)
project (MyTinySTL)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_EXTENSIONS OFF)

set (SRC_LIST 
    main.cpp
    src/Alloc.cpp
)

set(TEST_SRC hello.cpp)
add_executable(${CMAKE_PROJECT_NAME} ${SRC_LIST})

# add_subdirectory(MyTinySTL)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    include
)

# add_executable(hello ${TEST_SRC})
