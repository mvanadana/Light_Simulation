#include "stdafx.h"
#include "OpenGLWindow.h"
#include <QOpenGLContext>
#include <QOpenGLPaintDevice>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFunctions>
#include <QPainter>
#include <QFileInfo>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <QMatrix4x4>


OpenGLWindow::OpenGLWindow(const QColor& background, QMainWindow* parent)
    : mBackground(background)
{
    setParent(parent);
    setMinimumSize(1300, 784);
}

OpenGLWindow::~OpenGLWindow()
{
    reset();
}

void OpenGLWindow::reset()
{
    // And now release all OpenGL resources.
    makeCurrent();
    delete mProgram;
    mProgram = nullptr;
    delete mVshader;
    mVshader = nullptr;
    delete mFshader;
    mFshader = nullptr;
    mVbo.destroy();
    doneCurrent();

    QObject::disconnect(mContextWatchConnection);
}

void OpenGLWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(135.0f / 255.0f, 206.0f / 255.0f, 235.0f / 255.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    mProgram->bind();
    QMatrix4x4 matrix_proj;
    QMatrix4x4 matrix_view;
    QMatrix4x4 matrix_model;

    // matrix_model.setToIdentity();
    matrix_model.rotate(mRotationAngle);
   
    
    matrix_proj.ortho(-60, 60,0, 60, -100, 100);

    //matrix_view.setToIdentity();
    matrix_view.translate(0, 0, -2);
    matrix_view.scale(mZoomFactor);
    //  matrix_view.setToIdentity();
    matrix_view.lookAt(mNewpos1, mNewpos2, mNewpos3);
    drawPlane();
 
    mProgram->setUniformValue(m_matrixUniform_proj, matrix_proj);
    mProgram->setUniformValue(m_matrixUniform_view, matrix_view);
    mProgram->setUniformValue(m_matrixUniform_model, matrix_model);
    mProgram->setUniformValue(mLightPosLoc, mNewpos);




    QMatrix3x3 normalMatrix = matrix_model.normalMatrix();
    mProgram->setUniformValue(mNormalMatrixLoc, normalMatrix);

    GLfloat* verticesData = mVertices.data();
    GLfloat* normalData = mNormals.data();
    GLfloat* colorData = mColors.data();


    glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, verticesData);
    glVertexAttribPointer(m_normals, 3, GL_FLOAT, GL_FALSE, 0, normalData);
    glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, colorData);
    glEnableVertexAttribArray(m_posAttr);
    glEnableVertexAttribArray(m_normals);
    glEnableVertexAttribArray(m_colAttr);


    if (mFlag) {
        glDrawArrays(GL_TRIANGLES, 0, mVertices.size() / 3);
    }
    else {
        glDrawArrays(GL_LINE_LOOP, 0, mVertices.size() / 3);
    }
    
}


void OpenGLWindow::initializeGL()
{

    initializeOpenGLFunctions();

    glEnableVertexAttribArray(m_posAttr);
    glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, nullptr);


    QString vertexShaderSource = readShader("shaders/VertexShaders.glsl");
    QString fragmentShaderSource = readShader("shaders/FragmentShaders.glsl");
    setMouseTracking(true);
    mProgram = new QOpenGLShaderProgram(this);
    mProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    mProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    mProgram->bindAttributeLocation("vertex", 0);
    mProgram->bindAttributeLocation("normal", 1);
   


    mProgram->link();

    m_posAttr = mProgram->attributeLocation("posAttr");
    m_normals = mProgram->attributeLocation("normalAttr");
    m_colAttr = mProgram->attributeLocation("colAttr");
    m_matrixUniform_proj = mProgram->uniformLocation("u_ProjMatrix");
    m_matrixUniform_view = mProgram->uniformLocation("u_viewMatrix");
    m_matrixUniform_model = mProgram->uniformLocation("u_modelMatrix");
    m_normalMatrixLoc = mProgram->uniformLocation("normalMatrix");
    mLightPosLoc = mProgram->uniformLocation("lightPos");

}
void OpenGLWindow::processTriangles(const std::vector<Triangle>& triangles)
{

    mVertices.clear();
    mColors.clear();


    for (const auto& triangle : triangles)
    {
        // Assuming you have functions in Triangle to retrieve vertices and normal
        Point3D normal = triangle.normal();
        Point3D p1 = triangle.p1();
        Point3D p2 = triangle.p2();
        Point3D p3 = triangle.p3();

        // Add your logic to update mVertices and mColors based on the triangle data

        mVertices << p1.x() * 0.1 << p1.y() * 0.1 << p1.z() * 0.1;
        mColors << 1.0f << 1.0f << 0.0f;
        mVertices << p2.x() * 0.1 << p2.y() * 0.1 << p2.z() * 0.1;
        mColors << 1.0f << 1.0f << 1.0f;
        mVertices << p3.x() * 0.1 << p3.y() * 0.1 << p3.z() * 0.1;
        mColors << 1.0f << 0.0f << 1.0f;

        mNormals << normal.x() << normal.y() << normal.z();
     
    }

    emit shapeUpdate();
}

