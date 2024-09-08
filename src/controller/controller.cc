#include "controller.h"

namespace my_viewer {
bool Controller::Parser(std::string file) {
  facade_.ClearEverything();

  bool answer = true;
  try {
    facade_.Parse(file);
  } catch (...) {
    answer = false;
  }
  return answer;
}

int Controller::getEdges() { return facade_.res_.totalEdges; }

int Controller::getVertexes() { return facade_.res_.v.amountVert; }

std::vector<float> &Controller::getCoord() { return facade_.adapter_.coord; }

std::vector<int> &Controller::getIndexes() { return facade_.res_.indexes; }

void Controller::affine() {
  facade_.Affine(xyRot, yzRot, xzRot, xTrans, yTrans, zTrans, Scale);
}

bool Controller::adapterEmpty() { return facade_.adapter_.matrix.empty(); }

int Controller::amountIndexes() { return facade_.res_.indexes.size(); }

void Controller::saveConfig(QSettings *settings) {
  settings->setValue("thicknessEdge", thicknessEdge);
  settings->setValue("centralProjection", centralProjection);
  settings->setValue("dashedEdge", dashedEdge);
  settings->setValue("circlePoints", circlePoints);
  settings->setValue("squarePoints", squarePoints);
  settings->setValue("sizePoint", sizePoint);
  settings->setValue("backgroundColor", backgroundColor);
  settings->setValue("edgeColor", edgeColor);
  settings->setValue("pointColor", pointColor);
}

void Controller::loadConfig(QSettings *settings) {
  thicknessEdge = (settings->value("thicknessEdge").toFloat()) ? true : false;
  centralProjection =
      (settings->value("centralProjection").toBool()) ? true : false;
  dashedEdge = (settings->value("dashedEdge").toBool()) ? true : false;
  circlePoints = (settings->value("circlePoints").toBool()) ? true : false;
  squarePoints = (settings->value("squarePoints").toBool()) ? true : false;
  sizePoint = (settings->value("sizePoint").toInt())
                  ? settings->value("sizePoint").toInt()
                  : 5;
  backgroundColor = (!(settings->value("backgroundColor")).isNull())
                        ? settings->value("backgroundColor").value<QColor>()
                        : QColor(255, 255, 244, 1);
  edgeColor = (!(settings->value("edgeColor")).isNull())
                  ? (settings->value("edgeColor").value<QColor>())
                  : QColor(211, 168, 128, 1);
  pointColor = (!(settings->value("pointColor")).isNull())
                   ? settings->value("pointColor").value<QColor>()
                   : QColor(89, 135, 153, 1);
}
}  // namespace my_viewer
