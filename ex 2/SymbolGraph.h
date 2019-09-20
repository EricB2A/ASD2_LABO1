/* 
 * File:   SymbolGraph.h
 * Author: Olivier Cuisenaire
 * Modified: Valentin Minder (2018), Raphaël Racine (2018), Antoine Rochat (2019)
 *
 * Created on 26. septembre 2014, 15:08
 */

#ifndef SYMBOLGRAPH_H
#define	SYMBOLGRAPH_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>

#include "Util.h"

template<typename GraphType>
class SymbolGraph
{
    typedef GraphType Graph; 
private:
    Graph* g;
    // A IMPLEMENTER: vos structures privées ici.
    
public:
    
    ~SymbolGraph()
    {
        delete g; 
    }            
    
    //creation du SymbolGraph a partir du fichier movies.txt
    SymbolGraph(const std::string& filename) {
        /* A IMPLEMENTER */
        // Indication: nous autorisons une double lecture du fichier.

        // exemple de lecture du fichier, ligne par ligne puis element par element (separe par des /)
        std::string line;

        std::ifstream s(filename);
        while (std::getline(s, line))
        {
            auto names = split(line,'/');
            
            for( auto name : names ) {
                std::cout << name << " ";
            }
            
            std::cout << std::endl;
        }
        s.close();
    }
    
    //verifie la presence d'un symbole
    bool contains(const std::string& name) const {
        /* A IMPLEMENTER */
    }
    
    //index du sommet correspondant au symbole
    int index(const std::string& name) const {
         /* A IMPLEMENTER */
    }
    
    //symbole correspondant au sommet
    std::string symbol(int idx) const {
        /* A IMPLEMENTER */
    }

    //symboles adjacents a un symbole
    std::vector<std::string> adjacent(const std::string& name) const {
        /* A IMPLEMENTER */
    }
    
    const Graph& G() const {
        return *g; 
    }
    
};


#endif	/* SYMBOLGRAPH_H */
