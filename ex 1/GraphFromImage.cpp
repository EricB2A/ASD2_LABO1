#include "GraphFromImage.h"

using namespace std;
GraphFromImage::GraphFromImage(const bitmap_image& i) : image(i) {
}

// throws std::out_of_range
GraphFromImage::Iterable GraphFromImage::adjacent(int v) const {
    if (isIdxOutOfRange(v)) throw out_of_range("coordonnées du pixel invalide");
    Iterable neighbours;

    // add pixel from right side only if the pixel is not in the first column
    if ((unsigned) x(v) > 0 && isPixelSameColor(v, v - 1)) {
        neighbours.push_back(v - 1);
    }

    // add pixel from left side only if the pixel is not in the last column
    if ((unsigned) x(v) < (image.width() - 1) && isPixelSameColor(v, v + 1)) {
        neighbours.push_back(v + 1);
    }

    // add pixel from above only if the pixel is  not in the first row
    if (y(v) > 0 && isPixelSameColor(v, v - (int) image.width())) {
        neighbours.push_back(v - (int) image.width());
    }

    // add pixel from below only if the pixel is not in the last row
    if ((unsigned) y(v) < (image.height() - 1)
        && isPixelSameColor(v, v + (int) image.width())) {
        neighbours.push_back(v + (int) image.width());
    }
    return neighbours;
}

// throws std::out_of_range
int GraphFromImage::idx(int x, int y) const {
    if ((unsigned) x >= image.width() || (unsigned) y >= image.height() || x < 0
        || y < 0)
        throw new std::out_of_range("coordonnées du pixel invalide");
    return y * (int) image.width() + x;
}

// throws std::out_of_range
int GraphFromImage::x(int idx) const {
    if (isIdxOutOfRange(idx))
        throw new std::out_of_range("coordonnées du pixel invalide");
    return idx % (int) image.width();
}

// throws std::out_of_range
int GraphFromImage::y(int idx) const {
    if (isIdxOutOfRange(idx))
        throw new std::out_of_range("coordonnées du pixel invalide");
    return idx / (int) image.width();
}

int GraphFromImage::V() const {
    return (int) (image.width() * image.height());
}
bool GraphFromImage::isIdxOutOfRange(int idx) const {
    return (unsigned) idx > (image.width() * image.height()) - 1 || idx < 0;
}
bool GraphFromImage::isPixelSameColor(const int lPixel,
                                      const int rPixel) const {
    unsigned char lR, lG, lB;
    unsigned char rR, rG, rB;

    image.get_pixel((unsigned) x(lPixel), (unsigned) y(lPixel), lR, lG, lB);
    image.get_pixel((unsigned) x(rPixel), (unsigned) y(rPixel), rR, rG, rB);

    return (lR == rR && lG == rG && lB == rB);
}
