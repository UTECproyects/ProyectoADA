#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QGeoRoute>
#include <QGeoPath>
#include <QQuickView>
#include <QQmlComponent>
#include <QQmlContext>
#include <QThread>
#include "myThread.h"
#include <set>
#include <QGeoCoordinate>
#include <QAtomicInteger>
#include <QMutex>
#define nNodos 100
#define nodoini 4362423164
#define distMax 100000
#ifndef LAVAINA
#define LAVAINA
#include "../Grafo/read.h"
#include "../Grafo/graph.h"
#include"../Grafo/node.h"
#endif








//chorrillos 4362423164  miraflores 263615940 lima 791159777
int main(int argc, char *argv[])
{
    int numThreads = QThread::idealThreadCount();
    graph g1;
    rd gg;
    gg.getGraph(&g1);
    g1.iniciar_taxis(nNodos);


    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    QGeoPath geopath;


    auto ResultadosEstrella = g1.A_Star(nodoini,g1.buscar_taxista(0)->nodo->get());
   // auto ResultadosEstrella = g1.A_Star(nodoini,1432901632);
    auto lista=ResultadosEstrella.second;
    //empiezo los threads
    QAtomicInt agregador=1;
    int numeroNodos = nNodos;
    QMutex mutex;
    vector<myThread *> misthreads;
    double menor =  2147483647;
    for (int i = 0; i < numThreads; ++i) {
        myThread * ptrThread =new myThread (g1, &menor,&lista,&agregador,numeroNodos,&mutex);
        misthreads.push_back(ptrThread);
        misthreads[i]->start();
    }
    for (int i = 0; i < numThreads; ++i){
        misthreads[i]->wait();
    }
//    for(int j=1;j<nNodos;j++){

//        ResultadosEstrella = g1.A_Star(nodoini,g1.buscar_taxista(j)->nodo->get());
//        if(ResultadosEstrella.first<menor){
//            menor=ResultadosEstrella.first;
//            lista=ResultadosEstrella.second;
//        }
//    }

    for (list<Node<Graph<Traits>>*>::iterator  j = lista.begin(); j != lista.end(); ++j) {
        geopath.addCoordinate(QGeoCoordinate((*j)->get_y(), (*j)->get_x()));
    }

    engine.rootContext()->setContextProperty("geopath", QVariant::fromValue(geopath));
    engine.load(QUrl(QStringLiteral("/home/fernando/Desktop/ADA_masterbranch/ProyectoADA/qt/main.qml")));
    QQmlComponent component(&engine,QUrl::fromLocalFile("/home/fernando/Desktop/ADA_masterbranch/ProyectoADA/qt/main.qml"));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
