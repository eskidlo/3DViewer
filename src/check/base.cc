#include <gtest/gtest.h>

#include "../model/adapter.h"
#include "../model/builder.h"
#include "../model/facade.h"
#include "../model/parser.h"

TEST(RULE_OF_FIVE_ADAPTER, adapter1) {
  my_viewer::adaptMatrix adapter;
  ASSERT_TRUE(adapter.coord.empty());
  ASSERT_TRUE(adapter.matrix.empty());
}

TEST(RULE_OF_FIVE_ADAPTER, adapter2) {
  my_viewer::Parser parser;
  my_viewer::Vertex vert;

  std::string line1("v 2 5 6");
  std::string line2("v 1 0 9.8");

  parser.parseV(line1, &vert);
  parser.parseV(line2, &vert);

  my_viewer::adaptMatrix adapter(vert);

  ASSERT_EQ(adapter.matrix.getRows(), vert.amountVert);
  ASSERT_EQ(adapter.matrix.getCols(), 3);

  ASSERT_EQ(adapter.matrix(0, 0), 2);
  ASSERT_EQ(adapter.matrix(0, 1), 5);
  ASSERT_EQ(adapter.matrix(0, 2), 6);

  ASSERT_EQ(adapter.matrix(1, 0), 1);
  ASSERT_EQ(adapter.matrix(1, 1), 0);
  ASSERT_NEAR(adapter.matrix(1, 2), 9.8, 1e-6);
}

TEST(RULE_OF_FIVE_ADAPTER, adapter3) {
  my_viewer::Parser parser;
  my_viewer::Vertex vert;

  std::string line1("v 2 5 6");
  std::string line2("v 1 0 9");

  parser.parseV(line1, &vert);
  parser.parseV(line2, &vert);
  my_viewer::adaptMatrix adapter(vert);
  my_viewer::adaptMatrix adapterCopy(adapter);

  ASSERT_EQ(adapterCopy.matrix.getRows(), adapter.matrix.getRows());
  ASSERT_EQ(adapterCopy.matrix.getCols(), adapter.matrix.getCols());

  ASSERT_EQ(adapter.matrix(0, 0), adapterCopy.matrix(0, 0));
  ASSERT_EQ(adapter.matrix(0, 1), adapterCopy.matrix(0, 1));
  ASSERT_EQ(adapter.matrix(0, 2), adapterCopy.matrix(0, 2));

  ASSERT_EQ(adapter.matrix(1, 0), adapterCopy.matrix(1, 0));
  ASSERT_EQ(adapter.matrix(1, 1), adapterCopy.matrix(1, 1));
  ASSERT_EQ(adapter.matrix(1, 2), adapterCopy.matrix(1, 2));
}

TEST(RULE_OF_FIVE_ADAPTER, adapter4) {
  my_viewer::Parser parser;
  my_viewer::Vertex vert;

  std::string line1("v 2 5 6");
  std::string line2("v 1 0 9");

  parser.parseV(line1, &vert);
  parser.parseV(line2, &vert);

  my_viewer::adaptMatrix adapter(vert);
  my_viewer::adaptMatrix adapterCopy(adapter);
  my_viewer::adaptMatrix adapterMove(std::move(adapter));

  ASSERT_EQ(adapterCopy.matrix.getRows(), adapterMove.matrix.getRows());
  ASSERT_EQ(adapterCopy.matrix.getCols(), adapterMove.matrix.getCols());

  ASSERT_EQ(adapterMove.matrix(0, 0), adapterCopy.matrix(0, 0));
  ASSERT_EQ(adapterMove.matrix(0, 1), adapterCopy.matrix(0, 1));
  ASSERT_EQ(adapterMove.matrix(0, 2), adapterCopy.matrix(0, 2));

  ASSERT_EQ(adapterMove.matrix(1, 0), adapterCopy.matrix(1, 0));
  ASSERT_EQ(adapterMove.matrix(1, 1), adapterCopy.matrix(1, 1));
  ASSERT_EQ(adapterMove.matrix(1, 2), adapterCopy.matrix(1, 2));
}

TEST(RULE_OF_FIVE_ADAPTER, adapter5) {
  my_viewer::Parser parser;
  my_viewer::Vertex vert;

  std::string line1("v 2 5 6");
  std::string line2("v 1 0 9");

  parser.parseV(line1, &vert);
  parser.parseV(line2, &vert);

  my_viewer::adaptMatrix adapter(vert);
  my_viewer::adaptMatrix adapterCopy;
  adapterCopy = adapter;

  ASSERT_EQ(adapterCopy.matrix.getRows(), adapter.matrix.getRows());
  ASSERT_EQ(adapterCopy.matrix.getCols(), adapter.matrix.getCols());

  ASSERT_EQ(adapter.matrix(0, 0), adapterCopy.matrix(0, 0));
  ASSERT_EQ(adapter.matrix(0, 1), adapterCopy.matrix(0, 1));
  ASSERT_EQ(adapter.matrix(0, 2), adapterCopy.matrix(0, 2));

  ASSERT_EQ(adapter.matrix(1, 0), adapterCopy.matrix(1, 0));
  ASSERT_EQ(adapter.matrix(1, 1), adapterCopy.matrix(1, 1));
  ASSERT_EQ(adapter.matrix(1, 2), adapterCopy.matrix(1, 2));
}

