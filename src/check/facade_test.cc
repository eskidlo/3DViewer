#include "../model/facade.h"

#include <gtest/gtest.h>

TEST(FACADE, parser1) {
  my_viewer::Facade f;
  f.Parse("check/dummy/cube_first.txt");
  ASSERT_EQ(f.res_.amountPols, 12);
  ASSERT_EQ(f.res_.totalEdges, 36);
  ASSERT_EQ(f.res_.v.amountVert, 8);

  ASSERT_EQ(f.res_.p[0].p[0], 5);
  ASSERT_EQ(f.res_.p[0].p[1], 3);
  ASSERT_EQ(f.res_.p[0].p[2], 1);

  ASSERT_EQ(f.res_.p[1].p[0], 3);
  ASSERT_EQ(f.res_.p[1].p[1], 8);
  ASSERT_EQ(f.res_.p[1].p[2], 4);

  ASSERT_EQ(f.res_.p[2].p[0], 7);
  ASSERT_EQ(f.res_.p[2].p[1], 6);
  ASSERT_EQ(f.res_.p[2].p[2], 8);

  ASSERT_NEAR(f.res_.v.coord[0], 1.000000, 1e-6);
  ASSERT_NEAR(f.res_.v.coord[1], 1.000000, 1e-6);
  ASSERT_NEAR(f.res_.v.coord[2], -1.000000, 1e-6);
}

TEST(FACADE, parser2) {
  my_viewer::Facade f;
  f.Parse("check/dummy/correct_single_poly.txt");
  ASSERT_EQ(f.res_.amountPols, 1);
  ASSERT_EQ(f.res_.totalEdges, 3);
  ASSERT_EQ(f.res_.v.amountVert, 3);

  ASSERT_NEAR(f.res_.v.coord[0], -1.000000, 1e-6);
  ASSERT_NEAR(f.res_.v.coord[1], -1.000000, 1e-6);
  ASSERT_NEAR(f.res_.v.coord[2], -1.000000, 1e-6);
}

TEST(FACADE, affine) {
  my_viewer::Facade f;
  f.Parse("check/dummy/correct_single_poly.txt");
  f.Affine(7, 0, 0, 3, 0, 0, 1.2);

  ASSERT_NEAR(f.adapter_.coord[0], 0.568640, 1e-5);
  ASSERT_NEAR(f.adapter_.coord[1], -2.087259, 1e-5);
  ASSERT_NEAR(f.adapter_.coord[2], -1.200000, 1e-5);

  ASSERT_NEAR(f.adapter_.coord[3], 0.568640, 1e-5);
  ASSERT_NEAR(f.adapter_.coord[4], -2.087259, 1e-5);
  ASSERT_NEAR(f.adapter_.coord[5], -1.200000, 1e-5);

  ASSERT_NEAR(f.adapter_.coord[6], 0.568640, 1e-5);
  ASSERT_NEAR(f.adapter_.coord[7], -2.087259, 1e-5);
  ASSERT_NEAR(f.adapter_.coord[8], -1.200000, 1e-5);
}

TEST(FACADE, toDefault) {
  my_viewer::Facade f;
  f.Parse("check/dummy/correct_single_poly.txt");
  f.ClearEverything();

  ASSERT_EQ(f.res_.v.amountVert, 0);
  ASSERT_TRUE(f.res_.v.coord.empty());
  ASSERT_TRUE(f.res_.v.xInfo[0] == INFINITY);
  ASSERT_TRUE(f.res_.v.xInfo[1] == -INFINITY);
  ASSERT_TRUE(f.res_.v.yInfo[0] == INFINITY);
  ASSERT_TRUE(f.res_.v.yInfo[1] == -INFINITY);
  ASSERT_TRUE(f.res_.v.zInfo[0] == INFINITY);
  ASSERT_TRUE(f.res_.v.zInfo[1] == -INFINITY);

  ASSERT_TRUE(f.res_.p.empty());
  ASSERT_TRUE(f.res_.amountPols == 0);
  ASSERT_TRUE(f.res_.totalEdges == 0);
  ASSERT_TRUE(f.res_.indexes.empty());
  ASSERT_TRUE(f.adapter_.coord.empty());
  ASSERT_TRUE(f.adapter_.matrix.empty());
}
