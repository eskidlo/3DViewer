#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "builder.h"

namespace my_viewer {
class Parser {
 public:
  Parser() {}
  Parser(const Parser &p) = default;
  Parser(Parser &&p) = default;
  Parser &operator=(const Parser &p) = default;
  Parser &operator=(Parser &&p) = default;
  ~Parser() {}

  void parseFromFile(Results *res, std::string nameOfFile);
  void parseF(std::string line, Results *res);
  void parseV(std::string line, Vertex *vert);
  void getIndexes(Results *res);
};

};  // namespace my_viewer

#endif  // PARSER_H