TEST(RULE_OF_FIVE_VERT, vert1) {
  my_viewer::Parser parser;
  my_viewer::Vertex vert;

  ASSERT_EQ(vert.amountVert, 0);
  ASSERT_TRUE(vert.coord.empty());
  ASSERT_TRUE(vert.xInfo[0] == INFINITY);
  ASSERT_TRUE(vert.xInfo[1] == -INFINITY);
  ASSERT_TRUE(vert.yInfo[0] == INFINITY);
  ASSERT_TRUE(vert.yInfo[1] == -INFINITY);
  ASSERT_TRUE(vert.zInfo[0] == INFINITY);
  ASSERT_TRUE(vert.zInfo[1] == -INFINITY);
}

TEST(RULE_OF_FIVE_VERT, vert2) {
  my_viewer::Parser parser;
  my_viewer::Vertex vert;

  std::string line1("v 2.1 1.3 0.5");
  std::string line2("v 1.11 0.2 7");

  parser.parseV(line1, &vert);
  parser.parseV(line2, &vert);

  ASSERT_NEAR(vert.coord[0], 2.1, 1e-6);
  ASSERT_NEAR(vert.coord[1], 1.3, 1e-6);
  ASSERT_NEAR(vert.coord[2], 0.5, 1e-6);
  ASSERT_NEAR(vert.coord[3], 1.11, 1e-6);
  ASSERT_NEAR(vert.coord[4], 0.2, 1e-6);
  ASSERT_NEAR(vert.coord[5], 7, 1e-6);

  ASSERT_NEAR(vert.xInfo[0], 1.11, 1e-6);
  ASSERT_NEAR(vert.xInfo[1], 2.1, 1e-6);

  ASSERT_NEAR(vert.yInfo[0], 0.2, 1e-6);
  ASSERT_NEAR(vert.yInfo[1], 1.3, 1e-6);

  ASSERT_NEAR(vert.zInfo[0], 0.5, 1e-6);
  ASSERT_NEAR(vert.zInfo[1], 7, 1e-6);
}

TEST(RULE_OF_FIVE_VERT, vert3) {
  my_viewer::Parser parser;
  my_viewer::Vertex vert;

  std::string line1("v 2.1 1.3 0.5");
  std::string line2("v 1.11 0.2 7");

  parser.parseV(line1, &vert);
  parser.parseV(line2, &vert);

  my_viewer::Vertex vertCopy(vert);

  ASSERT_NEAR(vert.coord[0], vertCopy.coord[0], 1e-6);
  ASSERT_NEAR(vert.coord[1], vertCopy.coord[1], 1e-6);
  ASSERT_NEAR(vert.coord[2], vertCopy.coord[2], 1e-6);
  ASSERT_NEAR(vert.coord[3], vertCopy.coord[3], 1e-6);
  ASSERT_NEAR(vert.coord[4], vertCopy.coord[4], 1e-6);
  ASSERT_NEAR(vert.coord[5], vertCopy.coord[5], 1e-6);

  ASSERT_NEAR(vert.xInfo[0], vertCopy.xInfo[0], 1e-6);
  ASSERT_NEAR(vert.xInfo[1], vertCopy.xInfo[1], 1e-6);

  ASSERT_NEAR(vert.yInfo[0], vertCopy.yInfo[0], 1e-6);
  ASSERT_NEAR(vert.yInfo[1], vertCopy.yInfo[1], 1e-6);

  ASSERT_NEAR(vert.zInfo[0], vertCopy.zInfo[0], 1e-6);
  ASSERT_NEAR(vert.zInfo[1], vertCopy.zInfo[1], 1e-6);
}

TEST(RULE_OF_FIVE_VERT, vert4) {
  my_viewer::Parser parser;
  my_viewer::Vertex first;

  std::string line1("v 2.1 1.3 0.5");
  std::string line2("v 1.11 0.2 7");

  parser.parseV(line1, &first);
  parser.parseV(line2, &first);

  my_viewer::Vertex vertCopy(first);
  my_viewer::Vertex vert(std::move(first));

  ASSERT_NEAR(vert.coord[0], vertCopy.coord[0], 1e-6);
  ASSERT_NEAR(vert.coord[1], vertCopy.coord[1], 1e-6);
  ASSERT_NEAR(vert.coord[2], vertCopy.coord[2], 1e-6);
  ASSERT_NEAR(vert.coord[3], vertCopy.coord[3], 1e-6);
  ASSERT_NEAR(vert.coord[4], vertCopy.coord[4], 1e-6);
  ASSERT_NEAR(vert.coord[5], vertCopy.coord[5], 1e-6);

  ASSERT_NEAR(vert.xInfo[0], vertCopy.xInfo[0], 1e-6);
  ASSERT_NEAR(vert.xInfo[1], vertCopy.xInfo[1], 1e-6);

  ASSERT_NEAR(vert.yInfo[0], vertCopy.yInfo[0], 1e-6);
  ASSERT_NEAR(vert.yInfo[1], vertCopy.yInfo[1], 1e-6);

  ASSERT_NEAR(vert.zInfo[0], vertCopy.zInfo[0], 1e-6);
  ASSERT_NEAR(vert.zInfo[1], vertCopy.zInfo[1], 1e-6);
}

