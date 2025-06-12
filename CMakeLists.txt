cmake_minimum_required(VERSION 3.24)

project(Link's_awakening_3D)

link_directories(${CMAKE_SOURCE_DIR}/../opengl_utils/build)

link_libraries(glfw GL X11 assimp pfgl)

add_library(imgui_lib imgui/imgui.cpp imgui/imgui_widgets.cpp imgui/imgui_draw.cpp imgui/imgui_tables.cpp imgui/imgui_impl_opengl3.cpp imgui/imgui_impl_glfw.cpp)

add_executable(main main.cpp /usr/include/glad/glad.c)

target_link_libraries(main imgui_lib)
