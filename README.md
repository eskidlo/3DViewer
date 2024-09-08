# 3D Viewer

## Overview 
This 3D Viewer implemented in C++ using the Qt graphic library. It allows you to load and manipulate 3D wireframe models from .obj files. 

## Main Features
- **Model Loading:** Load a wireframe model from an .obj file (supports vertices and surface lists only).
- **Translation:** Translate the model along the X, Y, and Z axes.
- **Rotation:** Rotate the model around the X, Y, and Z axes.
- **Scaling:** Scale the model proportionally.

## Customization
The program allows to customize the following options:

- **Projection Type:** Select between parallel and central projections.
- **Edge Appearance:** Customize the edge type (solid, dashed), color, and thickness.
- **Vertex Display:** Choose the display method (none, circle, square), and adjust the color and size of vertices.
- **Background Color:** Set the viewer's background color.

Although all settings are automatically saved and retained between program restarts. 

## Installation 
To install either version of the calculator, navigate to the src directory and run the following command: 

```bash
make install     
```

## Uninstallation 
To uninstall either version of the calculator, navigate to the src directory and run the following command: 

```bash
make uninstall
```    