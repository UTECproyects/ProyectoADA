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
  string nombre;
};
struct Node
{
  string id;
  double lon, lat;
};
struct edge
{
  string inicio, final;
};
vector<Way> ways;
vector<Node> nodos;
vector<edge> aristas;
int aux = 1;
void createEdges()
{
  for(int i = 0; i<ways.size(); i++)
  {
    for(int j = 0; j<ways[i].nodes.size();j++)
    {
      if(aux!=ways[i].nodes.size())
      {
        auto *temp = new edge;
        cout<<"Size: "<<ways[i].nodes.size()<<endl;
        cout<<"Node Inicial: "<<ways[i].nodes[j]<<endl;
        cout<<"Node Final: "<<ways[i].nodes[aux]<<endl;
        temp->inicio = ways[i].nodes[j];
        temp->final=ways[i].nodes[aux];
        aux++;
        aristas.push_back(*temp);
        delete temp;
      }
    }
    aux=1;
  }
}
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
    string nombre;
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
        if(e == "highway" && (g != "footway") && a.size()>8)
        {
          highway = 1;
        }
        if(e == "name")
        {
            nombre = g;
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
    temp->nombre=nombre;
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
  string name;
  ifstream ifs("Data/file.json");
  //ofstream data("Data/data.txt",ostream::trunc);
  json j = json::parse(ifs);
  j = j.at("osm");
  //readnodes(j);
  readways(j);
  /*for(int i=0; i<nodos.size(); i++)
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
  cout<<"@"<<endl;
  data<<"@"<<endl;
  for(int i=0; i<ways.size(); i++)
  {
    if(ways[i].nombre != "")
    {
      name = ways[i].nombre;
    }
    else{name = "No Name";}
    cout<<"Way ID: "<<ways[i].id<<endl<<"Nombre: "<<name<<endl<<"Peso: "<<ways[i].length<<endl;
    data<<"Way ID: "<<ways[i].id<<endl<<"Nombre: "<<name<<endl<<"Peso: "<<ways[i].length<<endl;
    for(int j=0; j<ways[i].nodes.size();j++)
    {
      cout<<"Nodo "<<j<<": "<<ways[i].nodes[j]<<endl;
      data<<"Nodo "<<j<<": "<<ways[i].nodes[j]<<endl;
    }
    data<<"@"<<endl;
  }
  data.close();*/
  createEdges();
}