TEST(RULE_OF_FIVE_VERT, vert5) {
  my_viewer::Parser parser;
  my_viewer::Vertex vert;

  std::string line1("v 2.1 1.3 0.5");
  std::string line2("v 1.11 0.2 7");

  parser.parseV(line1, &vert);
  parser.parseV(line2, &vert);

  my_viewer::Vertex vertCopy;
  vertCopy = vert;

  ASSERT_NEAR(vert.coord[0], vertCopy.coord[0], 1e-6);
  ASSERT_NEAR(vert.coord[1], vertCopy.coord[1], 1e-6);
  ASSERT_NEAR(vert.coord[2], vertCopy.coord[2], 1e-6);
  ASSERT_NEAR(vert.coord[3], vertCopy.coord[3], 1e-6);
  ASSERT_NEAR(vert.coord[4], vertCopy.coord[4], 1e-6);
  ASSERT_NEAR(vert.coord[5], vertCopy.coord[5], 1e-6);

  ASSERT_NEAR(vert.xInfo[0], vertCopy.xInfo[0], 1e-6);
  ASSERT_NEAR(vert.xInfo[1], vertCopy.xInfo[1], 1e-6);

  ASSERT_NEAR(vert.yInfo[0], vertCopy.yInfo[0], 1e-6);
  ASSERT_NEAR(vert.yInfo[1], vertCopy.yInfo[1], 1e-6);

  ASSERT_NEAR(vert.zInfo[0], vertCopy.zInfo[0], 1e-6);
  ASSERT_NEAR(vert.zInfo[1], vertCopy.zInfo[1], 1e-6);
}

TEST(RULE_OF_FIVE_POLYGON, poly1) {
  my_viewer::Polygon p;
  ASSERT_TRUE(p.p.empty());
  ASSERT_TRUE(p.amountP == 0);
}

TEST(RULE_OF_FIVE_POLYGON, poly2) {
  my_viewer::Results res;
  my_viewer::Parser p;
  std::string line1("f 2 5 6");
  std::string line2("f 1 2 9");

  p.parseF(line1, &res);
  p.parseF(line2, &res);

  ASSERT_EQ(res.p[0].p[0], 2);
  ASSERT_EQ(res.p[0].p[1], 5);
  ASSERT_EQ(res.p[0].p[2], 6);

  ASSERT_EQ(res.p[1].p[0], 1);
  ASSERT_EQ(res.p[1].p[1], 2);
  ASSERT_EQ(res.p[1].p[2], 9);

  ASSERT_EQ(res.p[1].amountP, 3);
}

TEST(RULE_OF_FIVE_POLYGON, poly3) {
  my_viewer::Results res;
  my_viewer::Parser p;
  std::string line1("f 2 5 6");

  p.parseF(line1, &res);
  my_viewer::Polygon pol(res.p[0]);

  ASSERT_EQ(res.p[0].p[0], pol.p[0]);
  ASSERT_EQ(res.p[0].p[1], pol.p[1]);
  ASSERT_EQ(res.p[0].p[2], pol.p[2]);

  ASSERT_EQ(res.p[0].amountP, pol.amountP);
}

TEST(RULE_OF_FIVE_POLYGON, poly4) {
  my_viewer::Results res;
  my_viewer::Parser p;
  std::string line1("f 2 5 6");

  p.parseF(line1, &res);
  my_viewer::Polygon pol(res.p[0]);
  my_viewer::Polygon pol2(std::move(pol));

  ASSERT_EQ(res.p[0].p[0], pol2.p[0]);
  ASSERT_EQ(res.p[0].p[1], pol2.p[1]);
  ASSERT_EQ(res.p[0].p[2], pol2.p[2]);

  ASSERT_EQ(res.p[0].amountP, pol2.amountP);
}
TEST(RULE_OF_FIVE_POLYGON, poly5) {
  my_viewer::Results res;
  my_viewer::Parser p;
  std::string line1("f 2 5 6");

  p.parseF(line1, &res);
  my_viewer::Polygon pol;
  pol = res.p[0];

  ASSERT_EQ(res.p[0].p[0], pol.p[0]);
  ASSERT_EQ(res.p[0].p[1], pol.p[1]);
  ASSERT_EQ(res.p[0].p[2], pol.p[2]);

  ASSERT_EQ(res.p[0].amountP, pol.amountP);
}

