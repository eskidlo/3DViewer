#include <QApplication>

#include "view/mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  my_viewer::MainWindow w;
  w.show();
  return a.exec();
}
