#include "myThread.h"
//#include<QtCore>
//#include <QDebug>
//#include "../Grafo/read.h"
//#include "../Grafo/graph.h"
//#include"../Grafo/node.h"
//#include <QAtomicInteger>
//#include <QMutex>
myThread::myThread(graph *grafo, double *min,std::list<Node<Graph<Traits>>*,std::allocator<Node<Graph<Traits>>*>> *lista ,QAtomicInt *agregador, int numNodosi, QMutex *mutex){

    myGraph = new graph;
   myGraph = grafo;
    myMin = new double;
    myMin = min;
    myList = new std::list<Node<Graph<Traits>>*,std::allocator<Node<Graph<Traits>>*>>;
    myList = lista;
    myAccum = new QAtomicInt;
    myAccum = agregador;
    mutexLock = new QMutex;
    mutexLock = mutex;
    numNodos = numNodosi;
}
myThread::myThread(){
    ;
}
void myThread::run(){
    while( myAccum->fetchAndOrAcquire(1)<numNodos){

        auto ResultadosEstrella = myGraph->A_Star(myGraph->buscar_taxista(0)->nodo->get(),myGraph->buscar_taxista(*myAccum)->nodo->get());
        if(ResultadosEstrella.first<*myMin){
            mutexLock->lock();
            *myMin=ResultadosEstrella.first;
            *myList=ResultadosEstrella.second;
            mutexLock->unlock();
        }
    }

}