TEST(RULE_OF_FIVE_RES, res1) {
  my_viewer::Results res;
  ASSERT_TRUE(res.v.amountVert == 0);
  ASSERT_TRUE(res.v.coord.empty());

  ASSERT_TRUE(res.v.xInfo[0] == INFINITY);
  ASSERT_TRUE(res.v.xInfo[1] == -INFINITY);
  ASSERT_TRUE(res.v.yInfo[0] == INFINITY);
  ASSERT_TRUE(res.v.yInfo[1] == -INFINITY);
  ASSERT_TRUE(res.v.zInfo[0] == INFINITY);
  ASSERT_TRUE(res.v.zInfo[1] == -INFINITY);

  ASSERT_TRUE(res.p.empty());
  ASSERT_TRUE(res.indexes.empty());
  ASSERT_TRUE(res.amountPols == 0);
  ASSERT_TRUE(res.totalEdges == 0);
}

TEST(RULE_OF_FIVE_RES, res2) {
  my_viewer::Results res;
  my_viewer::Parser p;
  p.parseFromFile(&res, "check/dummy/correct_single_poly.txt");
  p.getIndexes(&res);

  ASSERT_EQ(res.amountPols, 1);
  ASSERT_EQ(res.totalEdges, 3);

  ASSERT_EQ(res.indexes[0], 0);
  ASSERT_EQ(res.indexes[1], 1);
  ASSERT_EQ(res.indexes[2], 1);
  ASSERT_EQ(res.indexes[3], 2);
  ASSERT_EQ(res.indexes[4], 2);
  ASSERT_EQ(res.indexes[5], 0);
}

TEST(RULE_OF_FIVE_RES, res3) {
  my_viewer::Results res;
  my_viewer::Parser p;
  p.parseFromFile(&res, "check/dummy/correct_single_poly.txt");
  p.getIndexes(&res);

  my_viewer::Results resCopy(res);

  ASSERT_EQ(res.amountPols, resCopy.amountPols);
  ASSERT_EQ(res.totalEdges, resCopy.totalEdges);

  ASSERT_EQ(res.indexes[0], resCopy.indexes[0]);
  ASSERT_EQ(res.indexes[1], resCopy.indexes[1]);
  ASSERT_EQ(res.indexes[2], resCopy.indexes[2]);
  ASSERT_EQ(res.indexes[3], resCopy.indexes[3]);
  ASSERT_EQ(res.indexes[4], resCopy.indexes[4]);
  ASSERT_EQ(res.indexes[5], resCopy.indexes[0]);

  ASSERT_NEAR(res.v.coord[0], resCopy.v.coord[0], 1e-6);
  ASSERT_NEAR(res.v.coord[1], resCopy.v.coord[1], 1e-6);
  ASSERT_NEAR(res.v.coord[2], resCopy.v.coord[2], 1e-6);
  ASSERT_NEAR(res.v.coord[3], resCopy.v.coord[3], 1e-6);
  ASSERT_NEAR(res.v.coord[4], resCopy.v.coord[4], 1e-6);
  ASSERT_NEAR(res.v.coord[5], resCopy.v.coord[5], 1e-6);

  ASSERT_EQ(res.p[0].p[0], resCopy.p[0].p[0]);
  ASSERT_EQ(res.p[0].p[1], resCopy.p[0].p[1]);
  ASSERT_EQ(res.p[0].p[2], resCopy.p[0].p[2]);
}

TEST(RULE_OF_FIVE_RES, res4) {
  my_viewer::Results r;
  my_viewer::Parser p;
  p.parseFromFile(&r, "check/dummy/correct_single_poly.txt");
  p.getIndexes(&r);

  my_viewer::Results resCopy(r);
  my_viewer::Results res(std::move(r));

  ASSERT_EQ(res.amountPols, resCopy.amountPols);
  ASSERT_EQ(res.totalEdges, resCopy.totalEdges);

  ASSERT_EQ(res.indexes[0], resCopy.indexes[0]);
  ASSERT_EQ(res.indexes[1], resCopy.indexes[1]);
  ASSERT_EQ(res.indexes[2], resCopy.indexes[2]);
  ASSERT_EQ(res.indexes[3], resCopy.indexes[3]);
  ASSERT_EQ(res.indexes[4], resCopy.indexes[4]);
  ASSERT_EQ(res.indexes[5], resCopy.indexes[0]);

  ASSERT_NEAR(res.v.coord[0], resCopy.v.coord[0], 1e-6);
  ASSERT_NEAR(res.v.coord[1], resCopy.v.coord[1], 1e-6);
  ASSERT_NEAR(res.v.coord[2], resCopy.v.coord[2], 1e-6);
  ASSERT_NEAR(res.v.coord[3], resCopy.v.coord[3], 1e-6);
  ASSERT_NEAR(res.v.coord[4], resCopy.v.coord[4], 1e-6);
  ASSERT_NEAR(res.v.coord[5], resCopy.v.coord[5], 1e-6);

  ASSERT_EQ(res.p[0].p[0], resCopy.p[0].p[0]);
  ASSERT_EQ(res.p[0].p[1], resCopy.p[0].p[1]);
  ASSERT_EQ(res.p[0].p[2], resCopy.p[0].p[2]);
}

