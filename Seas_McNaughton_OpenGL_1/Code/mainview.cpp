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
    projectionTransformation.perspective(60, 4/3, 0.1, 100);


//    transformShape(cubeMatrix, 2, 0, -6);
//    transformShape(pyramidMatrix, -2, 0, -6);
    cubeMatrix.translate(2, 0, -6);
    pyramidMatrix.translate(-2, 0, -6);
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

    connect(&debugLogger, SIGNAL( messageLogged(QOpenGLDebugMessage)),
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

    VERTICE a = {.x = -1, .y = -1, .z = 1, .r = 0.1, .g = 0.2, .b = 0.3}, b = {.x = 1, .y = -1, .z = 1, .r = 0.3, .g = 1, .b = 0.2},
            c = {.x = 1, .y = 1, .z = 1, .r = 0, .g = 1, .b = 1}, d = {.x = -1, .y = 1, .z = 1, .r = 1, .g = 0, .b = 0},
            e = {.x = -1, .y = -1, .z = -1, .r = 0, .g = 0.5, .b = 0.5}, f = {.x = 1, .y = -1, .z = -1, .r = 0.5, .g = 1, .b = 0},
            g = {.x = 1, .y = 1, .z = -1, .r = 0, .g = 0.5, .b = 1}, h = {.x = -1, .y = 1, .z = -1, .r = 1, .g = 0, .b = 0.5};
            // creating cube vertices

    VERTICE pyrA = {.x = -1, .y = -1, .z = 1, .r = 1, .g = 1, .b = 0},
            pyrB = {.x = 1, .y = -1, .z = 1, .r = 0, .g = 1, .b = 0},
            pyrE = {.x = -1, .y = -1, .z = -1, .r = 0, .g = 0, .b = 1},
            pyrF = {.x = 1, .y = -1, .z = -1, .r = 0, .g = 1, .b = 1},
            pyrTop = {.x = 0, .y = 1, .z = 0, .r = 1, .g = 0, .b = 0};
            // creating pyramid vertices. The base square is the same as the bottom square of the cube and the top (apex) is pyrVer5

//    VERTICE pyrA = {.x = -1, .y = -1, .z = -1, .r = 0.5, .g = 0, .b = 0.2}, pyrB = {.x = 1, .y = -1, .z = -1, .r = 0.3, .g = 0.8, .b = 0.5},
//            pyrE = {.x = -1, .y = -1, .z = 1, .r = 1, .g = 0.2, .b = 0.1}, pyrF = {.x = 1, .y = -1, .z = 1, .r = 0, .g = 0.21, .b = 0.6},
//            pyrTop = {.x = 0, .y = 1, .z = 0, .r = 0, .g = 0, .b = 0};

    // adding cube vertices to a vector, containing the combinations of triangles (z points to the screen)
    VERTICE cubeVector[36] = {e, a, d, d, h, e,  // left base
                              h, g, c, c, d, h,  // top base
                              f, b, c, c, g, f,  // right base
                              a, b, c, c, d, a,  // back base
                              f, e, h, h, g, f,  // front base
                              a, e, f, f, b, a}; // bottom base


    // adding pyramid vertices to a vector, containing the combinations of triangles (z points to the screen)
    VERTICE pyramidVector[18] = {pyrA, pyrE, pyrF, pyrF, pyrB, pyrA, // botton base
                                 pyrE, pyrA, pyrTop,  // left triangle
                                 pyrF, pyrE, pyrTop,  // front triangle
                                 pyrB, pyrF, pyrTop,  // right triangle
                                 pyrA, pyrB, pyrTop}; // back base


    // FROM THIS LINE
    glGenBuffers(1, &cubeVBO); // Generating cube VBO
    glGenVertexArrays(1, &cubeVAO); // Generating cube VAO

    glBindVertexArray(cubeVAO); // Binding cube's VAO
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO); // Binding cube's VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVector), cubeVector, GL_STATIC_DRAW);

    // UNTIL THIS LINE
    // Doing the same procedure for pyramid
    // FROM THIS LINE

    glGenBuffers(1, &pyramidVBO); // Generating pyramid's VBO
    glGenVertexArrays(1, &pyramidVAO); // Generating pyramid's VAO


    glBindVertexArray(pyramidVAO); // Binding pyramid's VAO
    glBindBuffer(GL_ARRAY_BUFFER, pyramidVBO); // Binding pyramid's VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(pyramidVector), pyramidVector, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0); // Creating location 0 for coordinates
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VERTICE), (void*) offsetof(VERTICE, x)); // Assigning values of VERTICE for coordinates
    glEnableVertexAttribArray(1); // Creating location 1 for color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VERTICE), (void*) offsetof(VERTICE, r)); // Assigning values of VERTICE for color

    // UNTIL THIS LINE
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
    pyramidModelLocation = program.uniformLocation("modelTransform");
    cubeProjectLocation = program.uniformLocation("projectTransform");
    pyramidProjectLocation = program.uniformLocation("projectTransform");
    if (cubeModelLocation  == -1 || cubeProjectLocation == -1) {
            qDebug() << "cannot create uniformLocation\n";
            return ;
        }
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

    glUniformMatrix4fv(cubeProjectLocation, 1, GL_FALSE, projectionTransformation.data());

    // Draw here
    glBindVertexArray(cubeVAO); // Binding cube's VAO
    glUniformMatrix4fv(cubeModelLocation, 1, GL_FALSE, cubeMatrix.data());
    glDrawArrays(GL_TRIANGLES, 0, 36); // drawing 12 triangles for the cube (2 for each base). Each triangle has 3 vertices

    glUniformMatrix4fv(pyramidProjectLocation, 1, GL_FALSE, projectionTransformation.data());

    glBindVertexArray(pyramidVAO); // Binding pyramid's VAO
    glUniformMatrix4fv(pyramidModelLocation, 1, GL_FALSE, pyramidMatrix.data());
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
    Q_UNUSED(newWidth)
    Q_UNUSED(newHeight)
}

// --- Public interface

void MainView::setRotation(int rotateX, int rotateY, int rotateZ) {
    qDebug() << "Rotation changed to (" << rotateX << "," << rotateY << "," << rotateZ << ")";
//    QVector3D rotation;
//    if (rotateX < currentRotation.x())
//        rotation = QVector3D(rotateX - currentRotation.x(), 1, 1);
//    else if (rotateY < currentRotation.y())
//        rotation = QVector3D(1, rotateY - currentRotation.y(), 1);
//    else
//        rotation = QVector3D(1, 1, rotateZ - currentRotation.z());

//    pyramidMatrix.setToIdentity();
    pyramidMatrix.rotate(rotateX, 1, 0, 0);
    pyramidMatrix.rotate(rotateY, 0, 1, 0);
    pyramidMatrix.rotate(rotateZ, 0, 0, 1);/*
    pyramidMatrix.rotate(2.6, rotation);
    cubeMatrix.rotate(0, rotation);*/
    update();
    Q_UNIMPLEMENTED();
}

void MainView::setScale(int scale) {
    if (currentScale == 0) currentScale = 1;
    qDebug() << "Scale changed to " << scale;
    float scaleFloat = (float) (scale) / 100;
    float change = scaleFloat / currentScale; // if (change < 1) => Decreasing
    qDebug() << "Changed to " << change;
    pyramidMatrix.scale(change);
    if (scale == 100)
        currentScale = 1;
    else
        currentScale = (float) (scale) / 100;
    update();
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
