#include "./glview.h"

#include "mainwindow.h"
namespace my_viewer {
glView::glView(QWidget *parent) : QOpenGLWidget(parent) {}

glView::~glView() {}

void glView::paintGL() {
  glClearColor(controller_.backgroundColor.redF(),
               controller_.backgroundColor.greenF(),
               controller_.backgroundColor.blueF(), 1);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  projection();
  drawLines();
  if (controller_.circlePoints || controller_.squarePoints) {
    drawPoints();
  }
}

void glView::initializeGL() {
  glClearColor(controller_.backgroundColor.redF(),
               controller_.backgroundColor.greenF(),
               controller_.backgroundColor.blueF(), 1);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH);
}

void glView::resizeGL(int w, int h) {}

void glView::drawLines() {
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, controller_.getCoord().data());

  glColor3d(controller_.edgeColor.redF(), controller_.edgeColor.greenF(),
            controller_.edgeColor.blueF());

  glLineWidth(controller_.thicknessEdge);

  if (controller_.dashedEdge) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00F0);
  }

  glDrawElements(GL_LINES, controller_.amountIndexes(), GL_UNSIGNED_INT,
                 controller_.getIndexes().data());

  if (controller_.dashedEdge) {
    glDisable(GL_LINE_STIPPLE);
  }

  glDisableClientState(GL_VERTEX_ARRAY);
}

void glView::drawPoints() {
  glEnableClientState(GL_VERTEX_ARRAY);
  glPointSize(controller_.sizePoint);
  glColor3d(controller_.pointColor.redF(), controller_.pointColor.greenF(),
            controller_.pointColor.blueF());

  if (controller_.circlePoints) {
    glEnable(GL_POINT_SMOOTH);
  }
  glEnableClientState(GL_VERTEX_ARRAY);
  glDrawArrays(GL_POINTS, 0, controller_.getVertexes());

  if (controller_.circlePoints) {
    glDisable(GL_POINT_SMOOTH);
  }
  glDisableClientState(GL_VERTEX_ARRAY);
}

void glView::projection() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (controller_.centralProjection) {
    glFrustum(-1.2, 1.2, -1.2, 1.2, 3, 6);
    glTranslated(0, 0, -4);
  } else {
    glOrtho(-1.2, 1.2, -1.2, 1.2, -1.2, 1.2);
  }
}
}  // namespace my_viewer
