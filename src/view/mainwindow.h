#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../extra/gif/src/gifimage/qgifimage.h"
#include "./glview.h"
#include "controller/controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace my_viewer {
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  QGifImage *gif;
  QTimer *timer;
  QString gifName;
  int counter;
  ~MainWindow();

 private slots:

  void on_openFile_clicked();
  void Load();

  // affine
  void on_rotation_xy_textChanged(const QString &arg1);
  void on_rotation_xz_textChanged(const QString &arg1);
  void on_rotation_yz_textChanged(const QString &arg1);
  void on_trans_x_textChanged(const QString &arg1);
  void on_trans_y_textChanged(const QString &arg1);
  void on_trans_z_textChanged(const QString &arg1);
  void on_scale_textChanged(const QString &arg1);

  // parametres
  void on_dashed_edge_clicked();
  void on_solid_edge_clicked();
  void on_thickness_edge_textChanged(const QString &arg1);
  void on_size_point_textChanged(const QString &arg1);
  void on_none_point_clicked();
  void on_circle_point_clicked();
  void on_square_point_clicked();
  void on_central_clicked();
  void on_parallel_clicked();
  void on_colorback_clicked();
  void on_coloredge_clicked();
  void on_colorvert_clicked();
  void on_save_image_clicked();

  void on_save_gif_clicked();
  void creating_gif();

 private:
  Ui::MainWindow *ui;
  glView *glview;
  QSettings *settings_;
};
}  // namespace my_viewer

#endif  // MAINWINDOW_H
