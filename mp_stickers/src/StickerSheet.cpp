#include "StickerSheet.h"
#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <vector>
#include <math.h>

using namespace cs225;

//Note to self: You need to keep track of the stickers' x and y positions.
//Make yourself a struct


StickerSheet::StickerSheet(const Image& picture, unsigned max):
    base_(new Image(picture)), stickers_(std::vector<sticker>()), max_(max) {
    //Constructor
}
StickerSheet::~StickerSheet() {
    delete base_;
    stickers_.clear();
}
StickerSheet::StickerSheet(const StickerSheet& other): 
    base_(new Image(*(other.base_))), 
    stickers_(std::vector<sticker>(other.stickers_)), 
    max_(other.max_) {
    //copy constructor
}
int StickerSheet::addSticker(Image& image, unsigned x, unsigned y) {
    if(stickers_.size() >= max_) {
        return -1;
    }
    if(x > base_->width()) {
        return -1;
    }
    if(y > base_->height()) {
        return -1;
    }
    stickers_.push_back(sticker(image, x, y));
    return stickers_.size();
}
void StickerSheet::changeMaxStickers(unsigned max) {
    //Change the max. If it is less than current size, remove the stickers that fall out of bounds.
    if(stickers_.size() > max) {
        stickers_.erase(stickers_.begin() + max, stickers_.end());
    }
    max_ = max;
}
Image * StickerSheet::getSticker(unsigned index) {
    if(index >= stickers_.size()) {
        return NULL;
    }
    return &stickers_[index].image_;
}
const StickerSheet & StickerSheet::operator=(const StickerSheet& other) {
    if(this == &other) {
        return *this;
    }
    delete base_;
    base_ = new Image(*(other.base_));
    max_ = other.max_;
    stickers_ = other.stickers_;
    return *this;
}
void StickerSheet::removeSticker(unsigned index) {
    //Vector remove method
    if (index < stickers_.size()) {
        stickers_.erase(stickers_.begin() + index);
    }
}
Image StickerSheet::render() const {
    //EZ
    Image rendered(*base_);
    for(unsigned i = 0; i < stickers_.size(); i++) {
        insertStickerHelper(rendered, stickers_[i]);
    }
    return rendered;
}
bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
    //EZ
    if(index >= stickers_.size()) {
        return false;
    }
    if(x > base_->width()) {
        return false;
    }
    if(y > base_->height()) {
        return false;
    }
    stickers_[index].x_ = x;
    stickers_[index].y_ = y;
    return true;
}

void StickerSheet::insertStickerHelper(Image &modified, const sticker &insertion) const {
    unsigned new_width = std::max(modified.width(), insertion.x_ + insertion.image_.width());
    unsigned new_height = std::max(modified.height(), insertion.y_ + insertion.image_.height());
    if (modified.width() != new_width || modified.height() != new_height) {
        modified.resize(new_width, new_height);
    }
    for(unsigned y = 0; y < insertion.image_.height(); y++) {
        for(unsigned x = 0; x < insertion.image_.width(); x++) {
            if(insertion.image_.getPixel(x, y).a != 0) {
                modified.getPixel(x + insertion.x_, y + insertion.y_) = insertion.image_.getPixel(x, y);
            }
        }
    }
}

/*  Old implementation which had the sticker cut off bounds.
void StickerSheet::insertStickerHelper(Image &modified, const sticker &insertion) const {
    unsigned y_max = std::min(insertion.image_.height(), modified.height() - insertion.y_);
    unsigned x_max = std::min(insertion.image_.width(), modified.width() - insertion.x_);
    for(unsigned y = 0; y < y_max; y++) {
        for(unsigned x = 0; x < x_max; x++) {
            if(insertion.image_.getPixel(x, y).a != 0) {
                modified.getPixel(x + insertion.x_, y + insertion.y_) = insertion.image_.getPixel(x, y);
            }
        }
    }
}
*/
//Default vector copy functionality is not working. Make a copy helper function which does this element-wise.
/*
void StickerSheet::copy(const StickerSheet& other) {
    base_ = new Image(*(other.base_));
    for(unsigned i = 0; i < other.stickers_.size(); i++) {
        stickers_.push_back(sticker(other.stickers_[i]));
    }
}
*/