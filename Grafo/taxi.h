#ifndef TAXI_H
#define TAXI_H
#include<string>

template <typename G>
class Taxi {
    public:
        typedef typename G::E E;
        typedef typename G::node node;
        Taxi(E dat,node* nodo_,double _x,double _y):id(dat),nodo(nodo_),x(_x),y(_y){};
        E get(){return id;}
        double get_x(){return x;}
        double get_y(){return y;}
        void set_xy(double x_,double y_){x=x_;y=y_;}
        ~Taxi(){};
        node* nodo;
    private:
        E id;
        double x;
        double y;
};

#endif
