#ifndef GLVIEW_H
#define GLVIEW_H

#include "controller/controller.h"

namespace Ui {
class glView;
}
namespace my_viewer {

class glView : public QOpenGLWidget {
  Q_OBJECT

 public:
  glView(QWidget *parent = nullptr);
  ~glView();

  Controller controller_;
  QString filename;

  // protected:
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int w, int h) override;
  void drawLines();
  void drawPoints();
  void projection();

 private:
  Ui::glView *ui;
};
}  // namespace my_viewer

#endif  // GLVIEW_H
