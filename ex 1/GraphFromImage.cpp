#include "GraphFromImage.h"

GraphFromImage::GraphFromImage(const bitmap_image& i) : image(i) {
    /* A IMPLEMENTER */
}

bool GraphFromImage::estDeMemeCouleur(int idx, int idx2) const{
    unsigned char r1, g1, b1, r2, g2, b2;
    image.get_pixel(x(idx), y(idx), r1, g1, b1);
    image.get_pixel(x(idx2), y(idx2), r2, g2, b2);
    return r1 == r2 && g1 == g2 && b1 == b2;
}
// throws std::out_of_range
GraphFromImage::Iterable GraphFromImage::adjacent(int v) const {
    if (v >= V() || v < 0) throw std::out_of_range("out_of_range");

    Iterable cotesPossibles, cotesAdjacents;

    if (x(v) > 0) cotesPossibles.push_back(v - 1);
    if (x(v) < image.width() - 1) cotesPossibles.push_back(v + 1);
    if (y(v) > 0) cotesPossibles.push_back(v - image.width());
    if (y(v) < image.height() - 1) cotesPossibles.push_back(v + image.width());

    for(auto cotePossible : cotesPossibles) {
        if(estDeMemeCouleur(v, cotePossible)){
            cotesAdjacents.push_back(cotePossible);
        }
    }
    return cotesAdjacents;
}

// throws std::out_of_range
int GraphFromImage::idx(int x, int y) const {
    if (x >= image.width() || x < 0 || y >= image.height() || y < 0) throw std::out_of_range("out_of_range");

    return x + (y * image.width());
}

// throws std::out_of_range
int GraphFromImage::x(int idx) const {
    if (idx >= V() || idx < 0) throw std::out_of_range("out_of_range");

    return  idx % image.width();
}

// throws std::out_of_range
int GraphFromImage::y(int idx) const {
    if (idx >= V() || idx < 0) throw std::out_of_range("out_of_range");

    return (idx - x(idx)) / image.width();
}

int GraphFromImage::V() const {
    return image.width() * image.height();
}
