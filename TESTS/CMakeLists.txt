cmake_minimum_required(VERSION 3.14)
project(SnakeGame)

# Настройка C++ стандарта
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включаем поддиректории
add_subdirectory(game)
add_subdirectory(tests)
# Установите этот флаг перед add_subdirectory или project()
if(MSVC)
    # Используем динамическую версию Runtime Library (MD)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
    
    # Или для статической (MT):
    # set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()