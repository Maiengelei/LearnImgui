# 新建 EXE 项目
add_executable(ImGuiWindow
        main.cpp
        mainWindow.cpp
)

# 引入库
target_link_libraries(ImGuiWindow PRIVATE glfw imgui)
target_include_directories(ImGuiWindow PRIVATE ${CMAKE_SOURCE_DIR}/include)

# 链接必要的系统库
if (UNIX)
    target_link_libraries(ImGuiWindow PRIVATE GL)
elseif (WIN32)
    target_link_libraries(ImGuiWindow PRIVATE opengl32)
endif()