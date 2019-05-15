#ifndef EDGE_H
#define EDGE_H
#include "node.h"
using namespace std;

template <typename G>
class Edge {
    public:
        typedef typename G::E E;
        typedef typename G::N N;
        typedef typename G::node node;
        node* nodes[2];
        Edge(double data_,string nombre_,node* node1,node* node2):data(data_),nombre(nombre_){
            nodes[0]=node1;
            nodes[1]=node2;
        }
        double get(){return data;}
        string get_nombre(){return nombre;}
        /*
        node* goes_to(N v1){
            if (nodes[0]->get()==v1){
                return nodes[1];
            }else{
                return nodes[0];
            }
        }
        */
        ~Edge(){}
    private:
        double data;
        string nombre;
};

#endif
