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
  int length;
  vector<string> nodes;
};
struct Node
{
  string id;
};
vector<Way> ways;
vector<Node> nodos;
void readnodes(json j)
{
  json a = j;
  int sizenodes;
  string nodeid;
  a = a.at("node");
  sizenodes = a.size();
  for(int i=0;i<sizenodes;i++)
  {
    a=j.at("node")[i];
    auto *temp = new Node;
    nodeid=a.at("_id");
    nodeid.erase(remove(nodeid.begin(), nodeid.end(), '"'), nodeid.end());
    temp->id=nodeid;
    nodos.push_back(*temp);
    delete temp;
  }
}
void readways(json j)
{
  int sizeways, sizerefs, sizetags;
  json a = j.at("way");
  json b,c,d,Jlen,filtro,e;
  bool highway = 0;
  string id,nodo;
  sizeways = a.size();
  for(int i=0; i<sizeways;i++)
  {
    auto *temp = new Way;
    a = j.at("way")[i];
    filtro = a.at("tag");
    sizetags = filtro.size();
    for(int k=0;k<sizetags;k++)
    {
      Jlen=a.at("tag")[k];
      e = Jlen.at("_k");
      if(e == "highway")
      {
        highway = 1;
      }
    }
    if(highway)
  {
    b = a.at("nd");
    sizerefs = b.size();
    c = a.at("_id");
    id = c;
    id.erase(remove(id.begin(), id.end(), '"'), id.end());
    temp->id=id;
    for(int x=0; x<sizerefs; x++)
    {
    b = a.at("nd")[x];
    d = b.at("_ref");
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
    if(data.is_open())
    {
      data<<"Nodo "<<i<<" id: "<<nodos[i].id<<endl;
    }
  }
  for(int i=0; i<ways.size(); i++)
  {
    cout<<"Way ID: "<<ways[i].id<<endl;
    data<<"Way ID: "<<ways[i].id<<endl;
    for(int j=0; j<ways[i].nodes.size();j++)
    {
      cout<<"Nodo "<<j<<": "<<ways[i].nodes[j]<<endl;
      data<<"Nodo "<<j<<": "<<ways[i].nodes[j]<<endl;
    }
  }
  data.close();
}
