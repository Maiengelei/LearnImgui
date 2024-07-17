#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GLFW/glfw3.h"

/**
 * @class MainWindow
 * @brief 用于创建和运行使用 OpenGL 和 ImGui 的应用程序框架
 */
class MainWindow {
public:
    /**
     * @brief 构造函数，初始化应用程序
     * @param title 窗口标题
     * @param width 窗口宽度
     * @param height 窗口高度
     */
    MainWindow(const char *title, int width, int height);
    ~MainWindow();

    /**
     * @brief 运行应用程序主循环
     */
    void Run();

private:
    /**
     * @brief 初始化应用程序，创建窗口和设置 ImGui 上下文
     */
    void Init();

    /**
     * @brief 清理应用程序，销毁窗口释放资源
     */
    void Cleanup() const;

    /**
     * @brief 渲染主循环
     */
    void RenderMainLoop();

    /**
     * @brief 渲染 UI 界面
     * @param clearColor 清除颜色
     */
    void RenderUI(ImVec4& clearColor);

    const char *title;          ///< 窗口标题
    int width;                  ///< 窗口宽度
    int height;                 ///< 窗口高度
    GLFWwindow *window;         ///< GLFW 窗口指针
    const char *glsl_version;   ///< GLSL 版本号字符串
};


#endif //MAINWINDOW_H
