/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */

#pragma once

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

using namespace cs225;

class Image: public PNG {
    // Note to developer: Assuming use of default constructor
    public:
    /** Lightens an Image by decreasing the luminance of every pixel by 0.1
      * Ensures that the luminance remains in the range [0, 1]
      */
    void lighten();

    /** Lightens an Image by decreasing the luminance of every pixel by amount
      * Ensures that the luminance remains in the range [0, 1]
      * @param amount the desired increase in luminance
      */
    void lighten(double amount);

    /** Darkens an Image by decreasing the luminance of every pixel by 0.1
      * Ensures that the luminance remains in the range [0, 1]
      */
    void darken();

    /** Darkens an Image by decreasing the luminance of every pixel by amount
      * Ensures that the luminance remains in the range [0, 1]
      * @param amount the desired decrease in luminance
      */
    void darken(double amount);

    /** Increases saturation of each pixel in Image by 0.1
      * Ensures saturation remains in range [0, 1]
      */
    void saturate();

    /** Increases saturation of each pixel in Image by amount
      * Ensures saturation remains in range [0, 1]
      * @param amount the desired increase in saturation
      */
    void saturate(double amount);

    /**
      */
    void desaturate();

    /**
      */
    void desaturate(double amount);

    /** Sets all pixel saturations in the image to 0
      */
    void grayscale();

    /** Rotates the color wheel of each pixel by degrees
      * Ensures that hue remains in range [0, 360]. Is positive in increase.
      * @param degrees The desired amount of rotation
      */
    void rotateColor(double degrees);

    /** Transforms an Image to illini colors.
      * This sets the hue of each pixel to 11 or 216 depending on what it is closer to
      */
    void illinify();

    /** Scales the Image by a given factor
      * This resizes the image and scales the contents
      * @param factor Scale factor
      */
    void scale(double factor);

    /** Scales the Image to fit within width times height.
      * This will however preserve the aspect ratio, and use the smallest scale difference.
      * @param w Desired width of scaled Image
      * @param h Desired height of scaled Image
      */
    void scale(unsigned w, unsigned h);
};