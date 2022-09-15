#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <math.h>

using namespace cs225;

void Image::lighten() {
    for(unsigned y = 0; y < height(); y++) {
        for(unsigned x = 0; x < width(); x++) {
            double &pixel_luminance = getPixel(x, y).l;
            pixel_luminance += 0.1;
            if(pixel_luminance > 1.0) {
                pixel_luminance = 1.0;
            }
            if(pixel_luminance < 0) {
                pixel_luminance = 0;
            }
        }
    }
}

void Image::lighten(double amount) {
    for(unsigned y = 0; y < height(); y++) {
        for(unsigned x = 0; x < width(); x++) {
            double &pixel_luminance = getPixel(x, y).l;
            pixel_luminance += amount;
            if(pixel_luminance > 1.0) {
                pixel_luminance = 1.0;
            }
            if(pixel_luminance < 0) {
                pixel_luminance = 0;
            }
        }
    }
}

void Image::darken() {
    for(unsigned y = 0; y < height(); y++) {
        for(unsigned x = 0; x < width(); x++) {
            double &pixel_luminance = getPixel(x, y).l;
            pixel_luminance -= 0.1;
            if(pixel_luminance > 1.0) {
                pixel_luminance = 1.0;
            }
            if(pixel_luminance < 0) {
                pixel_luminance = 0;
            }
        }
    }
}

void Image::darken(double amount) {
    for(unsigned y = 0; y < height(); y++) {
        for(unsigned x = 0; x < width(); x++) {
            double &pixel_luminance = getPixel(x, y).l;
            pixel_luminance -= amount;
            if(pixel_luminance > 1.0) {
                pixel_luminance = 1.0;
            }
            if(pixel_luminance < 0) {
                pixel_luminance = 0;
            }
        }
    }
}

void Image::saturate() {
    for(unsigned y = 0; y < height(); y++) {
        for(unsigned x = 0; x < width(); x++) {
            double &pixel_saturation = getPixel(x, y).s;
            pixel_saturation += 0.1;
            if(pixel_saturation > 1.0) {
                pixel_saturation = 1.0;
            }
            if(pixel_saturation < 0) {
                pixel_saturation = 0;
            }
        }
    }
}

void Image::saturate(double amount) {
    for(unsigned y = 0; y < height(); y++) {
        for(unsigned x = 0; x < width(); x++) {
            double &pixel_saturation = getPixel(x, y).s;
            pixel_saturation += amount;
            if(pixel_saturation > 1.0) {
                pixel_saturation = 1.0;
            }
            if(pixel_saturation < 0) {
                pixel_saturation = 0;
            }
        }
    }
}

void Image::desaturate() {
    for(unsigned y = 0; y < height(); y++) {
        for(unsigned x = 0; x < width(); x++) {
            double &pixel_saturation = getPixel(x, y).s;
            pixel_saturation -= 0.1;
            if(pixel_saturation > 1.0) {
                pixel_saturation = 1.0;
            }
            if(pixel_saturation < 0) {
                pixel_saturation = 0;
            }
        }
    }
}

void Image::desaturate(double amount) {
    for(unsigned y = 0; y < height(); y++) {
        for(unsigned x = 0; x < width(); x++) {
            double &pixel_saturation = getPixel(x, y).s;
            pixel_saturation -= amount;
            if(pixel_saturation > 1.0) {
                pixel_saturation = 1.0;
            }
            if(pixel_saturation < 0) {
                pixel_saturation = 0;
            }
        }
    }
}

void Image::grayscale() {
    for(unsigned y = 0; y < height(); y++) {
        for(unsigned x = 0; x < width(); x++) {
            getPixel(x, y).s = 0;
        }
    }
}

void Image::rotateColor(double degrees) {
    for(unsigned y = 0; y < height(); y++) {
        for(unsigned x = 0; x < width(); x++) {
            double &pixel_hue = getPixel(x, y).h;
            pixel_hue += degrees;
            //if(pixel_hue >= 360.0) {
            //    pixel_hue -= 360.0;
            //}
            //The code below makes the hue a value below 360 and above -360. It then adds 360 if it is negative.
            pixel_hue -= 360.0 * ((int)(pixel_hue / 360)); 
            if(pixel_hue < 0) {
                pixel_hue += 360.0;
            }
        }
    }
}

//Note: orange is 11, blue is 216
void Image::illinify() {
    for(unsigned y = 0; y < height(); y++) {
        for(unsigned x = 0; x < width(); x++) {
            double &pixel_hue = getPixel(x, y).h;
            double orange = std::abs(pixel_hue - 11);
            if(orange > 180) {
                orange = 360 - orange;
            }
            double blue = std::abs(pixel_hue - 216);
            if(blue > 180) {
                blue = 360 - blue;
            }
            pixel_hue = (blue < orange)?216:11;
        }
    }
}

void Image::scale(double factor) {
    // Use nearest neighbor implementation
    if(factor < 0 || factor == 1) {
        return;
    }
    PNG resized = PNG((unsigned)(width() * factor + 0.01), (unsigned)(height() * factor + 0.01));  //Adding 0.01 to avoid floating point errors.
    //Note: if factor is zero, the below loop won't be execuded.
    for(unsigned y = 0; y < resized.height(); y++) {
        for(unsigned x = 0; x < resized.width(); x++) {
            unsigned orig_x = (unsigned)(x / factor);
            unsigned orig_y = (unsigned)(y / factor);
            resized.getPixel(x, y) = getPixel(orig_x, orig_y); //Note: may reference pixel that gets deleted later.
        }
    }
    PNG::operator=(resized);
}

void Image::scale(unsigned w, unsigned h) {
    double width_factor = w / (width() * 1.0);
    double height_factor = h / (height() * 1.0);
    scale((width_factor < height_factor?width_factor:height_factor));
}
