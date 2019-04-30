#include <iostream>
#include <string.h>
#include <vector>
#include <fstream>
#include "json.hpp"
using json = nlohmann::json;

using namespace std;

struct Way
{
  int id;
  string name;
  vector<int> nodes;
};
struct Nodes
{
  int id;
};
int main()
{
  ifstream ifs("file.json");
  json j = json::parse(ifs);
  vector<Way> ways;
  auto *temp = new Way;
  temp->id = 1;
  temp->name = "Ian";
  temp->nodes.push_back(1);
  temp->nodes.push_back(4);
  temp->nodes.push_back(3);
  ways.push_back(*temp);
  delete temp;
  for(int i=0; i<ways.size(); i++)
  {
    cout<<"id: "<<ways[i].id<<endl;
    cout<<"name: "<<ways[i].name<<endl;
    for(int x=0; x<ways[i].nodes.size();x++)
    {
        cout<<"node: "<<ways[i].nodes[x]<<endl;
    }
  }
  cout<<j.at("pi");
}
