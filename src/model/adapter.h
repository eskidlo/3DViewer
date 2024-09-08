#ifndef ADAPTER_H
#define ADAPTER_H

#include <cmath>
#include <iostream>
#include <vector>

#include "builder.h"
#include "matrix.h"

namespace my_viewer {
class adaptMatrix {
 public:
  Matrix matrix;
  std::vector<float> coord;
  adaptMatrix() : matrix(), coord(){};
  adaptMatrix(Vertex vert) : matrix(vert.amountVert, 3), coord(vert.coord) {
    for (int i = 0; i < vert.amountVert; i++) {
      matrix(i, 0) = vert.coord[i * 3];
      matrix(i, 1) = vert.coord[i * 3 + 1];
      matrix(i, 2) = vert.coord[i * 3 + 2];
    }
  }

  adaptMatrix(const adaptMatrix &other) = default;
  adaptMatrix &operator=(const adaptMatrix &other) = default;
  ~adaptMatrix() { coord.clear(); };

  void affine(float rotationXY, float rotationXZ, float rotationYZ,
              float translationX, float translationY, float translationZ,
              float scale);

  void fill(Vertex vert) {
    matrix.editRows(vert.amountVert);
    matrix.editCols(3);
    coord = vert.coord;
    for (int i = 0; i < vert.amountVert; i++) {
      matrix(i, 0) = vert.coord[i * 3];
      matrix(i, 1) = vert.coord[i * 3 + 1];
      matrix(i, 2) = vert.coord[i * 3 + 2];
    }
  }

  void toDefault() {
    coord.clear();
    matrix.clear();
  }
};
}  // namespace my_viewer
#endif  // ADAPTER_H
