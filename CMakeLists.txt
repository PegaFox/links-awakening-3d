cmake_minimum_required(VERSION 3.24)

project(Link's_awakening_3D)

add_subdirectory(glfw)

file(
  COPY ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_opengl3.h
  DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/imgui
)
file(
  COPY ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_opengl3.cpp
  DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/imgui
)
file(
  COPY ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_opengl3_loader.h
  DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/imgui
)
file(
  COPY ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_glfw.h
  DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/imgui
)
file(
  COPY ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_glfw.cpp
  DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/imgui
)

add_executable(main main.cpp glad/glad.c imgui/imgui.cpp imgui/imgui_widgets.cpp imgui/imgui_draw.cpp imgui/imgui_tables.cpp imgui/imgui_impl_opengl3.cpp imgui/imgui_impl_glfw.cpp)

target_include_directories(main PRIVATE . glm imgui glfw/include)

target_link_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/../opengl_utils/build ${CMAKE_BUILD_DIR}/glfw/src)

target_link_libraries(main glfw GL X11 assimp pfgl)
