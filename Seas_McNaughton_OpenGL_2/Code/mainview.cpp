#include "mainview.h"
#include "model.h"
#include "vertex.h"

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

    destroyModelBuffers();
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

    connect(&debugLogger, SIGNAL(messageLogged(QOpenGLDebugMessage)),
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
    loadMesh();

    // Initialize transformations
    updateProjectionTransform();
    updateModelTransforms();
}

void MainView::createShaderProgram() {
    // Create shader program
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                           ":/shaders/vertshader.glsl");
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                           ":/shaders/fragshader.glsl");
    shaderProgram.link();

    // Get the uniforms
    uniformModelViewTransform = shaderProgram.uniformLocation("modelViewTransform");
    uniformProjectionTransform = shaderProgram.uniformLocation("projectionTransform");
}

void MainView::loadMesh() {
    Model model(":/models/cube.obj");
    QVector<QVector3D> vertexCoords = model.getVertices();

    QVector<float> meshData;
    meshData.reserve(2 * 3 * vertexCoords.size());

    for (auto coord : vertexCoords)
    {
        meshData.append(coord.x());
        meshData.append(coord.y());
        meshData.append(coord.z());
        meshData.append(static_cast<float>(rand()) / RAND_MAX);
        meshData.append(static_cast<float>(rand()) / RAND_MAX);
        meshData.append(static_cast<float>(rand()) / RAND_MAX);
    }

    meshSize = vertexCoords.size();

    // Generate VAO
    glGenVertexArrays(1, &meshVAO);
    glBindVertexArray(meshVAO);

    // Generate VBO
    glGenBuffers(1, &meshVBO);
    glBindBuffer(GL_ARRAY_BUFFER, meshVBO);

    // Write the data to the buffer
    glBufferData(GL_ARRAY_BUFFER, meshData.size() * sizeof(GLfloat), meshData.data(), GL_STATIC_DRAW);

    // Set vertex coordinates to location 0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(0));
    glEnableVertexAttribArray(0);

    // Set color coordinates to location 1
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
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

    shaderProgram.bind();

    // Set the projection matrix
    glUniformMatrix4fv(uniformProjectionTransform, 1, GL_FALSE, projectionTransform.data());
    glUniformMatrix4fv(uniformModelViewTransform, 1, GL_FALSE, meshTransform.data());

    glBindVertexArray(meshVAO);
    glDrawArrays(GL_TRIANGLES, 0, meshSize);

    shaderProgram.release();
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
    Q_UNUSED(newWidth)
    Q_UNUSED(newHeight)
    updateProjectionTransform();
}

void MainView::updateProjectionTransform() {
    float aspectRatio = static_cast<float>(width()) / static_cast<float>(height());
    projectionTransform.setToIdentity();
    projectionTransform.perspective(60.0F, aspectRatio, 0.2F, 20.0F);
}

void MainView::updateModelTransforms() {
    meshTransform.setToIdentity();
    meshTransform.translate(0.0F, 0.0F, -10.0F);
    meshTransform.rotate(QQuaternion::fromEulerAngles(rotation));
    meshTransform.scale(scale);

    update();
}

// --- OpenGL cleanup helpers

void MainView::destroyModelBuffers() {
    glDeleteBuffers(1, &meshVBO);
    glDeleteVertexArrays(1, &meshVAO);
}

// --- Public interface

void MainView::setRotation(int rotateX, int rotateY, int rotateZ) {
    rotation = { static_cast<float>(rotateX), static_cast<float>(rotateY), static_cast<float>(rotateZ) };
    updateModelTransforms();
}

void MainView::setScale(int newScale) {
    scale = static_cast<float>(newScale) / 100.0F;
    updateModelTransforms();
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