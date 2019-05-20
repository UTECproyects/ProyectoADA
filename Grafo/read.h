#ifndef READ_H
#define READ_H
#include <QUrl>
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <string>
#include "graph.h"

using namespace std;

inline double DegreeToRadian(double angle)
{
  return M_PI * angle / 180.0;
}

template <typename Tr>
class Read
{
  typedef Graph<Tr> self;
  typedef Node<self> node;
  typedef typename Tr::N N;
  typedef typename Tr::E E;
  string file;

public:
  map<E, pair<double, double>> idcoords;
  double HaversineDistance(E tempini, E tempfin)
  {
    double latRad1 = DegreeToRadian(idcoords[tempini].second);
    double latRad2 = DegreeToRadian(idcoords[tempfin].second);
    double lonRad1 = DegreeToRadian(idcoords[tempini].first);
    double lonRad2 = DegreeToRadian(idcoords[tempfin].first);

    double diffLa = latRad2 - latRad1;
    double doffLo = lonRad2 - lonRad1;

    double computation = asin(sqrt(sin(diffLa / 2) * sin(diffLa / 2) + cos(latRad1) * cos(latRad2) * sin(doffLo / 2) * sin(doffLo / 2)));
    return 2 * 6372.8 * computation * 1000;
  }
  void getGraph(graph *g1)
  {
    ifstream archivo;
    string line;
    int x;
    E linea, tempini, tempfin;
    int i = 0;
    bool oneway;
    pair<double, double> findcoords;
    double tempx, tempy;
    archivo.open("/home/fernando/Desktop/ADA_masterbranch/ProyectoADA/Data/datagrande.txt");

    while (!archivo.eof())
    {
      archivo >> line;

      if (line != "@")
      {
#ifdef _WIN32
        linea = stoll(line);
#else
        linea = stol(line);
#endif
        archivo >> tempx >> tempy;
        pair<double, double> coords;
        coords.first = tempx;
        coords.second = tempy;
        idcoords.insert(pair<E, pair<double, double>>(linea, coords));
      }
      else
      {
        break;
      }
    };

    getline(archivo, line);
    while (!archivo.eof())
    {
      getline(archivo, line);
      if (line != "@")
      {
        archivo >> oneway >> tempini >> tempfin;
        g1->insertar_nodo(tempini, idcoords[tempini].first, idcoords[tempini].second);
        g1->insertar_nodo(tempfin, idcoords[tempfin].first, idcoords[tempfin].second);
        if (oneway == 1)
        {
          g1->insertar_arista(tempini, tempfin, line, HaversineDistance(tempini, tempfin));
        }
        else
        {
          g1->insertar_arista(tempini, tempfin, line, HaversineDistance(tempini, tempfin));
          g1->insertar_arista(tempfin, tempini, line, HaversineDistance(tempini, tempfin));
        }

        getline(archivo, line);
      }
      else
      {
        break;
      }
    }
  }
};
typedef Read<Traits> rd;

#endif
