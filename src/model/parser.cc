#include "parser.h"

// ПОТОКИ ОЧЕНЬ МЕДЛЕННЫЕ ПОЭТОМУ ПЕРЕПИСАЛА ПАРСЕР Ф :((

namespace my_viewer {
void Parser::parseV(std::string line, Vertex *vert) {
  std::vector<float> tempCoord;
  float x = 0, y = 0, z = 0;

  std::istringstream iss(line.substr(2));
  iss >> x >> y >> z;

  vert->coord.resize((vert->amountVert + 1) * 3);

  vert->xInfo[0] = std::min(x, vert->xInfo[0]);
  vert->xInfo[1] = std::max(x, vert->xInfo[1]);

  vert->yInfo[0] = std::min(y, vert->yInfo[0]);
  vert->yInfo[1] = std::max(y, vert->yInfo[1]);

  vert->zInfo[0] = std::min(z, vert->zInfo[0]);
  vert->zInfo[1] = std::max(z, vert->zInfo[1]);

  vert->coord.resize((vert->amountVert + 1) * 3, 0.0f);
  vert->coord[vert->amountVert * 3] = x;
  vert->coord[vert->amountVert * 3 + 1] = y;
  vert->coord[vert->amountVert * 3 + 2] = z;
  vert->amountVert++;
}

void Parser::parseF(std::string line, Results *res) {
  int skip = 0, edges = 0;
  double x;
  std::string start = line.substr(2);
  std::string token;

  Polygon pol;
  pol.amountP = 0;
  std::vector<int> temp;

  for (auto ch = start.begin(); ch <= start.end(); ch++) {
    if (ch == start.end()) {
      if (!token.empty()) {
        x = stof(token);
        skip = ((ceilf(x) != x) || (x == 0)) ? 1 : skip;
        pol.p.push_back(x);
        pol.amountP++;
        edges++;
        token.clear();
      }
      break;
    }
    if (((*ch) >= '0' && (*ch) <= '9') || (*ch) == '.') {
      token += (*ch);
    } else if (*ch == '/') {
      token += ' ';
    } else if (*ch == ' ' || *ch == '\n') {
      if (!token.empty()) {
        x = stof(token);
        skip = ((ceilf(x) != x) || (x == 0)) ? 1 : skip;

        pol.p.push_back(x);
        pol.amountP++;
        edges++;
        token.clear();
      }
    } else if ((*ch) == 'e') {
      token += (*ch);
    } else {
      skip = 1;
      break;
    }
  }
  if (!skip && pol.amountP > 0) {
    res->amountPols++;
    res->p.push_back(pol);
    res->totalEdges += edges;
  } else {
    pol.amountP--;
    pol.p.clear();
  }
}

void Parser::parseFromFile(Results *res, std::string nameOfFile) {
  std::ifstream objFile(nameOfFile);
  std::string line;
  if (objFile.is_open()) {
    while (std::getline(objFile, line)) {
      if (line[0] == 'v' && line[1] == ' ') {
        parseV(line, &res->v);

      } else if (line[0] == 'f' && line[1] == ' ') {
        parseF(line, res);
      }
    }
    objFile.close();
  } else {
    throw std::logic_error("no such file");
  }
}

void Parser::getIndexes(Results *res) {
  std::vector<int> temp;
  for (int i = 0; i < res->amountPols; i++) {
    if (res->v.amountVert < res->p[i].p[0]) {
      throw std::logic_error("invalid input");
    }
    temp.push_back(res->p[i].p[0] - 1);
    for (int j = 1; j < res->p[i].amountP; j++) {
      if (res->v.amountVert < res->p[i].p[j]) {
        throw std::logic_error("invalid input");
      }
      temp.push_back(res->p[i].p[j] - 1);
      temp.push_back(res->p[i].p[j] - 1);
    }
    temp.push_back(res->p[i].p[0] - 1);
  }
  res->indexes = temp;
}

}  // namespace my_viewer
