#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QGeoRoute>
#include <QGeoPath>
#include <QQuickView>
#include <QGeoCoordinate>
#include <QQmlComponent>
#include <QQmlContext>
#include "../Grafo/read.h"
#include "../Grafo/graph.h"
#include"../Grafo/node.h"
#include <set>
#include <QGeoCoordinate>
#define nNodos 5
#define distMax 100000


int main(int argc, char *argv[])
{
    graph g1;
    rd gg;
    gg.getGraph(&g1);
    auto nodos = g1.getNodes();
    auto numNodos = g1.total_nodos();
    srand (time(nullptr));

    vector <string> loquemevanadarlasfunciones;
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    QGeoPath geopath;
    geopath.addCoordinate(QGeoCoordinate(-12.1348806, -77.02212709999999));
    geopath.addCoordinate(QGeoCoordinate(56.1, 93));
    geopath.addCoordinate(QGeoCoordinate(56.1, 92.777));
    engine.load(QUrl(QStringLiteral("/home/fernando/Desktop/ADA_masterbranch/ProyectoADA/qt/main.qml")));
    QQmlComponent component(&engine,QUrl::fromLocalFile("/home/fernando/Desktop/ADA_masterbranch/ProyectoADA/qt/main.qml"));
    engine.rootContext()->setContextProperty("geopath", QVariant::fromValue(geopath));
    vector<QObject*> misListas;
//    QObject *object = component.create();
//    QObject *mapa = object->findChild<QObject*>("myMap");
//    QObject *linea = mapa->findChild<QObject*>("myLine");
//    QObject *line = linea->findChild<QObject*>();
//    line[0].setProperty("color", "red");

    //linea->addCoordinate(wea)
    //TODO
    //acuerdate, a qt le vas a pasar SOLO COORDENADAS, i =2n, n siendo el numero del nodo
    //so that was a lie


    auto idNodoi = nodos.begin();
    std::set<int> ids;
    vector<unsigned long> idsParafind;

    //encuentra n nodos diferentes
    for (int x = 0;x <= nNodos; x++) {
        int currRand = rand()%numNodos ;
        while(!(ids.insert(currRand)).second)currRand= rand() %numNodos;
        //Tenemos los i's de los nodos a ser usados
    }

    int  nodoEstamos = 0;

    for (int i =0;i < numNodos; i++) {
        if (i == (*ids.find(i)) ) {

            //placeholders, esto es lima
            auto x =idNodoi->second->get_x();
            auto y =idNodoi->second->get_y();
            idsParafind.push_back(idNodoi->first);
//            misListas[i]->setProperty("centerLong",x);
//            misListas[i]->setProperty("centerLat",y);
            auto ResultadosEstrella = g1.A_Star(4354621323,4394276694);
            auto idNodoj = ResultadosEstrella.begin();
            QList<QVariant> buffer;
            for (list<Node<Graph<Traits>>*>::iterator  j = ResultadosEstrella.begin(); j != ResultadosEstrella.end(); j++) {
                vector<double> toSetCoords;
                cout<<(*j)->get_x()<<endl;
                cout<<(*j)->get_y()<<endl<<endl;
              //  double lat =(*idNodoj)->get_x();
              //  double longit = (*idNodoj)->get_y();
                 //   buffer.append(QVariant::fromValue(QGeoCoordinate(lat,longit)));
                //if (j == ResultadosEstrella.size()){
                 //     misListas.push_back(component.create());
                  //  misListas[i]->setProperty("path",buffer);
                }
                idNodoj++;
            }

            nodoEstamos++;
        }idNodoi++;
    //}
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
