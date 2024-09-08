#include "adapter.h"

namespace my_viewer {

void adaptMatrix::affine(float rotationXY, float rotationXZ, float rotationYZ,
                         float translationX, float translationY,
                         float translationZ, float scale) {
  float tempX, tempY, tempZ;

  for (int i = 0; i < matrix.getRows(); i++) {
    coord[i * 3] = matrix(i, 0) * scale;
    coord[i * 3 + 1] = matrix(i, 1) * scale;
    coord[i * 3 + 2] = matrix(i, 2) * scale;

    coord[i * 3] += translationX;
    coord[i * 3 + 1] += translationY;
    coord[i * 3 + 2] += translationZ;

    tempX = coord[i * 3];
    tempY = coord[i * 3 + 1];
    tempZ = coord[i * 3 + 2];

    if (rotationXY != 0) {
      coord[i * 3] = tempX * cos(rotationXY) + tempY * sin(rotationXY);
      coord[i * 3 + 1] = -tempX * sin(rotationXY) + tempY * cos(rotationXY);
    }

    tempX = coord[i * 3];
    tempY = coord[i * 3 + 1];

    if (rotationXZ != 0) {
      coord[i * 3] = tempX * cos(rotationXZ) + tempZ * sin(rotationXZ);
      coord[i * 3 + 2] = -tempX * sin(rotationXZ) + tempZ * cos(rotationXZ);
    }

    tempZ = coord[i * 3 + 2];

    if (rotationYZ != 0) {
      coord[i * 3 + 1] = tempY * cos(rotationYZ) + tempZ * sin(rotationYZ);
      coord[i * 3 + 2] = tempY * sin(rotationYZ) + tempZ * cos(rotationYZ);
    }
  }
}

}  // namespace my_viewer
