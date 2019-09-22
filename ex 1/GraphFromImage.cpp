#include "GraphFromImage.h"

GraphFromImage::GraphFromImage(const bitmap_image& i) : image(i) {
    /* A IMPLEMENTER */
}

// throws std::out_of_range
GraphFromImage::Iterable GraphFromImage::adjacent(int v) const {
    // Cellcules adjacentes
    Iterable adjacents;

    if(!estPixelDansImage(v)){
        throw std::out_of_range("Pixel hors de l'image.");
    }

    int coord_x = x(v);
    int coord_y = y(v);
    unsigned char red, green, blue;
    image.get_pixel(coord_x, coord_y, red, green, blue);

    if(!v || v > image.width() * image.height()){
       throw std::out_of_range("Pixel hors de l'image.");
    }

    // Position des voisins relative à pixel voulu.
    // Ordre de parcours : haut, droite, bas, gauche
    int voisins[] = {-((int) image.width()), 1, (int) image.width(), -1};

    for (size_t i = 0; i < sizeof(voisins) / sizeof(int); ++i){
        int pixel_voisin = v += voisins[i];
        if(estPixelDansImage(pixel_voisin) && estPixelMemeCouleur(x(pixel_voisin), y(pixel_voisin), red, green, blue)){
            adjacents.push_back(pixel_voisin);
        }
        
    }
    return adjacents;
}

// throws std::out_of_range
int GraphFromImage::idx(int x, int y) const {
    return x * image.width() * y;
}

// throws std::out_of_range
int GraphFromImage::x(int idx) const {
    return idx / image.width();
}

// throws std::out_of_range
int GraphFromImage::y(int idx) const {
    return idx % image.width();
}

int GraphFromImage::V() const {
    return image.width() * image.height();
}

bool GraphFromImage::estPixelMemeCouleur(int x, int y, unsigned red, unsigned green, unsigned blue) const {
    unsigned char r, g, b;
    image.get_pixel(x, y, r, g, b);
    return red == r && green == g && blue == b;
}

bool GraphFromImage::estPixelDansImage(int v) const {
    return v > 0 && v <= V();
}
