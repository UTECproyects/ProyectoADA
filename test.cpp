#include <iostream>
#include <fstream>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

int main()
{
  json a;
  ifstream ifs("file.json");
  json j = json::parse(ifs);
  cout<<j.at("name")<<endl;
}
