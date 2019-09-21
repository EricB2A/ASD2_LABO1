#include "GraphFromImage.h"

using namespace std;
GraphFromImage::GraphFromImage(const bitmap_image& i) : image(i) {
}

// throws std::out_of_range
GraphFromImage::Iterable GraphFromImage::adjacent(int v) const {
    Iterable neighbours;

    // add pixel from right side only if the pixel is not in the first column
    if ((unsigned) x(v) > 0 && pixelsSameColor(v, v - 1)) {
        neighbours.push_back(v - 1);
    }

    // add pixel from left side only if the pixel is not in the last column
    if ((unsigned) x(v) < (image.width() - 1) && pixelsSameColor(v, v + 1)) {
        neighbours.push_back(v + 1);
    }

    // add pixel from above only if the pixel is  not in the first row
    if (y(v) > 0 && pixelsSameColor(v, v - image.width())) {
        neighbours.push_back(v - image.width());
    }

    // add pixel from below only if the pixel is not in the last row
    if ((unsigned) y(v) < (image.height() - 1)
        && pixelsSameColor(v, v + image.width())) {
        neighbours.push_back(v + image.width());
    }
    return neighbours;
}

// throws std::out_of_range
int GraphFromImage::idx(int x, int y) const {
    if ((unsigned) x >= image.width() || (unsigned) y >= image.height())
        throw new std::out_of_range("Sac à vin");
    return y * image.width() + x;
}

// throws std::out_of_range
int GraphFromImage::x(int idx) const {
    if (isIdxOutOfRange(idx))
        throw new std::out_of_range("Sac à vin");
    return (unsigned) idx % image.width();
}

// throws std::out_of_range
int GraphFromImage::y(int idx) const {
    if (isIdxOutOfRange(idx))
        throw new std::out_of_range("Sac à vin");
    return (unsigned) idx / image.width();
}

int GraphFromImage::V() const {
    return (int) (image.width() * image.height());
}
bool GraphFromImage::isIdxOutOfRange(int idx) const
{
    return (unsigned) idx > (image.width() * image.height()) - 1;
}
bool GraphFromImage::pixelsSameColor(const int lPixel, const int rPixel) const {
    unsigned char lR, lG, lB;
    unsigned char rR, rG, rB;

    image.get_pixel(x(lPixel), y(lPixel), lR, lG, lB);
    image.get_pixel(x(rPixel), y(rPixel), rR, rG, rB);

    return (lR == rR && lG == rG && lB == rB);
}
