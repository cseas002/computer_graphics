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

void MainView::loadTexture(QString file, GLuint texturePtr) {
    QImage image = QImage(file);
    auto bytes = imageToBytes(image);
    glBindTexture(GL_TEXTURE_2D, texturePtr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes.data());

    // Maybe this will break the program
    glGenerateMipmap(GL_TEXTURE_2D);
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


    glGenTextures(1, &texture);
    createShaderProgramNormal();
    createShaderProgramPhong();
    createShaderProgramGouraud();
    loadMesh();
    loadTexture(":/textures/cat_diff.png", texture);

    // Initialize transformations
    updateProjectionTransform();
    updateModelTransforms();
}

void MainView::createShaderProgramNormal() {
    // Create shader program
    shaderProgramNormal.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                           ":/shaders/vertshader_normal.glsl");
    shaderProgramNormal.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                           ":/shaders/fragshader_normal.glsl");
    shaderProgramNormal.link();

    // Get the uniforms
    uniformModelViewTransformNormal = shaderProgramNormal.uniformLocation("modelViewTransform");
    uniformProjectionTransformNormal = shaderProgramNormal.uniformLocation("projectionTransform");
    uniformNormalTransformNormal= shaderProgramNormal.uniformLocation("normalTransform");
}

void MainView::createShaderProgramGouraud() {
    // Create shader program
    shaderProgramGouraud.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                           ":/shaders/vertshader_gouraud.glsl");
    shaderProgramGouraud.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                           ":/shaders/fragshader_gouraud.glsl");
    shaderProgramGouraud.link();

    // Get the uniforms
    uniformModelViewTransformGouraud = shaderProgramGouraud.uniformLocation("modelViewTransform");
    uniformProjectionTransformGouraud  = shaderProgramGouraud.uniformLocation("projectionTransform");
    uniformNormalTransformGouraud  = shaderProgramGouraud.uniformLocation("normalTransform");
    uniformLightPositionGouraud = shaderProgramGouraud.uniformLocation("lightPosition");
    uniformMaterialAmbientGouraud = shaderProgramGouraud.uniformLocation("materialAmbient");
    uniformMaterialDiffuseGouraud = shaderProgramGouraud.uniformLocation("materialDiffuse");
    uniformMaterialSpecularGouraud = shaderProgramGouraud.uniformLocation("materialSpecular");
    uniformMaterialSpecularExpomentGouraud = shaderProgramGouraud.uniformLocation("materialSpecularExponent");
    uniformLightColorGouraud = shaderProgramGouraud.uniformLocation("lightColor");
    uniformTextureGouraud = shaderProgramGouraud.uniformLocation("samplerUniform");
}

void MainView::createShaderProgramPhong() {
    // Create shader program
    shaderProgramPhong.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                           ":/shaders/vertshader_phong.glsl");
    shaderProgramPhong.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                           ":/shaders/fragshader_phong.glsl");
    shaderProgramPhong.link();

    // Get the uniforms
    uniformModelViewTransformPhong = shaderProgramPhong.uniformLocation("modelViewTransform");
    uniformProjectionTransformPhong = shaderProgramPhong.uniformLocation("projectionTransform");
    uniformNormalTransformPhong = shaderProgramPhong.uniformLocation("normalTransform");
    uniformLightPositionPhong = shaderProgramPhong.uniformLocation("lightPosition");
    uniformMaterialAmbientPhong = shaderProgramPhong.uniformLocation("materialAmbient");
    uniformMaterialDiffusePhong = shaderProgramPhong.uniformLocation("materialDiffuse");
    uniformMaterialSpecularPhong = shaderProgramPhong.uniformLocation("materialSpecular");
    uniformMaterialSpecularExpomentPhong = shaderProgramPhong.uniformLocation("materialSpecularExponent");
    uniformLightColorPhong = shaderProgramPhong.uniformLocation("lightColor");
    uniformTexturePhong = shaderProgramPhong.uniformLocation("samplerUniform");

}

