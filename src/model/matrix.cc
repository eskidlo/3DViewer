#include "matrix.h"

namespace my_viewer {
Matrix::Matrix() {
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

Matrix::~Matrix() {
  for (int i = 0; i < rows_; i++) {
    if ((matrix_) && (matrix_[i])) {
      delete[] matrix_[i];
    }
  }
  if (matrix_) {
    delete[] matrix_;
  }
}

Matrix::Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows_ < 0 || cols_ < 0) {
    throw std::logic_error("index is outside the matrix");
  }
  matrix_ = new double *[rows_] {};
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]{};
  }
}

Matrix::Matrix(const Matrix &other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(nullptr) {
  matrix_ = new double *[rows_] {};
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]{};
    std::copy(other.matrix_[i], other.matrix_[i] + cols_, matrix_[i]);
  }
}

Matrix::Matrix(Matrix &&other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.matrix_ = nullptr;
  other.rows_ = other.cols_ = 0;
}

double &Matrix::operator()(int row, int col) {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0) {
    throw std::out_of_range("index is outside the matrix");
  }
  return matrix_[row][col];
}

Matrix &Matrix::operator=(const Matrix &other) {
  this->~Matrix();

  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = new double *[rows_] {};
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]{};
    std::copy(other.matrix_[i], other.matrix_[i] + cols_, matrix_[i]);
  }

  return *this;
}

int Matrix::getRows() { return rows_; }

int Matrix::getCols() { return cols_; }

void Matrix::editRows(const int newRows) {
  if (newRows < 0) {
    throw std::logic_error("index is outside the matrix");
  }
  Matrix tmp(newRows, cols_);
  int actualRows = std::min(rows_, newRows);
  for (int i = 0; i < actualRows; i++) {
    for (int j = 0; j < cols_; j++) {
      tmp.matrix_[i][j] = matrix_[i][j];
    }
  }
  *this = std::move(tmp);
}

void Matrix::editCols(const int newCols) {
  if (newCols < 0) {
    throw std::logic_error("index is outside the matrix");
  }
  Matrix tmp(rows_, newCols);
  int actualCols = std::min(cols_, newCols);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < actualCols; j++) {
      tmp.matrix_[i][j] = matrix_[i][j];
    }
  }
  *this = std::move(tmp);
}

bool Matrix::empty() {
  bool answer = false;
  answer =
      ((cols_ == 0) && (rows_ == 0) && (matrix_ == nullptr)) ? true : false;
  return answer;
}

void Matrix::clear() {
  this->~Matrix();
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}
}  // namespace my_viewer