cmake_minimum_required(VERSION 3.9)

project(GameEngineByGL)


set(SOURCES
source.cpp
VertexBuffer.cpp
VertexArray.cpp
VertexBufferLayout.cpp
IndexBuffer.cpp
Shader.cpp
glad.c
Texture.cpp
Renderer.cpp
DependencyManagerImpl.cpp
#imgui
./Dependencies/include/imgui/imgui_impl_glfw.cpp
./Dependencies/include/imgui/imgui_impl_opengl3.cpp
./Dependencies/include/imgui/imgui.cpp
./Dependencies/include/imgui/imgui_demo.cpp
./Dependencies/include/imgui/imgui_draw.cpp
./Dependencies/include/imgui/imgui_tables.cpp
./Dependencies/include/imgui/imgui_widgets.cpp
#stb
./Dependencies/include/stb_image/stb_image.cpp
#test
./Test/Test.cpp
./Test/TestClearColor.cpp
./Test/TestTexture2D.cpp
./Test/TestTexture3D.cpp
./Test/TestCameraScene.cpp
#Object
./Object/Camera.cpp
./Object/FreeCamera.cpp
)
add_executable(GameEngineByGL ${SOURCES})

add_library(GLAD STATIC glad.c)

find_package(OpenGL REQUIRED)

target_include_directories(GameEngineByGL PRIVATE ${PROJECT_SOURCE_DIR}/Dependencies/include)

target_link_libraries(GameEngineByGL PRIVATE ${PROJECT_SOURCE_DIR}/Dependencies/lib/libglfw3.a)