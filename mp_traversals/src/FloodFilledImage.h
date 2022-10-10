/**
 * @file FloodFilledImage.h
 * Definition for a class to do flood fill on an image
 */
#pragma once

#include "cs225/PNG.h"
#include <list>
#include <iostream>
#include <vector>

#include "colorPicker/ColorPicker.h"
#include "imageTraversal/ImageTraversal.h"

#include "Point.h"
#include "Animation.h"

using namespace cs225;
/**
 * This class is used to do flood fill on an image.
 * One or more FloodFill operations will be added and executed in the order they
 * are added in. Each operation should flood-fill the entire image. Each operation
 * should have its own traversal method and color picker.
 */
class FloodFilledImage {
public:
  FloodFilledImage(const PNG & png);
  void addFloodFill(ImageTraversal & traversal, ColorPicker & colorPicker);
  Animation animate(unsigned frameInterval) const;
  ~FloodFilledImage();

private:
	/** @todo [Part 2] */
	/** add private members here*/
  //const PNG* image_;
  PNG* image_;
  std::vector<ImageTraversal*> traversals_;
  std::vector<ColorPicker*> colors_;

};

// Note to self: since the image animations all seem to happen once
// and the tests are in the exact same scope, and the flood fill is called once,
// Pointers will be utilized to track objects.
// A heap png image will be used. This entails that traversals will always behave with respect to the old image.
// This is due to issues with modifying png.
// Note that this does entail that scope deletions will cause errors.