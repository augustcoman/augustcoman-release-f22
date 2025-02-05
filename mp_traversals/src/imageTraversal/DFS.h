/**
 * @file DFS.h
 */

#pragma once

#include <iterator>
#include <cmath>
#include <list>
#include <stack>
#include <vector>

#include "cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

using namespace cs225;

/**
 * A depth-first ImageTraversal.
 * Derived from base class ImageTraversal
 */
class DFS : public ImageTraversal {
public:
  DFS(const PNG & png, const Point & start, double tolerance);

  ImageTraversal::Iterator begin();
  ImageTraversal::Iterator end();

  void add(const Point & point);
  Point pop();
  Point peek() const;
  bool empty() const;

private:
	/** @todo [Part 1] */
	/** add private members here*/
  const PNG* image_;
  Point start_;
  double tolerance_;
  std::stack<Point> traversal_;
  //std::vector<bool> visited_;
  std::vector<std::vector<bool>> visited_;
  bool isValid(unsigned x, unsigned y);
};
