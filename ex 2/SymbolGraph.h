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
#include <map>
#include "Util.h"

template<typename GraphType>
class SymbolGraph
{
    typedef GraphType Graph; 
private:
    Graph* g;
    std::vector<std::string> symbols;
    std::map<std::string, int> indices;
    
public:
    
    ~SymbolGraph()
    {
        delete g; 
    }            
    
    //creation du SymbolGraph a partir du fichier movies.txt
    SymbolGraph(const std::string& filename) {
        std::string line;
        unsigned cnt = 0;

        std::ifstream s(filename);
        while (std::getline(s, line))
        {
            auto names = split(line,'/');
            std::string movie_title = names.front(); 
            //std::cout << movie_title;
            symbols.push_back(movie_title);
            indices[movie_title] = cnt;
            for( auto name : names ) {
                //std::cout << name << " ";
                symbols.push_back(name);
                indices[symbols[cnt]] = cnt;
                cnt++;
                
            }
            
            //std::cout << std::endl;

        }

        s.clear();
      s.seekg(0, std::ios::beg);

      // init the graph with the number of symbols/indices/"nodes"
      g = new Graph(symbols.size());

      // browse the file again and add the edges between the movie and the actors
      while (std::getline(s, line)) {
          std::vector<std::string> names = split(line, '/');
          int movieNum = indices[names[0]];

          for (unsigned i = 1; i < names.size(); ++i) {
              g->addEdge(movieNum, indices[names[i]]);
          }

      }
      s.close();
        
    }
    
    //verifie la presence d'un symbole
    bool contains(const std::string& name) const {
        /* A IMPLEMENTER */
        return std::find(symbols.begin(), symbols.end(), name) != symbols.end();
    }
    
    //index du sommet correspondant au symbole
    int index(const std::string& name) const {
         /* A IMPLEMENTER */
        return indices.at(name);
    }
    
    //symbole correspondant au sommet
    std::string symbol(int idx) const {
        /* A IMPLEMENTER */
        return symbols.at(idx);
    }

    //symboles adjacents a un symbole
    std::vector<std::string> adjacent(const std::string& name) const {
        /* A IMPLEMENTER */
        std::vector<std::string> adjacents;

        for (int i : g->adjacent(index(name))) {
            adjacents.push_back(this->symbol(i));
        }

        return adjacents;
    }
    
    const Graph& G() const {
        return *g; 
    }
    
};


#endif	/* SYMBOLGRAPH_H */
