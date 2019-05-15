#include<iostream>
#include<fstream>
#include<string>

using namespace std;
struct Node
{
  long id;
  double x,y;
};
struct Way
{

};
int main()
{
  ifstream archivo;
  string line;
  long linea;
  int i = 0;
  double tempx, tempy;
  archivo.open("Data/data.txt");
    while(!archivo.eof())
    {
      archivo>>line;
      if(line!="@")
      {
        linea = stol(line);
        cout<<linea<<endl;
        archivo>>tempx>>tempy;
        //g1->insertar_nodo(tempx,tempy,linea);
      }
      else{break;}
    }
  }
