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
#define nNodos 13
#define nodoini 377048583
#define distMax 100000


int main(int argc, char *argv[])
{
    double menor=9999999;
    graph g1;
    rd gg;
    gg.getGraph(&g1);
    auto nodos = g1.getNodes();
    auto numNodos = g1.total_nodos();
    srand (time(nullptr));
    g1.iniciar_taxis(nNodos);
    vector <string> loquemevanadarlasfunciones;
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    QGeoPath geopath,geosize;
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

    for (int i =0;i < 1; i++) {
        //if (i == (*ids.find(i)) ) {

            //placeholders, esto es lima
            auto x =idNodoi->second->get_x();
            auto y =idNodoi->second->get_y();
            idsParafind.push_back(idNodoi->first);

//            misListas[i]->setProperty("centerLong",x);
//            misListas[i]->setProperty("centerLat",y);
            auto ResultadosEstrella = g1.A_Star(nodoini,g1.buscar_taxista(0)->nodo->get());
            menor=ResultadosEstrella.first;
            auto lista=ResultadosEstrella.second;
            for(int j=1;j<nNodos;j++){
                ResultadosEstrella = g1.A_Star(nodoini,g1.buscar_taxista(j)->nodo->get());
                if(ResultadosEstrella.first<menor){
                    menor=ResultadosEstrella.first;
                    lista=ResultadosEstrella.second;
                }
            }


            QList<QVariant> buffer;

            for (list<Node<Graph<Traits>>*>::iterator  j = lista.begin(); j != lista.end(); ++j) {
                vector<double> toSetCoords;
                set<long> a;
                geopath.addCoordinate(QGeoCoordinate((*j)->get_y(), (*j)->get_x()));

                cout<<(*j)->get()<<endl;
              //  double lat =(*idNodoj)->get_x();
              //  double longit = (*idNodoj)->get_y();
                 //   buffer.append(QVariant::fromValue(QGeoCoordinate(lat,longit)));
                //if (j == ResultadosEstrella.size()){
                 //     misListas.push_back(component.create());
                  //  misListas[i]->setProperty("path",buffer);
                }
                //idNodoj++;
            //}

            //nodoEstamos++;
        //}idNodoi++;

    }
    engine.rootContext()->setContextProperty("geopath", QVariant::fromValue(geopath));
    engine.load(QUrl(QStringLiteral("/home/fernando/Desktop/ADA_masterbranch/ProyectoADA/qt/main.qml")));
    QQmlComponent component(&engine,QUrl::fromLocalFile("/home/fernando/Desktop/ADA_masterbranch/ProyectoADA/qt/main.qml"));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
