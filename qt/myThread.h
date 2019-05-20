#ifndef LAVAINA
#define LAVAINA
#include "../Grafo/read.h"
#include "../Grafo/graph.h"
#include"../Grafo/node.h"
#endif


#ifndef MYTHREAD_H
#define MYTHREAD_H
#include<QThread>

#include <QAtomicInteger>
#include <QMutex>
class myThread :  public QThread
{
public :
    myThread();
    myThread(graph grafo, double *min, std::list<Node<Graph<Traits>>*,std::allocator<Node<Graph<Traits>>*>> *lista,QAtomicInt *agregador, int numNodosi , QMutex *mutex);
    void run();


private:

    int numNodos;
    std::list<Node<Graph<Traits>>*,std::allocator<Node<Graph<Traits>>*>> * myList;
    graph myGraph;
    QAtomicInt  *myAccum;
    double  *myMin;
    QMutex * mutexLock;



};



#endif // MYTHREAD_H
