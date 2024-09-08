#ifndef CONTROLLER_H
#define CONTROLLER_H

#define GL_SILENCE_DEPRECATION
#include <QAction>
#include <QColor>
#include <QColorDialog>
#include <QFileDialog>
#include <QMainWindow>
#include <QMenuBar>
#include <QSettings>
#include <QTimer>
#include <QWidget>
#include <QtOpenGLWidgets>
#include <iostream>

#include "../model/facade.h"

namespace my_viewer {
class Controller {
 private:
  Facade facade_;

 public:
  Controller() {}
  Controller(const Controller& other) = default;
  Controller(Controller&& other) = default;
  ~Controller() {}
  Controller& operator=(const Controller& other) = default;

  bool Parser(std::string file);
  int getEdges();
  int getVertexes();
  void affine();
  bool adapterEmpty();
  int amountIndexes();
  std::vector<int>& getIndexes();
  std::vector<float>& getCoord();
  void saveConfig(QSettings* setting);
  void loadConfig(QSettings* setting);
  void newObj();

  QColor backgroundColor = QColor(255, 255, 244, 1),
         edgeColor = QColor(211, 168, 128, 1),
         pointColor = QColor(89, 135, 153, 1);

  float xyRot = 0, yzRot = 0, xzRot = 0, xTrans = 0, yTrans = 0, zTrans = 0,
        Scale = 1, thicknessEdge = 1, sizePoint = 5;
  bool circlePoints = false, squarePoints = false, dashedEdge = false,
       centralProjection = false;
};
}  // namespace my_viewer
#endif  // CONTROLLER_H
