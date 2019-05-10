#ifndef READ_H
#define READ_H

#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <string>
#include "graph.h"

using namespace std;
class Trts {
public:
    typedef char N;
    typedef int E;
};

template <typename Tr>
class Read {
    typedef typename Tr::N N;
    typedef typename Tr::E E;
    string file;

public:
    void getGraph(graph* g1) {
      ifstream archivo;
      string line;
      long linea;
      int i = 0;
      double tempx, tempy;
      archivo.open("../Data/data.txt");
        while(!archivo.eof())
        {
          archivo>>line;
          if(line!="@")
          {
            linea = stol(line);
            archivo>>tempx>>tempy;
            g1->insertar_nodo(tempx,tempy,linea);
          }
          else{break;}
        }
      }
    ~Read(){

    }
};
typedef Read<Trts> rd;

#endif
