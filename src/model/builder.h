#ifndef BUILDER_H
#define BUILDER_H

#include <cmath>
#include <iostream>
#include <vector>

namespace my_viewer {
class Polygon {
 public:
  std::vector<int> p;
  int amountP;

  Polygon() : amountP(0){};
  Polygon(const Polygon &p) = default;
  Polygon(Polygon &&p) = default;
  Polygon &operator=(const Polygon &p) = default;
  Polygon &operator=(Polygon &&p) = default;
  ~Polygon() {
    amountP = 0;
    p.clear();
  }
};

class Vertex {
 public:
  int amountVert;
  std::vector<float> coord;
  std::vector<float> xInfo;
  std::vector<float> yInfo;
  std::vector<float> zInfo;

  Vertex() {
    amountVert = 0;
    xInfo = {INFINITY, -INFINITY};
    yInfo = {INFINITY, -INFINITY};
    zInfo = {INFINITY, -INFINITY};
  }
  Vertex(const Vertex &v) = default;
  Vertex(Vertex &&p) = default;
  Vertex &operator=(const Vertex &p) = default;
  Vertex &operator=(Vertex &&p) = default;

  ~Vertex() {
    amountVert = 0;
    coord.clear();
    xInfo.clear();
    yInfo.clear();
    zInfo.clear();
  }

  void normalize();

  void toDefault() {
    amountVert = 0;
    coord.clear();
    xInfo = {INFINITY, -INFINITY};
    yInfo = {INFINITY, -INFINITY};
    zInfo = {INFINITY, -INFINITY};
  }
};

class Results {
 public:
  Vertex v;
  std::vector<Polygon> p;
  std::vector<int> indexes;

  int amountPols;
  int totalEdges;

  Results() : amountPols(0), totalEdges(0) {}
  Results(const Results &res) = default;
  Results(Results &&res) = default;
  Results &operator=(const Results &res) = default;
  Results &operator=(Results &&res) = default;
  ~Results() {
    amountPols = 0;
    totalEdges = 0;
    p.clear();
  }

  void toDefault() {
    v.toDefault();
    p.clear();
    indexes.clear();
    amountPols = 0;
    totalEdges = 0;
  }
};

}  // namespace my_viewer

#endif  // BUILDER_H
