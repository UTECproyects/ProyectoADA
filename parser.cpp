#include <iostream>
#include <string.h>
#include <vector>
#include <fstream>
#include "json.hpp"
using json = nlohmann::json;

using namespace std;
struct Way
{
  string id;
  double length;
  vector<string> nodes;
};
struct Node
{
  string id;
  double lon, lat;
};
vector<Way> ways;
vector<Node> nodos;
void readnodes(json j)
{
  json a = j;
  int sizenodes;
  string nodeid, nodelon, nodelat;
  double lon, lat;
  a = a.at("node");
  sizenodes = a.size();
  for(int i=0;i<sizenodes;i++)
  {
    a=j.at("node")[i];
    auto *temp = new Node;
    nodeid=a.at("@id");
    nodeid.erase(remove(nodeid.begin(), nodeid.end(), '"'), nodeid.end());
    nodelon=a.at("@lon");
    nodelat=a.at("@lat");
    nodelon.erase(remove(nodelon.begin(), nodelon.end(), '"'), nodelon.end());
    nodelat.erase(remove(nodelat.begin(), nodelat.end(), '"'), nodelat.end());
    lon = stof(nodelon);
    lat = stof(nodelat);
    temp->id=nodeid;
    temp->lon=lon;
    temp->lat=lat;
    nodos.push_back(*temp);
    delete temp;
  }
}
void readways(json j)
{
  int sizeways, sizerefs, sizetags;
  double peso;
  json a = j.at("way");
  json b,c,d,Jlen,filtro,e,f,g;
  bool highway = 0;
  string id,nodo,pesostring;
  sizeways = a.size();
  for(int i=0; i<sizeways;i++)
  {
    auto *temp = new Way;
    a = j.at("way")[i];
    if(a.size()>7)
    {
      filtro = a.at("tag");
      sizetags = filtro.size();
      for(int k=0;k<sizetags;k++)
      {
        Jlen=a.at("tag")[k];
        e = Jlen.at("@k");
        g = Jlen.at("@v");
        if(e == "highway" && g != "residential")
        {
          highway = 1;
        }
      }
    }

    if(highway)
  {
    f = a.at("d");
    pesostring = f.at("@length");
    pesostring.erase(remove(pesostring.begin(), pesostring.end(), '"'), pesostring.end());
    peso = stof(pesostring);
    temp->length=peso;
    b = a.at("nd");
    sizerefs = b.size();
    c = a.at("@id");
    id = c;
    id.erase(remove(id.begin(), id.end(), '"'), id.end());
    temp->id=id;
    for(int x=0; x<sizerefs; x++)
    {
    b = a.at("nd")[x];
    d = b.at("@ref");
    nodo = d;
    nodo.erase(remove(nodo.begin(), nodo.end(), '"'), nodo.end());
    temp->nodes.push_back(nodo);
    }
    ways.push_back(*temp);
    delete temp;
  }
  highway = 0;
  };
}
int main()
{
  ifstream ifs("file.json");
  ofstream data("data.txt");
  json j = json::parse(ifs);
  j = j.at("osm");
  readnodes(j);
  readways(j);
  for(int i=0; i<nodos.size(); i++)
  {
    cout<<"Nodo "<<i<<" id: "<<nodos[i].id<<endl;
    cout<<"Longitud: "<<nodos[i].lon<<endl;
    cout<<"Latitud: "<<nodos[i].lat<<endl;
    if(data.is_open())
    {
      data<<"Nodo "<<i<<" id: "<<nodos[i].id<<endl;
      data<<"Longitud: "<<nodos[i].lon<<endl;
      data<<"Latitud: "<<nodos[i].lat<<endl;
    }
  }
  for(int i=0; i<ways.size(); i++)
  {
    cout<<"Way ID: "<<ways[i].id<<" Peso: "<<ways[i].length<<endl;
    data<<"Way ID: "<<ways[i].id<<" Peso: "<<ways[i].length<<endl;
    for(int j=0; j<ways[i].nodes.size();j++)
    {
      cout<<"Nodo "<<j<<": "<<ways[i].nodes[j]<<endl;
      data<<"Nodo "<<j<<": "<<ways[i].nodes[j]<<endl;
    }
  }
  data.close();
}
