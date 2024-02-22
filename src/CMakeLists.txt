cmake_minimum_required(VERSION 3.14)
#set(CMAKE_CXX_COMPILER "C:/MinGW/bin/g++.exe")
project(s21_containers)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(.) 

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing() 

file(GLOB s21_containers_SRC CONFIGURE_DEPENDS  "tests/*.cc")

add_executable(s21_containers  
   ${s21_containers_SRC} 
   s21_containers.h
) 

target_compile_options(s21_containers
	PRIVATE -Wall -Werror -Wextra -Wpedantic
	-g -fprofile-arcs -ftest-coverage
)

target_link_libraries(s21_containers GTest::gtest_main pthread gcov) 

include(GoogleTest)
gtest_discover_tests(s21_containers)
