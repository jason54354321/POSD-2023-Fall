cmake_minimum_required(VERSION 3.10)
project(posd VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# header
include_directories(include)

# src
file(GLOB_RECURSE SOURCE "src/*.cpp")
add_executable(run ${SOURCE})
target_link_libraries(run gtest_main)
target_include_directories(run PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# tests
file(GLOB_RECURSE TEST "tests/*.cpp")
file(GLOB_RECURSE TEST_SOURCE "src/*.cpp")
list(FILTER TEST_SOURCE EXCLUDE REGEX "main.cpp$")
add_executable(run_test ${TEST} ${TEST_SOURCE})
target_link_libraries(run_test gtest_main gmock_main)
target_include_directories(run_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# 設定測試運行命令，可以使用 ctest 命令運行所有單元測試
enable_testing()
add_test(NAME run_test COMMAND run_test)
