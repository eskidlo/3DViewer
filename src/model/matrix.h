#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>

namespace my_viewer {
class Matrix {
 private:
  int rows_, cols_;
  double **matrix_;

 public:
  Matrix();
  ~Matrix();
  Matrix(int rows, int cols);
  Matrix(const Matrix &other);
  Matrix(Matrix &&other);

  double &operator()(int row, int col);
  Matrix &operator=(const Matrix &other);

  int getRows();
  int getCols();
  void editCols(const int newCols);
  void editRows(const int newRows);
  bool empty();
  void clear();
};
}  // namespace my_viewer

#endif  // MATRIX_H