TEST(RULE_OF_FIVE_RES, res5) {
  my_viewer::Results res;
  my_viewer::Parser p;
  p.parseFromFile(&res, "check/dummy/correct_single_poly.txt");
  p.getIndexes(&res);

  my_viewer::Results resCopy;
  resCopy = res;

  ASSERT_EQ(res.amountPols, resCopy.amountPols);
  ASSERT_EQ(res.totalEdges, resCopy.totalEdges);

  ASSERT_EQ(res.indexes[0], resCopy.indexes[0]);
  ASSERT_EQ(res.indexes[1], resCopy.indexes[1]);
  ASSERT_EQ(res.indexes[2], resCopy.indexes[2]);
  ASSERT_EQ(res.indexes[3], resCopy.indexes[3]);
  ASSERT_EQ(res.indexes[4], resCopy.indexes[4]);
  ASSERT_EQ(res.indexes[5], resCopy.indexes[0]);

  ASSERT_NEAR(res.v.coord[0], resCopy.v.coord[0], 1e-6);
  ASSERT_NEAR(res.v.coord[1], resCopy.v.coord[1], 1e-6);
  ASSERT_NEAR(res.v.coord[2], resCopy.v.coord[2], 1e-6);
  ASSERT_NEAR(res.v.coord[3], resCopy.v.coord[3], 1e-6);
  ASSERT_NEAR(res.v.coord[4], resCopy.v.coord[4], 1e-6);
  ASSERT_NEAR(res.v.coord[5], resCopy.v.coord[5], 1e-6);

  ASSERT_EQ(res.p[0].p[0], resCopy.p[0].p[0]);
  ASSERT_EQ(res.p[0].p[1], resCopy.p[0].p[1]);
  ASSERT_EQ(res.p[0].p[2], resCopy.p[0].p[2]);
}

TEST(RULE_OF_FIVE_RES, res6) {
  my_viewer::Results r;
  my_viewer::Parser p;
  p.parseFromFile(&r, "check/dummy/correct_single_poly.txt");
  p.getIndexes(&r);

  my_viewer::Results resCopy(r);
  my_viewer::Results res;
  res = std::move(r);

  ASSERT_EQ(res.amountPols, resCopy.amountPols);
  ASSERT_EQ(res.totalEdges, resCopy.totalEdges);

  ASSERT_EQ(res.indexes[0], resCopy.indexes[0]);
  ASSERT_EQ(res.indexes[1], resCopy.indexes[1]);
  ASSERT_EQ(res.indexes[2], resCopy.indexes[2]);
  ASSERT_EQ(res.indexes[3], resCopy.indexes[3]);
  ASSERT_EQ(res.indexes[4], resCopy.indexes[4]);
  ASSERT_EQ(res.indexes[5], resCopy.indexes[0]);

  ASSERT_NEAR(res.v.coord[0], resCopy.v.coord[0], 1e-6);
  ASSERT_NEAR(res.v.coord[1], resCopy.v.coord[1], 1e-6);
  ASSERT_NEAR(res.v.coord[2], resCopy.v.coord[2], 1e-6);
  ASSERT_NEAR(res.v.coord[3], resCopy.v.coord[3], 1e-6);
  ASSERT_NEAR(res.v.coord[4], resCopy.v.coord[4], 1e-6);
  ASSERT_NEAR(res.v.coord[5], resCopy.v.coord[5], 1e-6);

  ASSERT_EQ(res.p[0].p[0], resCopy.p[0].p[0]);
  ASSERT_EQ(res.p[0].p[1], resCopy.p[0].p[1]);
  ASSERT_EQ(res.p[0].p[2], resCopy.p[0].p[2]);
}

TEST(RULE_OF_FIVE_MATRIX, matrix1) {
  my_viewer::Matrix x(5, 2);

  ASSERT_EQ(x.getRows(), 5);
  ASSERT_EQ(x.getCols(), 2);
}

TEST(RULE_OF_FIVE_MATRIX, error) {
  EXPECT_THROW(my_viewer::Matrix x(-2, 2), std::logic_error);
}

TEST(RULE_OF_FIVE_MATRIX, matrix2) {
  my_viewer::Matrix x(1, 2);
  x(0, 0) = 1;
  x(0, 1) = 0.553;
  my_viewer::Matrix y(x);

  ASSERT_EQ(y.getRows(), 1);
  ASSERT_EQ(y.getCols(), 2);
  EXPECT_NEAR(y(0, 0), 1, 1e-6);
  EXPECT_NEAR(y(0, 1), 0.553, 1e-6);
}

