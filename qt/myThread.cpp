#include "myThread.h"
//#include<QtCore>
//#include <QDebug>
//#include "../Grafo/read.h"
//#include "../Grafo/graph.h"
//#include"../Grafo/node.h"
//#include <QAtomicInteger>
//#include <QMutex>
myThread::myThread(graph grafo, double *min,std::list<Node<Graph<Traits>>*,std::allocator<Node<Graph<Traits>>*>> *lista ,QAtomicInt *agregador, int numNodosi, QMutex *mutex){


   myGraph = grafo;

    myMin  = min;

    myList = lista;

    myAccum = agregador;

    mutexLock = mutex;
    numNodos = numNodosi;
}
myThread::myThread(){
    ;
}
void myThread::run(){
    int uno =1;
    long buffer = *myAccum;
    do{
       buffer = *myAccum;
       mutexLock->unlock();
        auto nodo1 = myGraph.buscar_taxista(0)->nodo->get();
        auto nodo2 = myGraph.buscar_taxista(buffer)->nodo->get();
        auto ResultadosEstrella = myGraph.A_Star(nodo1,nodo2);
        if(ResultadosEstrella.first< *myMin){

            mutexLock->lock();
            *myMin=ResultadosEstrella.first;
            *myList=ResultadosEstrella.second;
            mutexLock->unlock();
        }
        mutexLock->lock();
    }while( myAccum->fetchAndAddRelaxed(uno)< numNodos-1);
     mutexLock->unlock();
}
