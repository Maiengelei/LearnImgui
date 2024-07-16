# 新建 EXE 项目
add_executable(ImGuiWindow
        main.cpp
)

# 引入库
target_link_libraries(ImGuiWindow PRIVATE glfw imgui)

# 链接必要的系统库
if (UNIX)
    target_link_libraries(ImGuiWindow PRIVATE GL)
elseif (WIN32)
    target_link_libraries(ImGuiWindow PRIVATE opengl32)
endif()