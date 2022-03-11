#ifndef MAINVIEW_H
#define MAINVIEW_H

#include "model.h"

#include <QKeyEvent>
#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLDebugLogger>
#include <QOpenGLShaderProgram>
#include <QTimer>
#include <QVector3D>
#include <QMatrix4x4>
#include <memory>


class MainView : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core {
    Q_OBJECT

public:
    enum ShadingMode : GLuint {
        PHONG = 0, NORMAL, GOURAUD
    };

    MainView(QWidget *parent = 0);
    ~MainView();

    // Functions for widget input events
    void setRotation(int rotateX, int rotateY, int rotateZ);
    void setScale(int scale);
    void setShadingMode(ShadingMode shading);
    QVector<quint8> imageToBytes(QImage image);

protected:
    void initializeGL();
    void resizeGL(int newWidth, int newHeight);
    void paintGL();

    // Functions for keyboard input events
    void keyPressEvent(QKeyEvent *ev);
    void keyReleaseEvent(QKeyEvent *ev);

    // Function for mouse input events
    void mouseDoubleClickEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    void wheelEvent(QWheelEvent *ev);

private slots:
    void onMessageLogged(QOpenGLDebugMessage Message);

private:
    QOpenGLDebugLogger debugLogger;
    QTimer timer; // timer used for animation

    QOpenGLShaderProgram shaderProgramNormal, shaderProgramGouraud, shaderProgramPhong;
    GLint uniformModelViewTransformNormal, uniformModelViewTransformGouraud, uniformModelViewTransformPhong;

    GLint uniformLightPositionGouraud, uniformMaterialAmbientGouraud, uniformMaterialDiffuseGouraud,
          uniformMaterialSpecularGouraud, uniformMaterialSpecularExpomentGouraud, uniformLightColorGouraud, uniformTextureGouraud;

    GLint uniformLightPositionPhong, uniformMaterialAmbientPhong, uniformMaterialDiffusePhong,
          uniformMaterialSpecularPhong, uniformMaterialSpecularExpomentPhong, uniformLightColorPhong, uniformTexturePhong;

    GLuint texture;


    GLint uniformProjectionTransformNormal, uniformProjectionTransformGouraud, uniformProjectionTransformPhong;
    GLint uniformNormalTransformNormal, uniformNormalTransformGouraud, uniformNormalTransformPhong;
    ShadingMode shader;

    // Mesh values
    GLuint meshVAO;
    GLuint meshVBO;
    GLuint meshSize;
    QMatrix4x4 meshTransform;

    // Transforms
    float scale = 1.0F;
    QVector3D rotation;
    QMatrix4x4 projectionTransform;

    // Normals
    QMatrix3x3 normalTransform;

    void createShaderProgramNormal();
    void createShaderProgramGouraud();
    void createShaderProgramPhong();
    void loadMesh();

    void destroyModelBuffers();

    void updateProjectionTransform();
    void updateModelTransforms();
    void updateNormalTransform();
    void loadTexture(QString file, GLuint texturePtr);
};

#endif // MAINVIEW_H
