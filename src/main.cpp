#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GLFW/glfw3.h"
#include <cstdio>

// GLFW 错误回调
static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

int main(int, char**)
{
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    // OpenGL 版本
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    // 使用图形上下文创建窗口
    GLFWwindow* window = glfwCreateWindow(1366, 768, "Dear ImGui GLFW+OpenGL3 example", nullptr, nullptr);
    if (window == nullptr)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // 启用垂直同步

    // 设置 Dear ImGui 上下文
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // 设置 Dear ImGui 样式
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // 设置平台/渲染器后端
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Renderer loop
    while (!glfwWindowShouldClose(window))
    {
        // 轮询和处理事件（输入、窗口调整大小等）
        // 您可以阅读 io.WantCaptureMouse，io。WantCaptureKeyboard 标志，用于判断亲爱的 imgui 是否想使用您的输入。
        // - 当 io.WantCaptureMouse 为 true，请勿将鼠标输入数据分派给主应用程序，也不要清除/覆盖鼠标数据的副本。
        // - 当 io.WantCaptureKeyboard 为 true，请勿将键盘输入数据分派给主应用程序，也不要清除/覆盖键盘数据的副本。
        // 通常，您可以始终将所有输入传递给 dear imgui，并根据这两个标志将它们从您的应用程序中隐藏。
        glfwPollEvents();

        // 启动 Dear ImGui 框架
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 1. 展示大演示窗口（大部分示例代码都在 ImGui：：ShowDemoWindow（）！您可以浏览其代码以了解有关 Dear ImGui 的更多信息！
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // 2. 展示我们自己创建的简单窗口。我们使用 Begin/End 对来创建命名窗口。
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                                              // 创建一个名为“Hello， world！”的窗口，并附加到其中。

            ImGui::Text("This is some useful text.");                                    // 显示一些文本（您也可以使用字符串格式）
            ImGui::Checkbox("Demo Window", &show_demo_window);                          // 编辑存储窗口打开/关闭状态的布尔斯
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);                     // 使用从 0.0f 到 1.0f 的滑块编辑 1 个浮点数
            ImGui::ColorEdit3("clear color", reinterpret_cast<float *>(&clear_color));  // 编辑 3 个代表颜色的浮点数

            if (ImGui::Button("Button"))                                                // 按钮在单击时返回 true（大多数小部件在编辑/激活时返回 true）
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();
        }

        // 3. 显示另一个简单的窗口。
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);   // 将指针传递给我们的 bool 变量（窗口将有一个关闭按钮，单击该按钮时将清除 bool）
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }

        // 渲染
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // 清理
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
