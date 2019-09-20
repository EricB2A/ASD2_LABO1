/* 
 * File:   ex1.cpp
 * Author: Olivier Cuisenaire
 *
 * Created on 2 oct. 2014, 11:19:03
 */

#include <stdlib.h>
#include <iostream>

#include "GraphFromImage.h"
#include "ParcoursEnProfondeur.h"

int main(int argc, char** argv) {
    
    std::string filename("input.bmp");
    bitmap_image image(filename);
    
    if (!image) {
        std::cout << "test1 : Failed to open " << filename << ") \n";
        return (EXIT_FAILURE);
    }
    
    std::cout << "image size: " << image.width() << " x " << image.height() << "\n";
    
    GraphFromImage G(image);
    DFS<GraphFromImage> dfs(G);

    //Question BONUS: Pourquoi n'utilisons-nous pas la methode visite pour parcourir l'image ?
    
    //on colore le centre de la pomme
    dfs.iterativeVisit( G.idx(250, 400), [&G, &image] (int v) {
        image.set_pixel( G.x(v), G.y(v), 250, 150, 64);
    });
    
    // on colore la feuille en haut de la pomme
    dfs.iterativeVisit( G.idx(225, 100), [&G, &image] (int v) {
        image.set_pixel( G.x(v), G.y(v), 0, 225, 0);
    });
    
    // on ajoute une couleur de fond
    dfs.iterativeVisit( G.idx(50, 50), [&G, &image] (int v) {
        image.set_pixel( G.x(v), G.y(v), 150, 220, 255);
    });
    
    //on sauve l'image modifiee
    image.save_image("output.bmp");
    
    
    //on charge l'image temoin pour verifier notre code
    bitmap_image image_gold("goal.bmp");
    
    if(image.psnr(image_gold) < 1000000)
        std::cout  << "test failed - psnr = " << image.psnr(image_gold)  << ") \n";
    else
        std::cout << "test succeeded - image is identical to goal.bmp\n";
    
    return (EXIT_SUCCESS);
    
}

