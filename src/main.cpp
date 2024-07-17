#include <cstdio>
#include "mainWindow.h"

int main(int argc, char **argv)
{
    // 创建并运行应用程序
    MainWindow app("WorkTools", 1366, 768);
    app.Run();

    return 0;
}