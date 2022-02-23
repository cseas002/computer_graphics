#include "mainview.h"
#include <cstdlib>
#include <ctime>
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
    glDeleteBuffers(1, &sphereVBO);
    glDeleteVertexArrays(1, &sphereVAO);
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

    VERTICE pyrA = a, pyrB = b, pyrE = e, pyrF = f,
            pyrTop = {.x = 0, .y = 1, .z = 0, .r = 1, .g = 0, .b = 0};
            // creating pyramid vertices. The base square is the same as the bottom square of the cube and the top (apex) is pyrVer5

    // adding cube vertices to a vector, containing the combinations of triangles (z points to the screen)
    VERTICE cubeVector[36] = {e, a, d, d, h, e,  // left base
                              c, g, h, h, d, c,  // top base
                              f, e, h, h, g, f,  // front base
                              f, b, c, c, g, f,  // right base
                              a, b, c, c, d, a,  // back base
                              e, f, b, b, a, e}; // bottom base


    // adding pyramid vertices to a vector, containing the combinations of triangles (z points to the screen)
    VERTICE pyramidVector[18] = {pyrA, pyrE, pyrF, pyrF, pyrB, pyrA, // botton base
                                 pyrE, pyrA, pyrTop,  // left triangle
                                 pyrF, pyrE, pyrTop,  // front triangle
                                 pyrB, pyrF, pyrTop,  // right triangle
                                 pyrA, pyrB, pyrTop}; // back base

    std::srand(std::time(nullptr)); // Generate trully random numbers

    sphere3DVector = Model(":/models/sphere.obj").getVertices();

    VERTICE sphereVector[sizeof(VERTICE) * sphere3DVector.length()];
    for (int i = 0; i < sphere3DVector.length(); i++) {
        sphereVector[i].x = sphere3DVector[i].x();
        sphereVector[i].y = sphere3DVector[i].y();
        sphereVector[i].z = sphere3DVector[i].z();
        sphereVector[i].r = (float) std::rand() / (RAND_MAX + 1u); // can also try std::rand() for these
        sphereVector[i].g = (float) std::rand() / (RAND_MAX + 1u);
        sphereVector[i].b = (float) std::rand() / (RAND_MAX + 1u);
    }
//    free(sphereVector);


    // FROM THIS LINE
    glGenBuffers(1, &cubeVBO); // Generating cube VBO
    glGenVertexArrays(1, &cubeVAO); // Generating cube VAO

    glBindVertexArray(cubeVAO); // Binding cube's VAO
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO); // Binding cube's VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVector), cubeVector, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0); // Creating location 0 for coordinates
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VERTICE), (void*) offsetof(VERTICE, x)); // Assigning values of VERTICE for coordinates
    glEnableVertexAttribArray(1); // Creating location 1 for color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VERTICE), (void*) offsetof(VERTICE, r)); // Assigning values of VERTICE for color

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
    // Doing the same procedure for sphere
    // FROM THIS LINE
    glGenBuffers(1, &sphereVBO); // Generating sphere's VBO
    glGenVertexArrays(1, &sphereVAO); // Generating sphere's VAO

    glBindVertexArray(sphereVAO); // Binding sphere's VAO
    glBindBuffer(GL_ARRAY_BUFFER, sphereVBO); // Binding sphere's VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(sphereVector), sphereVector, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0); // Creating location 0 for coordinates
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VERTICE), (void*) offsetof(VERTICE, x)); // Assigning values of VERTICE for coordinates
    glEnableVertexAttribArray(1); // Creating location 1 for color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VERTICE), (void*) offsetof(VERTICE, r)); // Assigning values of VERTICE for color

    // UNTIL THIS LINE
}

void MainView::createShaderProgram() {
    // Create shader program
    program.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                           ":/shaders/vertshader.glsl");
    program.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                           ":/shaders/fragshader.glsl");
    program.link();

    // added code
    model_mat_location = program.uniformLocation("modelTransform"); // extracting uniform locations
    proj_mat_location = program.uniformLocation("projectTransform");
    if (model_mat_location  == -1 || proj_mat_location == -1) {
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

    // Draw here
    glUniformMatrix4fv(proj_mat_location, 1, GL_FALSE, proj_mat.data());

    glBindVertexArray(cubeVAO); // Binding cube's VAO
    model_mat = QMatrix4x4(); // 1 0 0 - 0 1 0
    model_mat.translate(2, 0, -6); // 1 0 x - 0 1 y
    model_mat.scale(currentScale);
    model_mat.rotate(currentX, QVector3D(1, 0, 0));
    model_mat.rotate(currentY, QVector3D(0, 1, 0));
    model_mat.rotate(currentZ, QVector3D(0, 0, 1));
    glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_mat.data());
    glDrawArrays(GL_TRIANGLES, 0, 36); // drawing 12 triangles for the cube (2 for each base). Each triangle has 3 vertices



    glBindVertexArray(pyramidVAO); // Binding pyramid's VAO
    model_mat = QMatrix4x4();
    model_mat.translate(-2, 0, -6); // 1 0 x - 0 1 y
    model_mat.scale(currentScale);
    model_mat.rotate(currentX, QVector3D(1, 0, 0));
    model_mat.rotate(currentY, QVector3D(0, 1, 0));
    model_mat.rotate(currentZ, QVector3D(0, 0, 1));
    glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_mat.data());
    glDrawArrays(GL_TRIANGLES, 0, 18); // drawing 6 triangles for the pyramid (2 for base). Each triangle has 3 vertices



    glBindVertexArray(sphereVAO); // Binding sphere's VAO
    model_mat = QMatrix4x4();
    model_mat.translate(0, 0, -10); //
    model_mat.scale(0.04 * currentScale); // setting the scale to 0.04
//    model_mat.scale(currentScale);
    model_mat.rotate(currentX, QVector3D(1, 0, 0));
    model_mat.rotate(currentY, QVector3D(0, 1, 0));
    model_mat.rotate(currentZ, QVector3D(0, 0, 1));
    glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_mat.data());
    glDrawArrays(GL_TRIANGLES, 0, sphere3DVector.length());

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
    proj_mat = QMatrix4x4();
    proj_mat.perspective(60, (float) (newWidth) / (float) (newHeight), 0.1, 100);
    Q_UNUSED(newWidth)
    Q_UNUSED(newHeight)
    update();
}

// --- Public interface

void MainView::setRotation(int rotateX, int rotateY, int rotateZ) {
    qDebug() << "Rotation changed to (" << rotateX << "," << rotateY << "," << rotateZ << ")";
    currentX = rotateX;
    currentY = rotateY;
    currentZ = rotateZ;
    update();
}

void MainView::setScale(int scale) {
    qDebug() << "Scale changed to " << scale;
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
