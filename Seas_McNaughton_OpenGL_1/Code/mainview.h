#ifndef MAINVIEW_H
#define MAINVIEW_H

#include "model.h"
#include "ShapeVertice.h"
#include <QKeyEvent>
#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLDebugLogger>
#include <QOpenGLShaderProgram>
#include <QTimer>
#include <QVector3D>
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

protected:
    void initializeGL();
    void resizeGL(int newWidth, int newHeight);
    void paintGL();
    void transformShape(QMatrix4x4 matrix, float x, float y, float z);

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
    void onMessageLogged( QOpenGLDebugMessage Message );

private:
    QOpenGLDebugLogger debugLogger;
    QTimer timer; // timer used for animation

    QOpenGLShaderProgram program;
<<<<<<< HEAD
    GLuint cubeVBO, cubeVAO, pyramidVBO, pyramidVAO, sphereVBO, sphereVAO;
    QMatrix4x4 model_mat, view_mat, proj_mat;
    int model_mat_location, view_mat_location, proj_mat_location;
    float currentScale = 1;
    int currentX = 0, currentY = 0, currentZ  = 0;
    QVector3D currentRotation = QVector3D(0, 0, 0);

    QVector<QVector3D> sphere3DVector;
=======
    GLuint cubeVBO, cubeVAO, pyramidVBO, pyramidVAO;
    QMatrix4x4 cubeMatrix, pyramidMatrix, projection;
    GLint cubeModelLocation, cubeProjectLocation, pyramidModelLocation, pyramidProjectLocation;

>>>>>>> 4eb9ba93318fd2f4e8f41e718f4317fcb251e8fd

    void createShaderProgram();
};

#endif // MAINVIEW_H
