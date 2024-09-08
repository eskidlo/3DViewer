#ifndef FACADE_H
#define FACADE_H

#include "adapter.h"
#include "builder.h"
#include "matrix.h"
#include "parser.h"

namespace my_viewer {
class Facade {
 public:
  Parser parser_;
  adaptMatrix adapter_;
  Results res_;

  Facade() {}
  Facade(const Facade &other) = default;
  Facade(Facade &&other) = default;
  ~Facade() {}
  Facade &operator=(const Facade &other) = default;

  void Parse(std::string name);
  void Affine(float rotationXY, float rotationXZ, float rotationYZ,
              float translationX, float translationY, float translationZ,
              float scale);
  void ClearEverything();
};
}  // namespace my_viewer

#endif  // FACADE_H