TEST(RULE_OF_FIVE_MATRIX, matrix3) {
  my_viewer::Matrix x(1, 2);
  x(0, 0) = 1;
  x(0, 1) = 0.553;
  my_viewer::Matrix y(std::move(x));

  ASSERT_EQ(y.getRows(), 1);
  ASSERT_EQ(y.getCols(), 2);
  EXPECT_NEAR(y(0, 0), 1, 1e-6);
  EXPECT_NEAR(y(0, 1), 0.553, 1e-6);
}

TEST(RULE_OF_FIVE_MATRIX, matrix4) {
  my_viewer::Matrix x(1, 2);
  x(0, 0) = 1;
  x(0, 1) = 0.553;
  my_viewer::Matrix y;
  y = x;

  ASSERT_EQ(y.getRows(), 1);
  ASSERT_EQ(y.getCols(), 2);
  EXPECT_NEAR(y(0, 0), 1, 1e-6);
  EXPECT_NEAR(y(0, 1), 0.553, 1e-6);
}

TEST(RULE_OF_FIVE_MATRIX, facade1) {
  my_viewer::Facade facade;
  facade.Parse("check/dummy/correct_single_poly.txt");
  my_viewer::Facade facade2(facade);

  ASSERT_EQ(facade.res_.amountPols, facade2.res_.amountPols);
  ASSERT_EQ(facade.res_.totalEdges, facade2.res_.totalEdges);

  ASSERT_EQ(facade.res_.indexes[0], facade2.res_.indexes[0]);
  ASSERT_EQ(facade.res_.indexes[1], facade2.res_.indexes[1]);
  ASSERT_EQ(facade.res_.indexes[2], facade2.res_.indexes[2]);
  ASSERT_EQ(facade.res_.indexes[3], facade2.res_.indexes[3]);
  ASSERT_EQ(facade.res_.indexes[4], facade2.res_.indexes[4]);
  ASSERT_EQ(facade.res_.indexes[5], facade2.res_.indexes[0]);

  ASSERT_NEAR(facade.res_.v.coord[0], facade2.res_.v.coord[0], 1e-6);
  ASSERT_NEAR(facade.res_.v.coord[1], facade2.res_.v.coord[1], 1e-6);
  ASSERT_NEAR(facade.res_.v.coord[2], facade2.res_.v.coord[2], 1e-6);
  ASSERT_NEAR(facade.res_.v.coord[3], facade2.res_.v.coord[3], 1e-6);
  ASSERT_NEAR(facade.res_.v.coord[4], facade2.res_.v.coord[4], 1e-6);
  ASSERT_NEAR(facade.res_.v.coord[5], facade2.res_.v.coord[5], 1e-6);

  ASSERT_EQ(facade.res_.p[0].p[0], facade.res_.p[0].p[0]);
  ASSERT_EQ(facade.res_.p[0].p[1], facade.res_.p[0].p[1]);
  ASSERT_EQ(facade.res_.p[0].p[2], facade.res_.p[0].p[2]);

  ASSERT_NEAR(facade.adapter_.coord[0], facade2.adapter_.coord[0], 1e-6);
  ASSERT_NEAR(facade.adapter_.coord[1], facade2.adapter_.coord[0], 1e-6);
  ASSERT_NEAR(facade.adapter_.coord[2], facade2.adapter_.coord[0], 1e-6);
  ASSERT_NEAR(facade.adapter_.coord[3], facade2.adapter_.coord[0], 1e-6);
  ASSERT_NEAR(facade.adapter_.coord[4], facade2.adapter_.coord[0], 1e-6);
  ASSERT_NEAR(facade.adapter_.coord[5], facade2.adapter_.coord[0], 1e-6);

  ASSERT_NEAR(facade.adapter_.matrix(0, 0), facade2.adapter_.matrix(0, 0),
              1e-6);
  ASSERT_NEAR(facade.adapter_.matrix(0, 1), facade2.adapter_.matrix(0, 1),
              1e-6);
  ASSERT_NEAR(facade.adapter_.matrix(0, 2), facade2.adapter_.matrix(0, 0),
              1e-6);

  ASSERT_NEAR(facade.adapter_.matrix(1, 0), facade2.adapter_.matrix(1, 0),
              1e-6);
  ASSERT_NEAR(facade.adapter_.matrix(1, 1), facade2.adapter_.matrix(1, 1),
              1e-6);
  ASSERT_NEAR(facade.adapter_.matrix(1, 2), facade2.adapter_.matrix(1, 2),
              1e-6);

  ASSERT_NEAR(facade.adapter_.matrix(2, 0), facade2.adapter_.matrix(2, 0),
              1e-6);
  ASSERT_NEAR(facade.adapter_.matrix(2, 1), facade2.adapter_.matrix(2, 1),
              1e-6);
  ASSERT_NEAR(facade.adapter_.matrix(2, 2), facade2.adapter_.matrix(2, 2),
              1e-6);
}

