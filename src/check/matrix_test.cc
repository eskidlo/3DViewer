
#include "../model/matrix.h"

#include <gtest/gtest.h>

TEST(MATRIX, getRowsAndCols) {
  my_viewer::Matrix x(5, 2);

  ASSERT_EQ(x.getRows(), 5);
  ASSERT_EQ(x.getCols(), 2);
}

TEST(MATRIX, getRowsAndCols2) {
  EXPECT_THROW(my_viewer::Matrix x(-5, -2);, std::logic_error);
}

TEST(MATRIX, editRows1) {
  my_viewer::Matrix x(2, 2);
  x(0, 0) = 5;
  x(0, 1) = 0.54;
  x(1, 0) = 3.123;
  x(1, 1) = 0.0000004;
  x.editRows(2);

  ASSERT_EQ(x.getRows(), 2);
  EXPECT_NEAR(x(0, 0), 5, 1e-6);
  EXPECT_NEAR(x(0, 1), 0.54, 1e-6);
  EXPECT_NEAR(x(1, 0), 3.123, 1e-6);
  EXPECT_NEAR(x(1, 1), 0.0000004, 1e-6);
}

TEST(MATRIX, editRows2) {
  my_viewer::Matrix x(2, 2);
  x(0, 0) = 5;
  x(0, 1) = 0.54;
  x(1, 0) = 3.123;
  x(1, 1) = 0.0000004;
  x.editRows(3);
  ASSERT_EQ(x.getRows(), 3);
  EXPECT_NEAR(x(0, 0), 5, 1e-6);
  EXPECT_NEAR(x(0, 1), 0.54, 1e-6);
  EXPECT_NEAR(x(1, 0), 3.123, 1e-6);
  EXPECT_NEAR(x(1, 1), 0.0000004, 1e-6);
  ASSERT_EQ(x(2, 0), 0);
  ASSERT_EQ(x(2, 1), 0);
}

TEST(MATRIX, editRows3) {
  my_viewer::Matrix x(2, 2);
  x(0, 0) = 5;
  x(0, 1) = 0.54;
  x(1, 0) = 3.123;
  x(1, 1) = 0.0000004;
  x.editRows(1);

  ASSERT_EQ(x.getRows(), 1);
  EXPECT_NEAR(x(0, 0), 5, 1e-6);
  EXPECT_NEAR(x(0, 1), 0.54, 1e-6);
}

TEST(MATRIX, editRows4) {
  my_viewer::Matrix x(2, 2);
  x(0, 0) = 5;
  x(0, 1) = 0.54;
  x(1, 0) = 3.123;
  x(1, 1) = 0.0000004;
  EXPECT_THROW(x.editRows(-5), std::logic_error);
}

TEST(MATRIX, editCols1) {
  my_viewer::Matrix x(2, 2);
  x(0, 0) = 5;
  x(0, 1) = 0.54;
  x(1, 0) = 3.123;
  x(1, 1) = 0.0000004;
  x.editCols(2);

  ASSERT_EQ(x.getCols(), 2);
  EXPECT_NEAR(x(0, 0), 5, 1e-6);
  EXPECT_NEAR(x(0, 1), 0.54, 1e-6);
  EXPECT_NEAR(x(1, 0), 3.123, 1e-6);
  EXPECT_NEAR(x(1, 1), 0.0000004, 1e-6);
}

TEST(MATRIX, editCols2) {
  my_viewer::Matrix x(2, 2);
  x(0, 0) = 5;
  x(0, 1) = 0.54;
  x(1, 0) = 3.123;
  x(1, 1) = 0.0000004;
  x.editCols(3);

  ASSERT_EQ(x.getCols(), 3);
  EXPECT_NEAR(x(0, 0), 5, 1e-6);
  EXPECT_NEAR(x(0, 1), 0.54, 1e-6);
  EXPECT_NEAR(x(0, 2), 0, 1e-6);
  EXPECT_NEAR(x(1, 0), 3.123, 1e-6);
  EXPECT_NEAR(x(1, 1), 0.0000004, 1e-6);
  EXPECT_NEAR(x(1, 2), 0, 1e-6);
}

TEST(MATRIX, editCols3) {
  my_viewer::Matrix x(2, 2);
  x(0, 0) = 5;
  x(0, 1) = 0.54;
  x(1, 0) = 3.123;
  x(1, 1) = 0.0000004;
  x.editCols(1);

  ASSERT_EQ(x.getCols(), 1);
  EXPECT_NEAR(x(0, 0), 5, 1e-6);
  EXPECT_NEAR(x(1, 0), 3.123, 1e-6);
}

TEST(MATRIX, editCols4) {
  my_viewer::Matrix x(2, 2);
  x(0, 0) = 5;
  x(0, 1) = 0.54;
  x(1, 0) = 3.123;
  x(1, 1) = 0.0000004;
  EXPECT_THROW(x.editCols(-5);, std::logic_error);
}

TEST(MATRIX, emptyAndClear) {
  my_viewer::Matrix x(2, 2);
  x(0, 0) = 5;
  x(0, 1) = 0.54;
  x(1, 0) = 3.123;
  x(1, 1) = 0.0000004;
  x.clear();
  EXPECT_TRUE(x.empty());
}

TEST(MATRIX, error) {
  my_viewer::Matrix x(2, 2);
  x(0, 0) = 5;
  x(0, 1) = 0.54;
  x(1, 0) = 3.123;
  x(1, 1) = 0.0000004;
  EXPECT_THROW(x(-1, 5);, std::logic_error);
}