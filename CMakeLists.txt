cmake_minimum_required(VERSION 3.28)
project(WorkToolsGUI VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

# 第三方源码路径
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/third_party/imgui)
set(GLFW_DIR ${CMAKE_SOURCE_DIR}/third_party/glfw)

# 载入第三方源码
set(IMGUI_SOURCES
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_demo.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
        ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

# 引入为静态链接库
add_library(imgui STATIC ${IMGUI_SOURCES})

# 对库对象绑定头文件
target_include_directories(imgui PUBLIC
        ${IMGUI_DIR}
        ${IMGUI_DIR}/backends
        ${GLFW_DIR}/include
)

# 第三方库引入
add_subdirectory(${GLFW_DIR})

# 引入项目工程
add_subdirectory(src)

