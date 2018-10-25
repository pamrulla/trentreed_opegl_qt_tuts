#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    //:ui(new Ui::QOpenGLWindow)
{
    //ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    //delete ui;
    makeCurrent();
    teardownGL();
}


void MainWindow::initializeGL()
{
    initializeOpenGLFunctions();
    printContextInformation();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    program = new QOpenGLShaderProgram();
    program->addCacheableShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/simple.vert");
    program->addCacheableShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/simple.frag");
    program->link();
    program->bind();

    float vertices[] = {
         0.00f,  0.75f, 1.0f,      1.0f, 0.0f, 0.0f,
         0.75f, -0.75f, 1.0f,      0.0f, 1.0f, 0.0f,
        -0.75f, -0.75f, 1.0f,      0.0f, 0.0f, 1.0f
    };

    vao.create();
    vao.bind();

    vbo.create();
    vbo.bind();
    vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vbo.allocate(vertices, 18 * sizeof(float));

    program->enableAttributeArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    program->enableAttributeArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    vao.release();
    vbo.release();
    program->release();

}

void MainWindow::resizeGL(int w, int h)
{
}

void MainWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    program->bind();
    {
        vao.bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);
        vao.release();
    }
    program->release();
}

void MainWindow::teardownGL()
{
    vao.destroy();
    vbo.destroy();
    delete program;
}

void MainWindow::printContextInformation()
{
    QString glType;
    QString glVersion;
    QString glProfile;

    glType = (context()->isOpenGLES()) ? "OpenGL ES" : "OpenGL";
    glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));

#define CASE(c) case QSurfaceFormat::c: glProfile = #c; break
  switch (format().profile())
  {
    CASE(NoProfile);
    CASE(CoreProfile);
    CASE(CompatibilityProfile);
  }
#undef CASE
    qDebug() << qPrintable(glType) << qPrintable(glVersion) << "(" << qPrintable(glProfile) << ")";
}
















