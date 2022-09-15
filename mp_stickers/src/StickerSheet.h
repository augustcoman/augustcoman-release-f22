/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once

#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <vector>

using namespace cs225;

class StickerSheet {
    public:
    struct sticker {
        Image image_; 
        unsigned x_;
        unsigned y_;
        sticker(): image_(Image()), x_(0), y_(0) {
            //Default constructor for use in vector.
        }
        sticker(Image& image, unsigned x, unsigned y): image_(image), x_(x), y_(y) {
            //Parametrized constructor
        }
        sticker(const sticker& other): image_(other.image_), x_(other.x_), y_(other.y_) {
            //copy constructor
        }
        sticker& operator=(const sticker& other) {
            if (this != &other) {
                this->image_ = other.image_;
                this->x_ = other.x_;
                this->y_ = other.y_;
            }
            return *this;
        }
    };
    /** Constructor which takes a deep copy of picture as its base image, and a specified
     * maximum number of stickers.
     * @param picture The Image object to be deep copied, used as base image.
     * @param max The maximum number of 
     */
    StickerSheet(const Image& picture, unsigned max);
    // Frees up all dynamic memory in StickerSheet.
    ~StickerSheet();
    /** Copy constructor which creates a deep copy.
     * @param other the other StickerSheet to copy data from
     */
    StickerSheet(const StickerSheet& other);
    /** Adds a sticker image to StickerSheet so that the top-left of the sticker is at
     * x, y from the image
     * @param sticker The sticker Image to add
     * @param x the x coordinate of the top left coner of the sticker
     * @param y the y coordinate of the top left coner of the sticker
     * @returns The index of the sticker amongst the layers, or -1 if the sticker cannot be added.
     */
    int addSticker(Image& image, unsigned x, unsigned y);
    /** Modifies the maximum number if stickers that can be stored
     * Note: objects that fall outside of the new maximum will be deleted if shrinking.
     * @param max The new max sticker count
     */
    void changeMaxStickers(unsigned max);
    /** Returns a pointer to the sticker at the specified index. This allows for modification
     * @param index The index to retrieve the sticker from.
     * @returns A pointer to the specific Image in the StickerSheet, or NULL if invalid index.
     */
    Image * getSticker(unsigned index);
    const StickerSheet & operator=(const StickerSheet& other);
    /** Removes the sticker at the given zero-based layer index
     * @param index The layer in which to delete the image
     */
    void removeSticker(unsigned index);
    /** Renders the whole StickerSheet on the base image
     * @returns an Image with the stickers pixels
     */
    Image render() const;
    /** Changes the x and y coordinates of the image at the specified layer.
     * Note that the returned image will be enlarged if the sticker is out of bounds.
     * Also note that this does not support alpha blending.
     * @param index the index of the sticker to be moved
     * @param x the x coordinate to move the sticker
     * @param y the y coordinate to move the sticker.
     * @returns true if the translation was successful, false otherwise
     */
    bool translate(unsigned index, unsigned x, unsigned y);
    private:
    Image *base_;
    std::vector<sticker> stickers_;
    unsigned max_;
    //Helper function to render stickers onto the image.
    void insertStickerHelper(Image &modified, const sticker &insertion) const;
};

//My plan here is keep this a dynamic array. It will be resized when "max" is ever changed
// Initially I was thinking of using Image *images_; array
//To maintain simplicity, I can simply use a vector. I can push, pop, and delete.