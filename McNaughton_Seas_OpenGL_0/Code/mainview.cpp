#include "mainview.h"
#include "triangleVertice.h"

GLuint cubeVBO, cubeVAO;
QOpenGLShaderProgram program;

MainView::MainView(QWidget *parent) : QOpenGLWidget(parent) {
    qDebug() << "MainView constructor";
}

MainView::~MainView() {
    qDebug() << "MainView destructor";

    makeCurrent();
    glDeleteBuffers(1, &cubeVBO);
    glDeleteVertexArrays(1, &cubeVAO);
}

void MainView::initializeGL() {
    qDebug() << ":: Initializing OpenGL";
    initializeOpenGLFunctions();

    connect(&debugLogger, SIGNAL(messageLogged(QOpenGLDebugMessage)),
            this, SLOT(onMessageLogged(QOpenGLDebugMessage)), Qt::DirectConnection);

    if (debugLogger.initialize()) {
        qDebug() << ":: Logging initialized";
        debugLogger.startLogging(QOpenGLDebugLogger::SynchronousLogging);
    }

    QString glVersion{reinterpret_cast<const char*>(glGetString(GL_VERSION))};
    qDebug() << ":: Using OpenGL" << qPrintable(glVersion);

    VERTICE ver1 = {.x = -1, .y = -1, .r = 1, .g = 0, .b = 0}, ver2 = {.x = 1, .y = -1, .r = 0, .g = 1, .b = 0},
            ver3 = {.x = 0, .y = 1, .r = 0, .g = 0, .b = 1}; // creating triangle vertices
    VERTICE qVector[3] = {ver1, ver2, ver3}; // adding them to a vector

    glGenBuffers(1, &cubeVBO); // Generating VBO
    glGenVertexArrays(1, &cubeVAO); // Generating VAO

    program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vertshader.glsl");
    program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fragshader.glsl"); // Adding shaders
    program.link(); // Linking with the context
    program.bind(); // Binding them together


    glBindVertexArray(cubeVAO); // Binding VAO
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO); // Binding VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(qVector), qVector, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0); // Creating location 0 for coordinates
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(VERTICE), (void*) offsetof(VERTICE, x)); // Assigning values of VERTICE for coordinates
    glEnableVertexAttribArray(1); // Creating location 1 for color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VERTICE), (void*) offsetof(VERTICE, r)); // Assigning values of VERTICE for color
}

void MainView::resizeGL(int newWidth, int newHeight) {
    Q_UNUSED(newWidth)
    Q_UNUSED(newHeight)
}

void MainView::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glViewport(0, 0, width(), height());
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void MainView::onMessageLogged(QOpenGLDebugMessage Message) {
    qDebug() << " → Log:" << Message;
}