TEST(RULE_OF_FIVE_MATRIX, facade2) {
  my_viewer::Facade f;

  f.Parse("check/dummy/correct_single_poly.txt");
  my_viewer::Facade facade(f);
  my_viewer::Facade facade2(std::move(f));

  ASSERT_EQ(facade.res_.amountPols, facade2.res_.amountPols);
  ASSERT_EQ(facade.res_.totalEdges, facade2.res_.totalEdges);

  ASSERT_EQ(facade.res_.indexes[0], facade2.res_.indexes[0]);
  ASSERT_EQ(facade.res_.indexes[1], facade2.res_.indexes[1]);
  ASSERT_EQ(facade.res_.indexes[2], facade2.res_.indexes[2]);
  ASSERT_EQ(facade.res_.indexes[3], facade2.res_.indexes[3]);
  ASSERT_EQ(facade.res_.indexes[4], facade2.res_.indexes[4]);
  ASSERT_EQ(facade.res_.indexes[5], facade2.res_.indexes[0]);

  ASSERT_NEAR(facade.res_.v.coord[0], facade2.res_.v.coord[0], 1e-6);
  ASSERT_NEAR(facade.res_.v.coord[1], facade2.res_.v.coord[1], 1e-6);
  ASSERT_NEAR(facade.res_.v.coord[2], facade2.res_.v.coord[2], 1e-6);
  ASSERT_NEAR(facade.res_.v.coord[3], facade2.res_.v.coord[3], 1e-6);
  ASSERT_NEAR(facade.res_.v.coord[4], facade2.res_.v.coord[4], 1e-6);
  ASSERT_NEAR(facade.res_.v.coord[5], facade2.res_.v.coord[5], 1e-6);

  ASSERT_EQ(facade.res_.p[0].p[0], facade.res_.p[0].p[0]);
  ASSERT_EQ(facade.res_.p[0].p[1], facade.res_.p[0].p[1]);
  ASSERT_EQ(facade.res_.p[0].p[2], facade.res_.p[0].p[2]);

  ASSERT_NEAR(facade.adapter_.coord[0], facade2.adapter_.coord[0], 1e-6);
  ASSERT_NEAR(facade.adapter_.coord[1], facade2.adapter_.coord[0], 1e-6);
  ASSERT_NEAR(facade.adapter_.coord[2], facade2.adapter_.coord[0], 1e-6);
  ASSERT_NEAR(facade.adapter_.coord[3], facade2.adapter_.coord[0], 1e-6);
  ASSERT_NEAR(facade.adapter_.coord[4], facade2.adapter_.coord[0], 1e-6);
  ASSERT_NEAR(facade.adapter_.coord[5], facade2.adapter_.coord[0], 1e-6);

  ASSERT_NEAR(facade.adapter_.matrix(0, 0), facade2.adapter_.matrix(0, 0),
              1e-6);
  ASSERT_NEAR(facade.adapter_.matrix(0, 1), facade2.adapter_.matrix(0, 1),
              1e-6);
  ASSERT_NEAR(facade.adapter_.matrix(0, 2), facade2.adapter_.matrix(0, 0),
              1e-6);

  ASSERT_NEAR(facade.adapter_.matrix(1, 0), facade2.adapter_.matrix(1, 0),
              1e-6);
  ASSERT_NEAR(facade.adapter_.matrix(1, 1), facade2.adapter_.matrix(1, 1),
              1e-6);
  ASSERT_NEAR(facade.adapter_.matrix(1, 2), facade2.adapter_.matrix(1, 2),
              1e-6);

  ASSERT_NEAR(facade.adapter_.matrix(2, 0), facade2.adapter_.matrix(2, 0),
              1e-6);
  ASSERT_NEAR(facade.adapter_.matrix(2, 1), facade2.adapter_.matrix(2, 1),
              1e-6);
  ASSERT_NEAR(facade.adapter_.matrix(2, 2), facade2.adapter_.matrix(2, 2),
              1e-6);
}