void MainView::loadMesh() {
    Model model(":/models/cat.obj");
    QVector<QVector3D> vertexCoords = model.getVertices();

    QVector<float> meshData;
    meshData.reserve(2 * 3 * vertexCoords.size());

    auto normals = model.getNormals();
    auto textureCoords = model.getTextureCoords();

    for (int i = 0; i < vertexCoords.size(); i++)
    {
        meshData.append(vertexCoords[i].x());
        meshData.append(vertexCoords[i].y());
        meshData.append(vertexCoords[i].z());

        meshData.append(normals[i].x());
        meshData.append(normals[i].y());
        meshData.append(normals[i].z());

        meshData.append(textureCoords[i].x());
        meshData.append(textureCoords[i].y());



//        meshData.append(static_cast<float>(rand()) / RAND_MAX);
//        meshData.append(static_cast<float>(rand()) / RAND_MAX);
//        meshData.append(static_cast<float>(rand()) / RAND_MAX);
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<GLvoid*>(0));
    glEnableVertexAttribArray(0);

    // Set color coordinates to location 1
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // Set uv coordinates to location 2
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<GLvoid*>(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

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
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture);

    switch(shader) {
        case PHONG:
        default: {
            // Set the projection matrix
            shaderProgramPhong.bind();
            glUniformMatrix3fv(uniformNormalTransformPhong, 1, GL_FALSE, normalTransform.data());
            glUniformMatrix4fv(uniformProjectionTransformPhong, 1, GL_FALSE, projectionTransform.data());
            glUniformMatrix4fv(uniformModelViewTransformPhong, 1, GL_FALSE, meshTransform.data());

            float lightPosition[3] = {10, 10, 10};
            glUniform3fv(uniformLightPositionPhong, 1, lightPosition);

            glUniform1f(uniformMaterialAmbientPhong, 0.2);
            glUniform1f(uniformMaterialDiffusePhong, 0.6 * 0.8);
            glUniform1f(uniformMaterialSpecularPhong, 0.4 * 0.3);
            glUniform1f(uniformMaterialSpecularExpomentPhong, 1);

            float lightColor[3] = {0.5, 0.5, 0.5};
            glUniform3fv(uniformLightColorPhong, 1, lightColor);

            glUniform1i(uniformTexturePhong, 1);

            glBindVertexArray(meshVAO);
            glDrawArrays(GL_TRIANGLES, 0, meshSize);
            shaderProgramPhong.release();
            break;
        }
        case GOURAUD: {
            // Set the projection matrix
            shaderProgramGouraud.bind();
            glUniformMatrix3fv(uniformNormalTransformGouraud, 1, GL_FALSE, normalTransform.data());
            glUniformMatrix4fv(uniformProjectionTransformGouraud, 1, GL_FALSE, projectionTransform.data());
            glUniformMatrix4fv(uniformModelViewTransformGouraud, 1, GL_FALSE, meshTransform.data());

            float lightPosition[3] = {10, 10, 10};
            glUniform3fv(uniformLightPositionGouraud, 1, lightPosition);

            glUniform1f(uniformMaterialAmbientGouraud, 0.2);
            glUniform1f(uniformMaterialDiffuseGouraud, 0.6 * 0.8);
            glUniform1f(uniformMaterialSpecularGouraud, 0.4 * 0.3);
            glUniform1f(uniformMaterialSpecularExpomentGouraud, 1);

            float lightColor[3] = {0.5, 0.5, 0.5};
            glUniform3fv(uniformLightColorGouraud, 1, lightColor);

            glUniform1i(uniformTextureGouraud, 1);

            glBindVertexArray(meshVAO);
            glDrawArrays(GL_TRIANGLES, 0, meshSize);
            shaderProgramGouraud.release();
            break;
        }
        case NORMAL:
            // Set the projection matrix
            shaderProgramNormal.bind();
            glUniformMatrix3fv(uniformNormalTransformNormal, 1, GL_FALSE, normalTransform.data());
            glUniformMatrix4fv(uniformProjectionTransformNormal, 1, GL_FALSE, projectionTransform.data());
            glUniformMatrix4fv(uniformModelViewTransformNormal, 1, GL_FALSE, meshTransform.data());
            glBindVertexArray(meshVAO);
            glDrawArrays(GL_TRIANGLES, 0, meshSize);
            shaderProgramNormal.release();
            break;
    }




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
    meshTransform.scale(scale * 30);

    normalTransform = meshTransform.normalMatrix();
//    normalTransform = meshTransform.inverted().transposed();


    update();
}

void MainView::updateNormalTransform() {

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
    shader = shading;
    update();
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
