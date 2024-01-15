#pragma once
#include <cstdint>
#include <QVector>
#include <bitset>
#include <string>
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include <QLineEdit>
#include "OpenGLWindow.h"


class OpenGLWindow;

class Visualizer : public QMainWindow
{
    Q_OBJECT

public:
    Visualizer(QWindow* parent = nullptr);
    ~Visualizer();

private:
    void setupUi();
    void openFileDialog();

private slots:
    void setCustomTime();
    void updateDigitalClock(int hours, int minutes, int seconds);

private:
    OpenGLWindow* mRenderer;
    QPushButton* mUploadButton;
    QPushButton* mSetTimeButton;
    QVector<GLfloat> mVertices;
    QVector<GLfloat> mColors;
    std::string mFileName;
 
    QLineEdit* mHourInput;
    QLineEdit* mMinuteInput;
    QLineEdit* mSecondInput;
    QLabel* mDigitalClockLabel;
    QTimer* mClockTimer;
 
   
   

};
