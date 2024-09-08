#include "mainwindow.h"

#include "./ui_mainwindow.h"

namespace my_viewer {
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setWindowTitle("3D_Viewer");
  settings_ = new QSettings(QApplication::applicationDirPath() + "/config",
                            QSettings::IniFormat, this);
  Load();
}

MainWindow::~MainWindow() {
  ui->view->controller_.saveConfig(settings_);
  delete settings_;
  delete ui;
}

void MainWindow::on_openFile_clicked() {
  ui->label->setText("");
  bool check = false;
  QString fileName =
      QFileDialog::getOpenFileName(this, "Open a file", "/Users", "*.obj", 0,
                                   QFileDialog::DontUseNativeDialog);
  check = ui->view->controller_.Parser(fileName.toStdString());
  ui->view->update();
  if (check) {
    ui->label->setText(ui->label->text() + fileName.split('/').last() + ';');
    ui->label->setText(ui->label->text() + " Number of edges: " +
                       QString::number(ui->view->controller_.getEdges()) + ';');
    ui->label->setText(ui->label->text() + " Number of vertices: " +
                       QString::number(ui->view->controller_.getVertexes()));
  } else {
    ui->label->setText("ERROR!!!");
  }
}

void MainWindow::on_rotation_xy_textChanged(const QString &arg1) {
  if (!ui->view->controller_.adapterEmpty()) {
    ui->view->controller_.xyRot = (M_PI * ui->rotation_xy->value()) / 180;
    ui->view->controller_.affine();
    ui->view->update();
  }
}

void MainWindow::on_rotation_xz_textChanged(const QString &arg1) {
  if (!ui->view->controller_.adapterEmpty()) {
    ui->view->controller_.xzRot = (M_PI * ui->rotation_xz->value()) / 180;
    ui->view->controller_.affine();
    ui->view->update();
  }
}

void MainWindow::on_rotation_yz_textChanged(const QString &arg1) {
  if (!ui->view->controller_.adapterEmpty()) {
    ui->view->controller_.yzRot = (M_PI * ui->rotation_yz->value()) / 180;
    ui->view->controller_.affine();
    ui->view->update();
  }
}

void MainWindow::on_trans_x_textChanged(const QString &arg1) {
  if (!ui->view->controller_.adapterEmpty()) {
    ui->view->controller_.xTrans = ui->trans_x->value();
    ui->view->controller_.affine();
    ui->view->update();
  }
}

void MainWindow::on_trans_y_textChanged(const QString &arg1) {
  if (!ui->view->controller_.adapterEmpty()) {
    ui->view->controller_.yTrans = ui->trans_y->value();
    ui->view->controller_.affine();
    ui->view->update();
  }
}

void MainWindow::on_trans_z_textChanged(const QString &arg1) {
  if (!ui->view->controller_.adapterEmpty()) {
    ui->view->controller_.zTrans = ui->trans_z->value();
    ui->view->controller_.affine();
    ui->view->update();
  }
}

void MainWindow::on_scale_textChanged(const QString &arg1) {
  if (!ui->view->controller_.adapterEmpty()) {
    ui->view->controller_.Scale = ui->scale->value();
    ui->view->controller_.affine();
    ui->view->update();
  }
}

void MainWindow::on_dashed_edge_clicked() {
  ui->view->controller_.dashedEdge = true;
  ui->view->update();
}

void MainWindow::on_solid_edge_clicked() {
  ui->view->controller_.dashedEdge = false;
  ui->view->update();
}

void MainWindow::on_thickness_edge_textChanged(const QString &arg1) {
  ui->view->controller_.thicknessEdge = ui->thickness_edge->value();
  ui->view->update();
}

void MainWindow::on_size_point_textChanged(const QString &arg1) {
  ui->view->controller_.sizePoint = ui->size_point->value();
  ui->view->update();
}

void MainWindow::on_none_point_clicked() {
  ui->view->controller_.circlePoints = false;
  ui->view->controller_.squarePoints = false;
  ui->view->update();
}

void MainWindow::on_circle_point_clicked() {
  ui->view->controller_.circlePoints = true;
  ui->view->controller_.squarePoints = false;
  ui->view->update();
}

void MainWindow::on_square_point_clicked() {
  ui->view->controller_.circlePoints = false;
  ui->view->controller_.squarePoints = true;
  ui->view->update();
}

void MainWindow::on_parallel_clicked() {
  ui->view->controller_.centralProjection = false;
  ui->view->update();
}

void MainWindow::on_central_clicked() {
  ui->view->controller_.centralProjection = true;
  ui->view->update();
}

void MainWindow::on_colorback_clicked() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Set Edges` Color");
  if (color.isValid()) {
    ui->view->controller_.backgroundColor = color;
    ui->view->update();
  }
}

void MainWindow::on_coloredge_clicked() {
  QColor edge = QColorDialog::getColor(Qt::white, this, "Set Edges` Color");
  if (edge.isValid()) {
    ui->view->controller_.edgeColor = edge;
    ui->view->update();
  }
}

void MainWindow::on_colorvert_clicked() {
  QColor vert = QColorDialog::getColor(Qt::white, this, "Set Edges` Color");
  if (vert.isValid()) {
    ui->view->controller_.pointColor = vert;
    ui->view->update();
  }
}

void MainWindow::Load() {
  ui->view->controller_.loadConfig(settings_);
  ui->size_point->setValue(ui->view->controller_.sizePoint);
  ui->thickness_edge->setValue(ui->view->controller_.thicknessEdge);
}

void MainWindow::on_save_image_clicked() {
  QString selectedFilter;
  QString saveAs = QFileDialog::getSaveFileName(
      this, tr("save as"), "/Users", tr(".bmp;; .jpg"), &selectedFilter,
      QFileDialog::DontUseNativeDialog);
  ui->view->grab().save(saveAs + selectedFilter);
}

void MainWindow::on_save_gif_clicked() {
  gif = new QGifImage();
  ui->save_gif->setEnabled(0);
  counter = 0;
  timer = new QTimer();
  QString selectedFilter;
  QString saveAs = QFileDialog::getSaveFileName(
      this, tr("save as"), "/Users", tr(".gif"), &selectedFilter,
      QFileDialog::DontUseNativeDialog);
  gifName = saveAs + selectedFilter;

  ui->save_gif->setEnabled(0);
  gif->setDefaultDelay(10);
  connect(timer, SIGNAL(timeout()), this, SLOT(creating_gif()));
  timer->start(100);
}

void MainWindow::creating_gif() {
  counter++;
  QImage frame = ui->view->grabFramebuffer();
  QImage normal_frame = frame.scaled(QSize(640, 480));
  gif->addFrame(normal_frame);

  if (counter == 50) {
    timer->stop();
    ui->save_gif->setEnabled(1);
    gif->save(gifName);
    disconnect(timer);
    delete gif;
    delete timer;
  }
}

}  // namespace my_viewer
