#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QOpenGLWindow>
#include <QOpenGLFunctions>
#include <QDebug>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>

/*namespace Ui {
class QOpenGLWindow;
}*/

class MainWindow : public QOpenGLWindow, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    //Ui::QOpenGLWndow *ui;

    // QOpenGLWindow interface
protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void teardownGL();

private:
    QOpenGLBuffer vbo;
    QOpenGLVertexArrayObject vao;
    QOpenGLShaderProgram *program;
    void printContextInformation();
};

#endif // MAINWINDOW_H
