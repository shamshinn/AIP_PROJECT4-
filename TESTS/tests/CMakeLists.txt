cmake_minimum_required(VERSION 3.14)
project(SnakeGameTests)

# Вариант 1: Используем FetchContent (рекомендуется)
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# ИЛИ Вариант 2: Ручное подключение с указанием бинарной директории
# add_subdirectory(
#   ${CMAKE_SOURCE_DIR}/extern/googletest
#   ${CMAKE_BINARY_DIR}/googletest-build
# )

add_executable(SnakeGameTests
    src/tests.cpp
)

target_link_libraries(SnakeGameTests
    PRIVATE
    GameLogic
    gtest_main
)

target_include_directories(SnakeGameTests PRIVATE
    ${CMAKE_SOURCE_DIR}/game/include
)

include(GoogleTest)
gtest_discover_tests(SnakeGameTests)
# Перед добавлением googletest
if(MSVC)
    # Убедимся, что Google Test использует ту же Runtime Library
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

# Затем добавляем Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)