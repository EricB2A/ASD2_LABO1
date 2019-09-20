#include "GraphFromImage.h"

GraphFromImage::GraphFromImage(const bitmap_image& i) : image(i) {
    /* A IMPLEMENTER */
}

// throws std::out_of_range
GraphFromImage::Iterable GraphFromImage::adjacent(int v) const {
    /* A IMPLEMENTER */
}

// throws std::out_of_range
int GraphFromImage::idx(int x, int y) const {
    /* A IMPLEMENTER */
}

// throws std::out_of_range
int GraphFromImage::x(int idx) const {
    /* A IMPLEMENTER */
}

// throws std::out_of_range
int GraphFromImage::y(int idx) const {
    /* A IMPLEMENTER */
}

int GraphFromImage::V() const {
    /* A IMPLEMENTER */
}
