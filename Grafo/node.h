#ifndef NODE_H
#define NODE_H
#include<string>

template <typename G>
class Node {
    public:
        typedef typename G::N N;
        typedef typename G::E E;
        typedef typename G::edge edge;
        typedef typename G::EdgeSeq EdgeSeq;
        Node(E dat,double _x,double _y):id(dat),x(_x),y(_y){};
        E get(){return id;}
        double get_x(){return x;}
        double get_y(){return y;}
        ~Node(){};

        EdgeSeq edges;
        bool tool=0;

    private:
        E id;
        double x;
        double y;
};

#endif
