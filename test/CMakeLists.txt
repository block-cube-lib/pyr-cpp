cmake_minimum_required(VERSION 3.8)
enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
find_package(Threads REQUIRED)

project(pyrite_test)

# directory
include_directories(
  ../
  ./lib/googletest/googletest/include/
  )

# test
add_subdirectory(lib/googletest/googletest)

# source
set(pyrite_test_source
  ./src/config/type_test.cpp
  ./src/core/is_complete_type_test.cpp
  ./src/stopwatch_test.cpp
  ./src/core/void_t_test.cpp
  ./src/scope_exit_test.cpp
  ./src/singleton_test.cpp
  ./src/singleton_test.cpp
  )

if(MSVC)
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-long-long -pedantic")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-long-long -pedantic")
endif()

add_executable(${CMAKE_PROJECT_NAME} ${pyrite_test_source})
target_link_libraries(${CMAKE_PROJECT_NAME} Threads::Threads)
target_link_libraries(${CMAKE_PROJECT_NAME} gtest_main)
