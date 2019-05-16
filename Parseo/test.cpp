#include <iostream>
#include <string.h>
#include <vector>
#include <fstream>
#include "json.hpp"
using json = nlohmann::json;

using namespace std;

int main()
{
  string name;
  ifstream ifs("../Data/mapagrande.json");
  ofstream data("../Data/datagrande.txt",ostream::trunc);
  json j = json::parse(ifs);
}

