#include "../model/parser.h"

#include <gtest/gtest.h>

#include "../model/adapter.h"
#include "../model/builder.h"
#include "../model/facade.h"

TEST(PARSER, parser1) {
  my_viewer::Parser parser;
  my_viewer::Results res;

  parser.parseFromFile(&res, "check/dummy/correct_polygons.txt");

  ASSERT_EQ(res.p[0].amountP, 3);
  ASSERT_EQ(res.p[1].amountP, 2);
  ASSERT_EQ(res.p[2].amountP, 2);
  ASSERT_EQ(res.p[3].amountP, 6);
  ASSERT_EQ(res.p[4].amountP, 5);
  ASSERT_EQ(res.p[5].amountP, 3);
  ASSERT_EQ(res.p[6].amountP, 3);
  ASSERT_EQ(res.p[7].amountP, 3);
  ASSERT_EQ(res.p[8].amountP, 3);
  ASSERT_EQ(res.p[9].amountP, 3);

  ASSERT_EQ(res.amountPols, 10);
  ASSERT_EQ(res.totalEdges, 33);

  ASSERT_EQ(res.p[0].p[0], 1);
  ASSERT_EQ(res.p[2].p[1], 1234);
  ASSERT_EQ(res.p[3].p[2], 5432);

  ASSERT_EQ(res.p[4].p[0], 1e1);
  ASSERT_EQ(res.p[4].p[1], 1e2);
  ASSERT_EQ(res.p[4].p[2], 1e3);
  ASSERT_EQ(res.p[4].p[3], 1e4);
  ASSERT_EQ(res.p[4].p[4], 1e5);

  ASSERT_EQ(res.p[5].p[0], 1);
  ASSERT_EQ(res.p[5].p[1], 2);
  ASSERT_EQ(res.p[5].p[2], 3);

  ASSERT_EQ(res.p[6].p[0], 1);
  ASSERT_EQ(res.p[6].p[1], 2);
  ASSERT_EQ(res.p[6].p[2], 3);

  ASSERT_EQ(res.p[7].p[0], 3);
  ASSERT_EQ(res.p[7].p[1], 4);
  ASSERT_EQ(res.p[7].p[2], 5);

  ASSERT_EQ(res.p[8].p[0], 6);
  ASSERT_EQ(res.p[8].p[1], 3);
  ASSERT_EQ(res.p[8].p[2], 7);

  ASSERT_EQ(res.p[9].p[0], 6);
  ASSERT_EQ(res.p[9].p[1], 3);
  ASSERT_EQ(res.p[9].p[2], 7);
}

TEST(PARSER, parser2) {
  my_viewer::Parser parser;
  my_viewer::Results res;
  parser.parseFromFile(&res, "check/dummy/incorrect_polygons.txt");
  ASSERT_EQ(res.amountPols, 0);
  ASSERT_EQ(res.totalEdges, 0);
}

TEST(PARSER, parser3) {
  my_viewer::Parser parser;
  my_viewer::Results res;

  EXPECT_THROW(parser.parseFromFile(&res, "check/dummy/igfdss.txt"),
               std::logic_error);
}

TEST(PARSER, parser4) {
  my_viewer::Parser parser;
  my_viewer::Results res;
  parser.parseFromFile(&res, "check/dummy/correct_vertex.txt");

  ASSERT_NEAR(res.v.coord[0], 1, 1e-6);
  ASSERT_NEAR(res.v.coord[1], 2, 1e-6);
  ASSERT_NEAR(res.v.coord[2], 3, 1e-6);
  ASSERT_NEAR(res.v.coord[3], 1, 1e-6);
  ASSERT_NEAR(res.v.coord[4], 2, 1e-6);
  ASSERT_NEAR(res.v.coord[5], 3, 1e-6);

  ASSERT_NEAR(res.v.coord[6], 111, 1e-6);
  ASSERT_NEAR(res.v.coord[7], 1111, 1e-6);
  ASSERT_NEAR(res.v.coord[8], 11111, 1e-6);

  ASSERT_NEAR(res.v.coord[9], 1.2, 1e-6);
  ASSERT_NEAR(res.v.coord[10], 1.3, 1e-6);
  ASSERT_NEAR(res.v.coord[11], 1.44444, 1e-6);
  ASSERT_NEAR(res.v.coord[12], -1.22, 1e-6);
  ASSERT_NEAR(res.v.coord[13], -1e5, 1e-6);
  ASSERT_NEAR(res.v.coord[14], 1e-6, 1e-6);

  ASSERT_NEAR(res.v.coord[15], 1, 1e-6);
  ASSERT_NEAR(res.v.coord[16], 2, 1e-6);
  ASSERT_NEAR(res.v.coord[17], 3, 1e-6);

  ASSERT_NEAR(res.v.coord[18], 1, 1e-6);
  ASSERT_NEAR(res.v.coord[19], 2, 1e-6);
  ASSERT_NEAR(res.v.coord[20], 3, 1e-6);

  ASSERT_NEAR(res.v.coord[21], 1, 1e-6);
  ASSERT_NEAR(res.v.coord[22], 2, 1e-6);
  ASSERT_NEAR(res.v.coord[23], 3, 1e-6);
}

TEST(PARSER, parser5) {
  my_viewer::Parser parser;
  my_viewer::Results res;
  parser.parseFromFile(&res, "check/dummy/incorrect_indexes.txt");
  EXPECT_THROW(parser.getIndexes(&res), std::logic_error);
}

TEST(PARSER, parser6) {
  my_viewer::Parser parser;
  my_viewer::Results res;
  parser.parseFromFile(&res, "check/dummy/incorrect_indexes2.txt");
  EXPECT_THROW(parser.getIndexes(&res), std::logic_error);
}