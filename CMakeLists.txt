cmake_minimum_required(VERSION 3.9)

project(GameEngineByGL)


set(SOURCES
source.cpp
glad.c
# 添加其他源文件
)
add_executable(GameEngineByGL ${SOURCES})

add_library(GLAD STATIC glad.c)

find_package(OpenGL REQUIRED)

target_include_directories(GameEngineByGL PRIVATE ${PROJECT_SOURCE_DIR}/Dependencies/include)

target_link_libraries(GameEngineByGL PRIVATE ${PROJECT_SOURCE_DIR}/Dependencies/lib/libglfw3.a)