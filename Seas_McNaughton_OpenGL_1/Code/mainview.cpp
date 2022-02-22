#include "mainview.h"

#include <QDateTime>

/**
 * @brief MainView::MainView
 *
 * Constructor of MainView
 *
 * @param parent
 */
MainView::MainView(QWidget *parent) : QOpenGLWidget(parent) {
    qDebug() << "MainView constructor";

    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
    projection.perspective(60, 4/3, 0.1, 100);
    //transformShape(cubeMatrix, 2, 0, -6);
    //transformShape(pyramidMatrix, -2, 0, -6);

    cubeMatrix.translate(2,0,-6);
    pyramidMatrix.translate(-2,0,-6);
}

/**
 * @brief MainView::~MainView
 *
 * Destructor of MainView
 * This is the last function called, before exit of the program
 * Use this to clean up your variables, buffers etc.
 *
 */
MainView::~MainView() {
    qDebug() << "MainView destructor";

    makeCurrent();
    glDeleteBuffers(1, &cubeVBO);
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteBuffers(1, &pyramidVBO);
    glDeleteVertexArrays(1, &pyramidVAO);

}

// --- OpenGL initialization

/**
 * @brief MainView::initializeGL
 *
 * Called upon OpenGL initialization
 * Attaches a debugger and calls other init functions
 */
void MainView::initializeGL() {
    qDebug() << ":: Initializing OpenGL";
    initializeOpenGLFunctions();

    connect(&debugLogger, SIGNAL( messageLogged( QOpenGLDebugMessage)),
            this, SLOT(onMessageLogged(QOpenGLDebugMessage)), Qt::DirectConnection);

    if (debugLogger.initialize()) {
        qDebug() << ":: Logging initialized";
        debugLogger.startLogging(QOpenGLDebugLogger::SynchronousLogging);
    }

    QString glVersion{reinterpret_cast<const char*>(glGetString(GL_VERSION))};
    qDebug() << ":: Using OpenGL" << qPrintable(glVersion);

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable backface culling
    glEnable(GL_CULL_FACE);

    // Default is GL_LESS
    glDepthFunc(GL_LEQUAL);

    // Set the color to be used by glClear. This is, effectively, the background color.
    glClearColor(0.2F, 0.5F, 0.7F, 1.0F);

    createShaderProgram();

    glEnable(GL_CULL_FACE);

    VERTICE ver1 = {.x = -1, .y = -1, .z = -1, .r = 0, .g = 0, .b = 1}, ver2 = {.x = -1, .y = -1, .z = 1, .r = 0, .g = 1, .b = 0},
            ver3 = {.x = -1, .y = 1, .z = -1, .r = 0, .g = 1, .b = 1}, ver4 = {.x = -1, .y = 1, .z = 1, .r = 1, .g = 0, .b = 0},
            ver5 = {.x = 1, .y = -1, .z = -1, .r = 0, .g = 0.5, .b = 0.5}, ver6 = {.x = 1, .y = -1, .z = 1, .r = 1, .g = 0.5, .b = 0.5},
            ver7 = {.x = 1, .y = 1, .z = -1, .r = 0.5, .g = 1, .b = 0}, ver8 = {.x = 1, .y = 1, .z = 1, .r = 0.5, .g = 0, .b = 1};
            // creating cube vertices

    VERTICE pyrVer1 = ver1, pyrVer2 = ver2, pyrVer3 = ver5, pyrVer4 = ver6, pyrVer5 = {.x = 0, .y = 1, .z = 0, .r = 1, .g = 0, .b = 0};
            // creating pyramid vertices. The base square is the same as the bottom square of the cube and the top (apex) is pyrVer5

    // adding cube vertices to a vector, containing the combinations of triangles (z points to the screen)
    VERTICE cubeVector[36] = {ver1, ver2, ver3, ver2, ver3, ver4,  // left base
                              ver5, ver6, ver7, ver6, ver7, ver8,  // right base
                              ver1, ver3, ver5, ver3, ver5, ver7,  // back base
                              ver2, ver4, ver6, ver4, ver6, ver8,  // front base
                              ver4, ver3, ver8, ver3, ver8, ver7,  // top base
                              ver2, ver1, ver5, ver1, ver5, ver6}; // bottom base


    // adding pyramid vertices to a vector, containing the combinations of triangles (z points to the screen)
    VERTICE pyramidVector[18] = {pyrVer2, pyrVer1, pyrVer3, pyrVer1, pyrVer3, pyrVer4, // botton base
                                 pyrVer1, pyrVer2, pyrVer5,  // left triangle
                                 pyrVer2, pyrVer4, pyrVer5,  // front triangle
                                 pyrVer4, pyrVer3, pyrVer5,  // right triangle
                                 pyrVer3, pyrVer1, pyrVer5}; // back base


    glGenBuffers(1, &cubeVBO); // Generating cube VBO
    glGenVertexArrays(1, &cubeVAO); // Generating cube VAO

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO); // Binding cube's VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVector), cubeVector, GL_STATIC_DRAW);

    // Doing the same procedure for pyramid
    glGenBuffers(1, &pyramidVBO); // Generating pyramid's VBO
    glGenVertexArrays(1, &pyramidVAO); // Generating pyramid's VAO

    glBindVertexArray(cubeVAO); // Binding cube's VAO
    glBindVertexArray(pyramidVAO); // Binding pyramid's VAO

    glBindBuffer(GL_ARRAY_BUFFER, pyramidVBO); // Binding pyramid's VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(pyramidVector), pyramidVector, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0); // Creating location 0 for coordinates
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VERTICE), (void*) offsetof(VERTICE, x)); // Assigning values of VERTICE for coordinates
    glEnableVertexAttribArray(1); // Creating location 1 for color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VERTICE), (void*) offsetof(VERTICE, r)); // Assigning values of VERTICE for color


}

