
# Shadow Simulation Project
## Overview
This project is a shadow simulation application that allows users to visualize and simulate shadows on 3D objects. The application loads STL files, representing 3D objects, and simulates shadows based on the position of a virtual sun. It utilizes Qt for the user interface and OpenGL for rendering.

## Features
### Load STL files: 
Users can browse and load STL files to visualize 3D objects.
### Set Custom Time:
Users can set a custom time (hours, minutes, seconds) to simulate shadows at different times of the day.
### Real-time Rendering:
The application provides real-time rendering of the 3D scene, updating the position of the sun and shadows dynamically.
## Project Structure
### Visualizer.cpp
#### Visualizer class:
Manages the user interface, including buttons for file browsing and setting custom time.
#### openFileDialog():
Handles the file browsing functionality and reads STL files using the ReadSTL class.
#### setCustomTime():
Handles the setting of custom time and updates the digital clock label.
#### updateDigitalClock():
Updates the digital clock label with the specified time.
### OpenGLWindow.cpp
#### OpenGLWindow class:
Manages the OpenGL rendering, including initializing shaders, handling mouse events, and drawing the 3D scene.
#### initializeGL():
Initializes OpenGL settings and shaders.
#### paintGL(): 
Renders the 3D scene, including the loaded STL file and a ground plane.
#### processTriangles():
Processes the triangles from the loaded STL file and updates the vertex and color data.
#### mouseMoveEvent():
Handles mouse movement for rotating the 3D scene.
#### wheelEvent(): 
Handles mouse wheel events for zooming in and out.
#### mousePressEvent(): 
Handles mouse press events for adjusting the position of the virtual sun.
#### sunTime():
Updates the position of the virtual sun based on the specified time.
## Dependencies
### Qt:
Used for the user interface.
### OpenGL:
Used for rendering the 3D scene.
### STL file reader:
The project relies on the ReadSTL class for reading STL files.
## Building and Running
Make sure you have Qt and OpenGL installed on your system.
Open the project in your preferred IDE that supports Qt.
Build and run the project.
Usage
Launch the application.
Click "Browse STL" to load a 3D object in STL format.
Set the desired time using the input fields for hours, minutes, and seconds.
Click "Set Time" to simulate shadows at the specified time.
Interact with the 3D scene using mouse movements and wheel scrolling.
Feel free to explore and experiment with different STL files and custom time settings to observe the shadow simulations in the 3D scene.
## UI 

![Screenshot (185)](https://github.com/mvanadana/Light_Simulation/assets/149364066/87d9fd6a-8522-4dd1-b85b-7997d4c468fb)

![Screenshot (187)](https://github.com/mvanadana/Light_Simulation/assets/149364066/bd65c453-5da1-4738-a005-8dc1af7e4ce9)


![Screenshot (186)](https://github.com/mvanadana/Light_Simulation/assets/149364066/7659b4fb-6f0a-446a-9d07-2357529a2faa)