void OpenGLWindow::mouseMoveEvent(QMouseEvent* event) {
    int dx = event->x() - mPosition.x();
    int dy = event->y() - mPosition.y();

    if (event->buttons() & Qt::LeftButton) {
        QQuaternion rotX = QQuaternion::fromAxisAndAngle(0.0f, 1.0f, 0.0f, 0.5f * dx);
        QQuaternion rotY = QQuaternion::fromAxisAndAngle(1.0f, 0.0f, 0.0f, 0.5f * dy);

        mRotationAngle = rotX * rotY * mRotationAngle;
        update();
    }
    mPosition = event->pos();
}

void OpenGLWindow::wheelEvent(QWheelEvent* event)
{
    int delta = event->angleDelta().y();

    // Adjust the zoom factor based on the mouse wheel movement
    if (delta > 0) {
        // Zoom in
        mZoomFactor *= 1.1f;
    }
    else {
        // Zoom out
        mZoomFactor /= 1.1f;
    }

    update();
}
void OpenGLWindow::updateData(const QVector<GLfloat>& vertices, const QVector<GLfloat>& colors)
{
    mVertices = vertices;
    mColors = colors;
    update();
}
QString OpenGLWindow::readShader(QString filepath)
{
    QFile file(filepath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return "Invalid file";
    QTextStream stream(&file);
    QString line = stream.readLine();
    while (!stream.atEnd())
    {
        line.append(stream.readLine());
    }
    return line;
}
void OpenGLWindow::drawPlane() {

    // Define vertices and colors for a ground plane
    QVector<GLfloat> planeVertices = {
        -5.0f, 0.0f, -5.0f,   
         5.0f, 0.0f, -5.0f,   
         5.0f, 0.0f,  5.0f,   
        -5.0f, 0.0f,  5.0f  
    };

    QVector<GLfloat> groundColors = {
        0.5f, 0.35f, 0.05f, 
        0.5f, 0.35f, 0.05f, 
        0.5f, 0.35f, 0.05f, 
        0.5f, 0.35f, 0.05f  
    };

    // Vertex Array Object (VAO) setup
    QOpenGLVertexArrayObject groundVAO;
    groundVAO.create();
    groundVAO.bind();

    // Vertex Buffer Objects (VBOs) setup
    QOpenGLBuffer groundVBO(QOpenGLBuffer::VertexBuffer);
    groundVBO.create();
    groundVBO.bind();
    groundVBO.setUsagePattern(QOpenGLBuffer::StaticDraw);

    // Allocate memory for vertex data and copy data
    int vertexCount = planeVertices.size() / 3;
    groundVBO.allocate(nullptr, vertexCount * (3 + 3) * sizeof(GLfloat));
    groundVBO.write(0, planeVertices.constData(), vertexCount * 3 * sizeof(GLfloat));
    groundVBO.write(vertexCount * 3 * sizeof(GLfloat), groundColors.constData(), vertexCount * 3 * sizeof(GLfloat));

    // Enable vertex attributes
    glEnableVertexAttribArray(m_posAttr);
    glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), nullptr);

    glEnableVertexAttribArray(m_colAttr);
    glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void*>(3 * sizeof(GLfloat)));

    // Set the ground color uniform
    mProgram->setUniformValue(m_colAttr, QVector3D(0.0f, 0.0f, 1.0f)); // Blue color for the ground

    // Draw the ground plane
    glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);

    // Clean up
    groundVBO.release();
    groundVAO.release();
}