TEST(RULE_OF_FIVE_MATRIX, facade3) {
  my_viewer::Facade facade;
  facade.Parse("check/dummy/correct_single_poly.txt");
  my_viewer::Facade facade2;
  facade2 = facade;

  ASSERT_EQ(facade.res_.amountPols, facade2.res_.amountPols);
  ASSERT_EQ(facade.res_.totalEdges, facade2.res_.totalEdges);

  ASSERT_EQ(facade.res_.indexes[0], facade2.res_.indexes[0]);
  ASSERT_EQ(facade.res_.indexes[1], facade2.res_.indexes[1]);
  ASSERT_EQ(facade.res_.indexes[2], facade2.res_.indexes[2]);
  ASSERT_EQ(facade.res_.indexes[3], facade2.res_.indexes[3]);
  ASSERT_EQ(facade.res_.indexes[4], facade2.res_.indexes[4]);
  ASSERT_EQ(facade.res_.indexes[5], facade2.res_.indexes[0]);

  ASSERT_NEAR(facade.res_.v.coord[0], facade2.res_.v.coord[0], 1e-6);
  ASSERT_NEAR(facade.res_.v.coord[1], facade2.res_.v.coord[1], 1e-6);
  ASSERT_NEAR(facade.res_.v.coord[2], facade2.res_.v.coord[2], 1e-6);
  ASSERT_NEAR(facade.res_.v.coord[3], facade2.res_.v.coord[3], 1e-6);
  ASSERT_NEAR(facade.res_.v.coord[4], facade2.res_.v.coord[4], 1e-6);
  ASSERT_NEAR(facade.res_.v.coord[5], facade2.res_.v.coord[5], 1e-6);

  ASSERT_EQ(facade.res_.p[0].p[0], facade.res_.p[0].p[0]);
  ASSERT_EQ(facade.res_.p[0].p[1], facade.res_.p[0].p[1]);
  ASSERT_EQ(facade.res_.p[0].p[2], facade.res_.p[0].p[2]);

  ASSERT_NEAR(facade.adapter_.coord[0], facade2.adapter_.coord[0], 1e-6);
  ASSERT_NEAR(facade.adapter_.coord[1], facade2.adapter_.coord[0], 1e-6);
  ASSERT_NEAR(facade.adapter_.coord[2], facade2.adapter_.coord[0], 1e-6);
  ASSERT_NEAR(facade.adapter_.coord[3], facade2.adapter_.coord[0], 1e-6);
  ASSERT_NEAR(facade.adapter_.coord[4], facade2.adapter_.coord[0], 1e-6);
  ASSERT_NEAR(facade.adapter_.coord[5], facade2.adapter_.coord[0], 1e-6);

  ASSERT_NEAR(facade.adapter_.matrix(0, 0), facade2.adapter_.matrix(0, 0),
              1e-6);
  ASSERT_NEAR(facade.adapter_.matrix(0, 1), facade2.adapter_.matrix(0, 1),
              1e-6);
  ASSERT_NEAR(facade.adapter_.matrix(0, 2), facade2.adapter_.matrix(0, 0),
              1e-6);

  ASSERT_NEAR(facade.adapter_.matrix(1, 0), facade2.adapter_.matrix(1, 0),
              1e-6);
  ASSERT_NEAR(facade.adapter_.matrix(1, 1), facade2.adapter_.matrix(1, 1),
              1e-6);
  ASSERT_NEAR(facade.adapter_.matrix(1, 2), facade2.adapter_.matrix(1, 2),
              1e-6);

  ASSERT_NEAR(facade.adapter_.matrix(2, 0), facade2.adapter_.matrix(2, 0),
              1e-6);
  ASSERT_NEAR(facade.adapter_.matrix(2, 1), facade2.adapter_.matrix(2, 1),
              1e-6);
  ASSERT_NEAR(facade.adapter_.matrix(2, 2), facade2.adapter_.matrix(2, 2),
              1e-6);
}

TEST(TO_DEFAULT, vertex) {
  my_viewer::Parser parser;
  my_viewer::Results res;

  parser.parseFromFile(&res, "check/dummy/correct_single_poly.txt");
  res.v.toDefault();
  ASSERT_EQ(res.v.amountVert, 0);
  ASSERT_TRUE(res.v.coord.empty());
  ASSERT_TRUE(res.v.xInfo[0] == INFINITY);
  ASSERT_TRUE(res.v.xInfo[1] == -INFINITY);
  ASSERT_TRUE(res.v.yInfo[0] == INFINITY);
  ASSERT_TRUE(res.v.yInfo[1] == -INFINITY);
  ASSERT_TRUE(res.v.zInfo[0] == INFINITY);
  ASSERT_TRUE(res.v.zInfo[1] == -INFINITY);
}

TEST(TO_DEFAULT, results) {
  my_viewer::Parser parser;
  my_viewer::Results res;

  parser.parseFromFile(&res, "check/dummy/correct_single_poly.txt");
  res.toDefault();
  ASSERT_EQ(res.v.amountVert, 0);
  ASSERT_TRUE(res.v.coord.empty());
  ASSERT_TRUE(res.v.xInfo[0] == INFINITY);
  ASSERT_TRUE(res.v.xInfo[1] == -INFINITY);
  ASSERT_TRUE(res.v.yInfo[0] == INFINITY);
  ASSERT_TRUE(res.v.yInfo[1] == -INFINITY);
  ASSERT_TRUE(res.v.zInfo[0] == INFINITY);
  ASSERT_TRUE(res.v.zInfo[1] == -INFINITY);

  ASSERT_TRUE(res.p.empty());
  ASSERT_TRUE(res.amountPols == 0);
  ASSERT_TRUE(res.totalEdges == 0);
  ASSERT_TRUE(res.indexes.empty());
}