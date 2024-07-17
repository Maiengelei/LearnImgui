//
// Created by admin on 24-7-17.
//

#include "mainWindow.h"
#include <cstdio>
#include <stdexcept>

// GLFW 错误回调函数
static void glfw_error_callback(int error, const char *description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

MainWindow::MainWindow(const char *title, int width, int height) :
    title(title), width(width), height(height), window(nullptr), glsl_version("#version 130")
{

    Init();
}

MainWindow::~MainWindow()
{
    Cleanup();
}

void MainWindow::Init()
{
    // 设置错误回调
    glfwSetErrorCallback(glfw_error_callback);

    // 初始化 GLFW 库
    if (!glfwInit())
        throw std::runtime_error("Failed to initialize GLFW");

    // 设置 OpenGL 版本
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    // 创建 GLFW 窗口
    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (window == nullptr)
        throw std::runtime_error("Failed to create GLFW window");

    // 将当前窗口window设置为上下文
    glfwMakeContextCurrent(window);
    // 垂直同步
    glfwSwapInterval(1);

    // 检查 ImGui 版本
    IMGUI_CHECKVERSION();
    // 创建 ImGui 上下文
    ImGui::CreateContext();

    // 获取 ImGui IO 对象，用于配置 ImGui
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // 启用键盘控制
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // 启用游戏手柄控制

    // 设置 ImGui 样式为黑暗模式
    ImGui::StyleColorsDark();

    // 初始化 ImGui 的 GLFW 和 OpenGL3 后端
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

void MainWindow::Cleanup() const
{
    // 清理 ImGui OpenGL3 后端，ImGui GLFW 后端和 ImGui 上下文
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // 如果窗口存在，销毁窗口
    if (window)
        glfwDestroyWindow(window);

    // 终止 GLFW 库
    glfwTerminate();
}

void MainWindow::Run()
{
    RenderMainLoop();
}

void MainWindow::RenderMainLoop(){
    ImVec4 clearColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);  // 清除颜色

    while (!glfwWindowShouldClose(window))
    {
        // 处理所有挂起的事件
        glfwPollEvents();

        // 启用新的 ImGui 帧
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Render UI
        RenderUI(clearColor);

        // 渲染 ImGui 绘制数据
        ImGui::Render();

        // 获取缓冲区大小，通常是窗口大小乘以屏幕 DPI 缩放因子
        // display_w 和 display_x 分别保存宽度和高度
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);

        // 设置 OpenGL 视口为窗口大小
        glViewport(0, 0, display_w, display_h);

        // 清除颜色并将颜色与 alpha 混合
        glClearColor(clearColor.x * clearColor.w, clearColor.y * clearColor.w, clearColor.z * clearColor.w, clearColor.w);

        // 清除缓冲区，并用上面的值填充缓冲区（背景颜色）
        glClear(GL_COLOR_BUFFER_BIT);

        // 调用 ImGui 的 OpenGL 渲染函数，将 ImGui 绘制数据发送到 OpenGL
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // 交换缓冲区
        glfwSwapBuffers(window);
    }
}

void MainWindow::RenderUI(ImVec4 &clearColor){
    ImGui::Begin("Hello, world!");
    ImGui::End();
}
