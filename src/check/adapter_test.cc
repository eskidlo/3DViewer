#include "../model/adapter.h"

#include <gtest/gtest.h>

#include "../model/builder.h"
#include "../model/facade.h"
#include "../model/parser.h"

TEST(ADAPTER, fill) {
  my_viewer::Parser parser;
  my_viewer::Vertex vert;

  std::string line1("v 2 5 6");
  std::string line2("v 1 0 9.8");

  parser.parseV(line1, &vert);
  parser.parseV(line2, &vert);

  my_viewer::adaptMatrix adapter;
  adapter.fill(vert);

  ASSERT_EQ(adapter.matrix.getRows(), vert.amountVert);
  ASSERT_EQ(adapter.matrix.getCols(), 3);

  ASSERT_EQ(adapter.matrix(0, 0), 2);
  ASSERT_EQ(adapter.matrix(0, 1), 5);
  ASSERT_EQ(adapter.matrix(0, 2), 6);

  ASSERT_EQ(adapter.matrix(1, 0), 1);
  ASSERT_EQ(adapter.matrix(1, 1), 0);
  ASSERT_NEAR(adapter.matrix(1, 2), 9.8, 1e-6);

  ASSERT_EQ(adapter.coord[0], 2);
  ASSERT_EQ(adapter.coord[1], 5);
  ASSERT_EQ(adapter.coord[2], 6);

  ASSERT_EQ(adapter.coord[3], 1);
  ASSERT_EQ(adapter.coord[4], 0);
  ASSERT_NEAR(adapter.coord[5], 9.8, 1e-6);
}

TEST(ADAPTER, toDefault) {
  my_viewer::Parser parser;
  my_viewer::Vertex vert;

  std::string line1("v 2 5 6");
  std::string line2("v 1 0 9.8");

  parser.parseV(line1, &vert);
  parser.parseV(line2, &vert);

  my_viewer::adaptMatrix adapter;
  adapter.fill(vert);
  adapter.toDefault();

  EXPECT_TRUE(adapter.coord.empty());
  EXPECT_TRUE(adapter.matrix.empty());
}

TEST(ADAPTER, affine1) {
  my_viewer::Parser p;
  my_viewer::Results res;
  my_viewer::adaptMatrix adapter;

  p.parseFromFile(&res, "check/dummy/cube_first.txt");
  p.getIndexes(&res);
  res.v.normalize();
  adapter.fill(res.v);

  adapter.affine(0, 0, 9, 3, 0, 6, 0.2);

  ASSERT_NEAR(adapter.coord[0], 3.200000, 1e-5);
  ASSERT_NEAR(adapter.coord[1], 2.208061, 1e-5);
  ASSERT_NEAR(adapter.coord[2], -5.202132, 1e-5);

  ASSERT_NEAR(adapter.coord[3], 3.200000, 1e-5);
  ASSERT_NEAR(adapter.coord[4], 2.572513, 1e-5);
  ASSERT_NEAR(adapter.coord[5], -5.366980, 1e-5);

  ASSERT_NEAR(adapter.coord[6], 3.200000, 1e-5);
  ASSERT_NEAR(adapter.coord[7], 2.372909, 1e-5);
  ASSERT_NEAR(adapter.coord[8], -5.566584, 1e-5);

  ASSERT_NEAR(adapter.coord[9], 3.200000, 1e-5);
  ASSERT_NEAR(adapter.coord[10], 2.737360, 1e-5);
  ASSERT_NEAR(adapter.coord[11], -5.731431, 1e-5);

  ASSERT_NEAR(adapter.coord[12], 2.800000, 1e-5);
  ASSERT_NEAR(adapter.coord[13], 2.208061, 1e-5);
  ASSERT_NEAR(adapter.coord[14], -5.202132, 1e-5);

  ASSERT_NEAR(adapter.coord[15], 2.800000, 1e-5);
  ASSERT_NEAR(adapter.coord[16], 2.572513, 1e-5);
  ASSERT_NEAR(adapter.coord[17], -5.366980, 1e-5);

  ASSERT_NEAR(adapter.coord[18], 2.800000, 1e-5);
  ASSERT_NEAR(adapter.coord[19], 2.372909, 1e-5);
  ASSERT_NEAR(adapter.coord[20], -5.566584, 1e-5);

  ASSERT_NEAR(adapter.coord[21], 2.800000, 1e-5);
  ASSERT_NEAR(adapter.coord[22], 2.737360, 1e-5);
  ASSERT_NEAR(adapter.coord[23], -5.731431, 1e-5);
}

TEST(ADAPTER, affine2) {
  my_viewer::Parser p;
  my_viewer::Results res;
  my_viewer::adaptMatrix adapter;

  p.parseFromFile(&res, "check/dummy/correct_single_poly.txt");
  p.getIndexes(&res);
  res.v.normalize();
  adapter.fill(res.v);

  adapter.affine(7, 0, 0, 3, 0, 0, 1.2);

  ASSERT_NEAR(adapter.coord[0], 0.568640, 1e-5);
  ASSERT_NEAR(adapter.coord[1], -2.087259, 1e-5);
  ASSERT_NEAR(adapter.coord[2], -1.200000, 1e-5);

  ASSERT_NEAR(adapter.coord[3], 0.568640, 1e-5);
  ASSERT_NEAR(adapter.coord[4], -2.087259, 1e-5);
  ASSERT_NEAR(adapter.coord[5], -1.200000, 1e-5);

  ASSERT_NEAR(adapter.coord[6], 0.568640, 1e-5);
  ASSERT_NEAR(adapter.coord[7], -2.087259, 1e-5);
  ASSERT_NEAR(adapter.coord[8], -1.200000, 1e-5);
}

TEST(ADAPTER, affine3) {
  my_viewer::Parser p;
  my_viewer::Results res;
  my_viewer::adaptMatrix adapter;

  p.parseFromFile(&res, "check/dummy/correct_single_poly.txt");
  p.getIndexes(&res);
  res.v.normalize();
  adapter.fill(res.v);

  adapter.affine(0, 3, 0, 3, 9, 6, 1);

  ASSERT_NEAR(adapter.coord[0], -1.274385, 1e-5);
  ASSERT_NEAR(adapter.coord[1], 8.0000009, 1e-5);
  ASSERT_NEAR(adapter.coord[2], -5.232203, 1e-5);

  ASSERT_NEAR(adapter.coord[3], -1.274385, 1e-5);
  ASSERT_NEAR(adapter.coord[4], 8.000000, 1e-5);
  ASSERT_NEAR(adapter.coord[5], -5.232203, 1e-5);

  ASSERT_NEAR(adapter.coord[6], -1.274385, 1e-5);
  ASSERT_NEAR(adapter.coord[7], 8.000000, 1e-5);
  ASSERT_NEAR(adapter.coord[8], -5.232203, 1e-5);
}