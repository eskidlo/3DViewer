#include "facade.h"

namespace my_viewer {

void Facade::Parse(std::string name) {
  parser_.parseFromFile(&res_, name);
  parser_.getIndexes(&res_);
  res_.v.normalize();
  adapter_.fill(res_.v);
}

void Facade::Affine(float rotationXY, float rotationXZ, float rotationYZ,
                    float translationX, float translationY, float translationZ,
                    float scale) {
  adapter_.affine(rotationXY, rotationXZ, rotationYZ, translationX,
                  translationY, translationZ, scale);
}

void Facade::ClearEverything() {
  res_.toDefault();
  adapter_.toDefault();
}

}  // namespace my_viewer