void MainView::transformShape(QMatrix4x4 shape, float x, float y, float z) {
    shape.setToIdentity();
    shape.translate(x, y, z);
}

void MainView::createShaderProgram() {
    // Create shader program
    program.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                           ":/shaders/vertshader.glsl");
    program.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                           ":/shaders/fragshader.glsl");
    program.link();

    // added code
    cubeModelLocation = program.uniformLocation("modelTransform"); // extracting uniform locations
    //pyramidModelLocation = program.uniformLocation("modelTransform");
    cubeProjectLocation = program.uniformLocation("projectTransform");
    //pyramidProjectLocation = program.uniformLocation("projectTransform");
//    if (cubeModelLocation  == -1 || pyramidModelLocation == -1 || cubeProjectLocation == -1 || pyramidProjectLocation == -1) {
//            qDebug() << "cannot create uniformLocation\n";
//            return ;
//        }

}

// --- OpenGL drawing

/**
 * @brief MainView::paintGL
 *
 * Actual function used for drawing to the screen
 *
 */
void MainView::paintGL() {
    // Clear the screen before rendering
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    program.bind();

    glUniformMatrix4fv(cubeProjectLocation, 1, GL_FALSE, projection.data());

    // Draw here
    glBindVertexArray(cubeVAO); // Binding cube's VAO
    glUniformMatrix4fv(cubeModelLocation, 1, GL_FALSE, cubeMatrix.data());
    glDrawArrays(GL_TRIANGLES, 0, 36); // drawing 12 triangles for the cube (2 for each base). Each triangle has 3 vertices

    glBindVertexArray(pyramidVAO); // Binding pyramid's VAO
    glUniformMatrix4fv(cubeModelLocation, 1, GL_FALSE, pyramidMatrix.data());
    glDrawArrays(GL_TRIANGLES, 0, 18); // drawing 6 triangles for the pyramid (2 for base). Each triangle has 3 vertices



    program.release();
}

/**
 * @brief MainView::resizeGL
 *
 * Called upon resizing of the screen
 *
 * @param newWidth
 * @param newHeight
 */
void MainView::resizeGL(int newWidth, int newHeight) {
    // TODO: Update projection to fit the new aspect ratio
   projection.setToIdentity();
   projection.perspective(60, (float(newWidth)/ float(newHeight)), 0.1, 100);
}

// --- Public interface

void MainView::setRotation(int rotateX, int rotateY, int rotateZ) {
    qDebug() << "Rotation changed to (" << rotateX << "," << rotateY << "," << rotateZ << ")";
    Q_UNIMPLEMENTED();
}

void MainView::setScale(int scale) {
    qDebug() << "Scale changed to " << scale;
    Q_UNIMPLEMENTED();
}

void MainView::setShadingMode(ShadingMode shading) {
    qDebug() << "Changed shading to" << shading;
    Q_UNIMPLEMENTED();
}

// --- Private helpers

/**
 * @brief MainView::onMessageLogged
 *
 * OpenGL logging function, do not change
 *
 * @param Message
 */
void MainView::onMessageLogged( QOpenGLDebugMessage Message ) {
    qDebug() << " → Log:" << Message;
}
