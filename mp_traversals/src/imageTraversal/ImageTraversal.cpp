#include <cmath>
#include <iterator>
#include <iostream>

#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator(): traversal_(NULL) {
  /** @todo [Part 1] */
  current_ = Point(0, 0); //Note that this is to initialize. It does not matter here.
}

ImageTraversal::Iterator::Iterator(ImageTraversal * traversal): traversal_(traversal) {
  current_ = traversal_->peek();
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  if(!traversal_->empty()) {
    current_ = traversal_->pop();
    //Note: letting traversal handle upper bounds.
    traversal_->add(Point(current_.x + 1, current_.y));
    traversal_->add(Point(current_.x, current_.y + 1));
    if(current_.x > 0) {
      traversal_->add(Point(current_.x - 1, current_.y));
    }
    if(current_.y > 0) {
      traversal_->add(Point(current_.x, current_.y - 1));
    }
    current_ = traversal_->peek();
  }
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return current_;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  bool empty_this = (!traversal_ || traversal_->empty());
  bool empty_other = (!other.traversal_ || other.traversal_->empty());
  if (empty_this && empty_other) {
    return false;
  }
  if (!empty_this && !empty_other) {
    return !(current_ == other.current_);
  }
  return true;
}

double ImageTraversal::calcDelta(const HSLAPixel &p1, const HSLAPixel &p2) {
  return calculateDelta(p1, p2);
}