void OpenGLWindow::setupVertexAttribs()
{
    mLogoVbo.bind();
    QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
    f->glEnableVertexAttribArray(0);
    f->glEnableVertexAttribArray(1);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
        nullptr);
    f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
        reinterpret_cast<void*>(3 * sizeof(GLfloat)));
    mLogoVbo.release();
}


void OpenGLWindow::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {


        float mouseX = static_cast<float>(event->x()) / width(); // Normalize mouse x-coordinate
        float mouseY = static_cast<float>(event->y()) / height(); // Normalize mouse y-coordinate
        
         // Convert mouse coordinates to a 3D position in your scene
        float sceneX = mouseX * mSceneWidth - mSceneWidth / 2.0f;
        float sceneY = mouseY * mSceneHeight - mSceneHeight / 2.0f;

        mNewpos = QVector3D(sceneX, sceneY, -100);
    
        
        update(); // Trigger a redraw
    }   
}


void OpenGLWindow::sunTime(int hours, int min, int sec)
{
    // Convert time to seconds
    double totalSeconds = hours * 3600 + min * 60 + sec;

    // Restrict daylight to 6 AM to 6 PM
    if (hours < 6 || hours >= 19)
    {
        // Set a far-away position for the sun during the night
        float sunX = 0.0f; // Adjust the X position as needed during the night
        float sunY = 0.0f; // Adjust the Y position as needed during the night
        float sunZ = 500.0f; // Far away from the screen
        mNewpos = QVector3D(-sunX, -sunY, 500);
        update();
    }
    else
    {
        if (hours == 6)
        {
            
            float sceneX = -3.10948e+08;
            float sceneY  = -3.96369e+08;
            mNewpos = QVector3D(sceneX, sceneY, -70);
            update();

        }
        if (hours == 7)
        {
            float sceneX = -3.53703e+08;
            float sceneY = -2.70691e+08;
            mNewpos = QVector3D(sceneX, sceneY, -70);
            update();
        }
        if (hours == 8)
        {
            float sceneX = -3.75081e+08;
            float sceneY = -7.08953e+07;
            mNewpos = QVector3D(sceneX, sceneY, -70);
            update();
        }
        
         if (hours == 9)
         {
            float sceneX = -3.39451e+08;
            float sceneY = 9.9898e+07;
            mNewpos = QVector3D(sceneX, sceneY, -70);
            update();

          }

         if (hours == 10)
         {
             float sceneX = -3.00583e+08;
             float sceneY = 2.80359e+08;
             mNewpos = QVector3D(sceneX, sceneY, -70);
             update();

         }
         if (hours == 11)
         {
             float sceneX = -2.47463e+08;
             float sceneY = 3.71663e+08;
             mNewpos = QVector3D(sceneX, sceneY, -70);
             update();

         }
         if (hours == 12)
         {
             float sceneX = -4.98812e+07;
             float sceneY = 4.0174e+08;
             mNewpos = QVector3D(sceneX, sceneY, -70);
             update();

         }
         if (hours == 13)
         {
             float sceneX = 1.27618e+08;
             float sceneY = 3.7596e+08;
             mNewpos = QVector3D(sceneX, sceneY, -70);
             update();

         }
         if (hours == 14)
         {
             float sceneX = 2.17664e+08;
             float sceneY = 2.66395e+08;
             mNewpos = QVector3D(sceneX, sceneY, -70);
             update();

         }
         if (hours == 15)
         {
             float sceneX = 3.00583e+08;
             float sceneY = 1.39642e+08;
             mNewpos = QVector3D(sceneX, sceneY, -70);
             update();

         }
         if (hours == 16)
         {
             float sceneX = 3.22608e+08;
             float sceneY = 1.50384e+07;
             mNewpos = QVector3D(sceneX, sceneY, -70);
             update();

         }
         if (hours == 17)
         {
             float sceneX = 3.30382e+08;
             float sceneY = -7.19695e+07;
             mNewpos = QVector3D(sceneX, sceneY, -70);
             update();

         }
         if (hours == 18)
         {
             float sceneX = 3.09004e+08;
             float sceneY = -2.21279e+08;
             mNewpos = QVector3D(sceneX, sceneY, -70);
             update();

         }
         if (hours == 18 && min == 30)
         {
             float sceneX = 2.71432e+08;
             float sceneY = -3.32993e+08;
             mNewpos = QVector3D(sceneX, sceneY, -70);
             update();

         }

    }

    // Trigger a redraw to reflect the updated sun position
    update();
}



