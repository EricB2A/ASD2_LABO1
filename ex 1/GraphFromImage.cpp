#include "GraphFromImage.h"

GraphFromImage::GraphFromImage(const bitmap_image& i) : image(i) {
    /* A IMPLEMENTER */
}

// throws std::out_of_range
GraphFromImage::Iterable GraphFromImage::adjacent(int v) const {
    // Cellcules adjacentes
    Iterable adjacents;

    if(v < 0 || v >= V()){
        throw std::out_of_range("Pixel hors de l'image.");
    }

    int coord_x = x(v);
    int coord_y = y(v);
    unsigned char red, green, blue;
    image.get_pixel(coord_x, coord_y, red, green, blue);


    // Pixel voisin haut
    if(coord_y - 1 >= 0 && estPixelMemeCouleur(coord_x, coord_y - 1, red, green, blue)){
        adjacents.push_back(idx(coord_x, coord_y - 1));
    } 
    
     // Pixel voisin droite  
    if(coord_x + 1 < image.width() && estPixelMemeCouleur(coord_x + 1, coord_y, red, green, blue)){
        adjacents.push_back(idx(coord_x + 1, coord_y));
    }

     // Pixel voisin bas
    if(coord_y + 1 < image.height() && estPixelMemeCouleur(coord_x, coord_y + 1, red, green, blue)){
        adjacents.push_back(idx(coord_x, coord_y + 1));
    } 

    // Pixel voisin gauche  
    if(coord_x - 1 >= 0 && estPixelMemeCouleur(coord_x - 1, coord_y, red, green, blue)){
        adjacents.push_back(idx(coord_x - 1, coord_y));
    }
    
    return adjacents;
}

// throws std::out_of_range
int GraphFromImage::idx(int x, int y) const {
    return x + image.width() * y;
}

// throws std::out_of_range
int GraphFromImage::x(int idx) const {
    return idx % image.width();
}

// throws std::out_of_range
int GraphFromImage::y(int idx) const {
    return idx / image.width();
}

int GraphFromImage::V() const {
    return image.width() * image.height();
}

bool GraphFromImage::estPixelMemeCouleur(int x, int y, unsigned red, unsigned green, unsigned blue) const {
    unsigned char r, g, b;
    image.get_pixel(x, y, r, g, b);
    return red == r && green == g && blue == b;
}
