/*
 * File:   SymbolGraph.h
 * Author: Olivier Cuisenaire
 * Modified: Valentin Minder (2018), Raphaël Racine (2018), Antoine Rochat (2019)
 * Modified: Ilias Goujgali (2019), Eric Bousbaa (2019), Fabio Marques (2019)
 *
 * Created on 26. septembre 2014, 15:08
 */

#ifndef SYMBOLGRAPH_H
#define SYMBOLGRAPH_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>
#include <vector>
#include <list>
#include "Util.h"
#include <string>



template<typename GraphType>
class SymbolGraph {
  typedef GraphType Graph;
 private:
  Graph* graph;
  std::vector<std::string> symbols; // contains the names of the nodes by indice
  std::map<std::string, int> indices; // contains the indices by name of the node

 public:

  ~SymbolGraph() {
      delete graph;
  }

  //creation du SymbolGraph a partir du fichier movies.txt
  SymbolGraph(const std::string& filename) {
      /* A IMPLEMENTER */
      // Indication: nous autorisons une double lecture du fichier.
      // exemple de lecture du fichier, ligne par ligne puis element par element (separe par des /)
      std::string line;

      std::ifstream s(filename);
      int count = 0;
      std::map<std::string, int>::iterator it;

      // read file and populate the "symbols" vector and the "indices" map
      while (std::getline(s, line)) {
          std::vector<std::string> names = split(line, '/');

          // the first name of the line is the movie title
          std::string movieTitle = names[0];
          symbols.push_back(movieTitle);
          indices[movieTitle] = count++;

          // add the actors
          for (unsigned i = 1; i < names.size(); ++i) {

              // if there is no entry for this name we add it - to avoid counting existing vertex
              it = indices.find(names[i]);

              if (it == indices.end()) {
                  symbols.push_back(names[i]);
                  indices[names[i]] = count++;
              }
          }
      }
      // return to the file 's beginning
      s.clear();
      s.seekg(0, std::ios::beg);

      // init the graph with the number of symbols/indices/"nodes"
      graph = new Graph(symbols.size());

      // browse the file again and add the edges between the movie and the actors
      while (std::getline(s, line)) {
          std::vector<std::string> names = split(line, '/');
          int movieNum = indices[names[0]];

          for (unsigned i = 1; i < names.size(); ++i) {
              graph->addEdge(movieNum, indices[names[i]]);
          }

      }
      s.close();
  }

  //verifie la presence d'un symbole
  bool contains(const std::string& name) const {
      return indices.find(name) != indices.end();
  }

  //index du sommet correspondant au symbole
  int index(const std::string& name) const {
      return indices.at(name);
  }

  //symbole correspondant au sommet
  std::string symbol(int idx) const {
      return symbols.at(idx);
  }

  //symboles adjacents a un symbole
  std::vector<std::string> adjacent(const std::string& name) const {
      std::vector<std::string> neighboursNames;
      const std::list<int> neighboursIdxList = graph->adjacent(indices.at(name));

      for (int neighboursIdx : neighboursIdxList) {
          neighboursNames.push_back(symbols[neighboursIdx]);
      }

      return neighboursNames;
  }

  const Graph& G() const {
      return *graph;
  }

};

#endif    /* SYMBOLGRAPH_H */
