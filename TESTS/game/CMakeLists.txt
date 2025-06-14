# Библиотека с игровой логикой
add_library(GameLogic STATIC
    src/GameLogic.cpp
)

# Публичные заголовки
target_include_directories(GameLogic PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)