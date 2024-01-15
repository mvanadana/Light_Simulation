// OpenGLWindow.h
#pragma once

#include "Triangle.h"
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <vector>
#include <QOpenGLVertexArrayObject>
#include <QMatrix4x4>

class QOpenGLTexture;
class QOpenGLShader;
class QOpenGLShaderProgram;
class QOpenGLPaintDevice;

class OpenGLWindow : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
signals:
    void shapeUpdate();

public:
    OpenGLWindow(const QColor& background, QMainWindow* parent);
    ~OpenGLWindow();

    void mouseMoveEvent(QMouseEvent* event);
    void processTriangles(const std::vector<Triangle>& triangles);
    void wheelEvent(QWheelEvent* event);
    void updateData(const QVector<GLfloat>& vertices, const QVector<GLfloat>& colors);
    QString readShader(QString filepath);
    void mousePressEvent(QMouseEvent* event);
    void sunTime(int hours,int minutes,int sec);
  

protected:
    void paintGL() override;
    void initializeGL() override;
    //void paintEvent(QPaintEvent* event) override;

private:
    void reset();
    void drawPlane();
    void setupVertexAttribs();
    
private:
    QOpenGLShader* mVshader = nullptr;
    QOpenGLShader* mFshader = nullptr;
    QOpenGLShaderProgram* mProgram = nullptr;
  
    QOpenGLBuffer mVbo;
    int mVertexAttr;
    int mNormalAttr;
    int mMatrixUniform;
    int m_lightPositionUniform;
    int mLightColorLoc;
    QColor mBackground;
    QMetaObject::Connection mContextWatchConnection;
    GLint m_posAttr = 0;
    GLint m_colAttr = 0;
    GLint m_normals = 0;
    GLint m_matrixUniform_proj = 0;
    GLint m_matrixUniform_view = 0;
    GLint m_matrixUniform_model = 0;
    
    QVector<QVector2D> mPixelVertices;
    int m_lightPosLoc = 0;
    int m_normalMatrixLoc = 0;
    QVector<GLfloat> mVertices;
    QVector<GLfloat> mColors;
    QVector<GLfloat> mNormals;
    float mZoomFactor = 1.0f;
    QQuaternion mRotationAngle;
    QPoint mPosition;
  
    int mNormalMatrixLoc = 0;
    int mLightPosLoc = 0;
   

 
    QPoint mLastPos;
    QOpenGLBuffer mLogoVbo;
    bool mFlag = true;
    int mCount = 0;
    int mSceneWidth;
    int mSceneHeight;
    QVector3D mNewpos;
    QVector3D mNewpos1;
    QVector3D mNewpos2;
    QVector3D mNewpos3;

   
    

   

};
