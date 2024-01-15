#include "stdafx.h"
#include <QFileDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QTime>
#include "Visualizer.h"
#include "ReadSTL.h"
#include "OpenGLWindow.h"

Visualizer::Visualizer(QWindow* parent)
{
    setupUi();
    // Connect the buttons to their respective slots
    connect(mUploadButton, &QPushButton::clicked, this, &Visualizer::openFileDialog);
    connect(mSetTimeButton, &QPushButton::clicked, this, &Visualizer::setCustomTime);
    
}

Visualizer::~Visualizer()
{
}
void Visualizer::setupUi()
{
    resize(1530, 785);

    setWindowTitle(QCoreApplication::translate("Shadow Simulation", nullptr));

    // Set window title
    setWindowTitle("Shadow Simulation");

    mUploadButton = new QPushButton(this);
    mUploadButton->setObjectName("uploadButton");
    mUploadButton->setText("Browse STL");
    mUploadButton->setGeometry(QRect(1300, 50, 200, 30));
    mUploadButton->setStyleSheet("QPushButton {"
        "    background-color: #4CAF50;"  // Green background
        "    color: white;"
        "    border: 1px solid #4CAF50;"
        "    border-radius: 5px;"
        "    padding: 5px;"
        "}");

    // Create input fields for hours, minutes, and seconds
    mHourInput = new QLineEdit(this);
    mHourInput->setObjectName("hourInput");
    mHourInput->setPlaceholderText("Hours");
    mHourInput->setGeometry(QRect(1300, 300, 60, 30));
    mHourInput->setStyleSheet("QLineEdit {"
        "    border: 1px solid #4CAF50;"  // Green border
        "    border-radius: 5px;"
        "    padding: 5px;"
        "}");

    mMinuteInput = new QLineEdit(this);
    mMinuteInput->setObjectName("minuteInput");
    mMinuteInput->setPlaceholderText("Minutes");
    mMinuteInput->setGeometry(QRect(1360, 300, 60, 30));
    mMinuteInput->setStyleSheet("QLineEdit {"
        "    border: 1px solid #4CAF50;"  // Green border
        "    border-radius: 5px;"
        "    padding: 5px;"
        "}");

    mSecondInput = new QLineEdit(this);
    mSecondInput->setObjectName("secondInput");
    mSecondInput->setPlaceholderText("Seconds");
    mSecondInput->setGeometry(QRect(1420, 300, 60, 30));
    mSecondInput->setStyleSheet("QLineEdit {"
        "    border: 1px solid #4CAF50;"  // Green border
        "    border-radius: 5px;"
        "    padding: 5px;"
        "}");

    // Create a button to set the custom time
    mSetTimeButton = new QPushButton(this);
    mSetTimeButton->setObjectName("setTimeButton");
    mSetTimeButton->setText("Set Time");
    mSetTimeButton->setGeometry(QRect(1300, 350, 140, 30));
    mSetTimeButton->setStyleSheet("QPushButton {"
        "    background-color: #4CAF50;"  // Green background
        "    color: white;"
        "    border: 1px solid #4CAF50;"
        "    border-radius: 5px;"
        "    padding: 5px;"
        "}");

    mRenderer = new OpenGLWindow(Qt::black, this);

    // Create and configure the digital clock label
    mDigitalClockLabel = new QLabel(this);
    mDigitalClockLabel->setGeometry(QRect(1300, 100, 250, 150));
    mDigitalClockLabel->setStyleSheet("QLabel {"
        "    font-size: 30px;"
        "    color: #FFFFFF;"        // White text
        "    background-color: #000000;"  // Black background
        "    border: 2px solid #666666;"
        "    border-radius: 10px;"
        "    padding: 5px;"
        "}");

    
}


void Visualizer::openFileDialog()
{
    QString qFileName = QFileDialog::getOpenFileName(this, tr("Open STL File"), "", tr("STL Files (*.stl);;All Files (*)"));

    if (!qFileName.isEmpty()) {
        std::string fileName = qFileName.toStdString();

        // Use the Reader class to read the STL file and create Triangle objects
        ReadSTL reader;
        std::vector<Triangle> triangles;

        reader.read(fileName, triangles);

        // Now, you can process the triangles as needed. 
      
        mRenderer->processTriangles(triangles);

        // emit signal to notify OpenGLWindow about the new file
        emit mRenderer->shapeUpdate();
    }
}


void Visualizer::setCustomTime()
{
    int hours = mHourInput->text().toInt();
    int minutes = mMinuteInput->text().toInt();
    int seconds = mSecondInput->text().toInt();

    updateDigitalClock(hours, minutes, seconds);
    mRenderer->sunTime(hours, minutes, seconds);
    
   
}
void Visualizer::updateDigitalClock(int hours, int minutes, int seconds)
{
    // Set the specified hours, minutes, and seconds
    QTime currentTime(hours, minutes, seconds);

    // Format the time as HH:mm:ss
    QString formattedTime = currentTime.toString("hh:mm:ss");

    // Update the digital clock label text
    mDigitalClockLabel->setText(formattedTime);
}