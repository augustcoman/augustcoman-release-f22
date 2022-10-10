#include "cs225/HSLAPixel.h"
#include "../Point.h"
#include "cs225/PNG.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  unsigned x_c = x % repeated_image_->width();
  unsigned y_c = y % repeated_image_->height();
  return repeated_image_->getPixel(x_c, y_c);
}

MyColorPicker::MyColorPicker(const PNG& png): repeated_image_(new PNG(png)) {
  //
}

MyColorPicker::~MyColorPicker() {
  delete repeated_image_;
}