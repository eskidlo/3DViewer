#include "builder.h"

namespace my_viewer {
void Vertex::normalize() {
  float rangeX = xInfo[1] - xInfo[0];
  float rangeY = yInfo[1] - yInfo[0];
  float rangeZ = zInfo[1] - zInfo[0];

  float maximum = (rangeX > rangeY) ? rangeX : rangeY;
  maximum = (maximum > rangeZ) ? maximum : rangeZ;
  maximum = (maximum == 0) ? 1 : maximum;

  for (int i = 0; i < amountVert; i++) {
    coord[i * 3] = (coord[i * 3] - xInfo[0]) / maximum * 2 - 1;
    coord[i * 3 + 1] = (coord[i * 3 + 1] - yInfo[0]) / maximum * 2 - 1;
    coord[i * 3 + 2] = (coord[i * 3 + 2] - zInfo[0]) / maximum * 2 - 1;
  }
}
}  // namespace my_viewer