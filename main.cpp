#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSurfaceFormat fmt;
    fmt.setRenderableType(QSurfaceFormat::RenderableType::OpenGL);
    fmt.setProfile(QSurfaceFormat::OpenGLContextProfile::CoreProfile);
    fmt.setVersion(3, 3);

    MainWindow w;
    w.setFormat(fmt);
    w.resize(800, 600);
    w.show();

    return a.exec();
}
