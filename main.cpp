#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QGeoRoute>
#include <QGeoCoordinate>
#include <QQmlComponent>
#include "Grafo/read.h"
#include "Grafo/graph.h"
#include"Grafo/node.h"
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
    unsigned long numNodos = g1.total_nodos();
    srand (time(nullptr));

    vector <string> loquemevanadarlasfunciones;
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    QQmlComponent component(&engine,QUrl::fromLocalFile("qrc:/misListas.qml"));
    vector<QObject*> misListas;
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
            misListas.push_back(component.create());
            //placeholders, esto es lima
            auto x =idNodoi->second->get_x();
            auto y =idNodoi->second->get_y();
            idsParafind.push_back(idNodoi->first);
            misListas[i]->setProperty("centerLong",x);
            misListas[i]->setProperty("centerLat",y);
            auto ResultadosEstrella = g1.A_Star(idNodoi->first,*idsParafind.begin());

            auto idNodoj = ResultadosEstrella.begin();
            for (unsigned long j =0;j <= ResultadosEstrella.size(); j++) {
                vector<double> toSetCoords;
                QList<QVariant> buffer;
                double lat =(*idNodoj)->get_x();
                double longit = (*idNodoj)->get_y();
                    buffer.append(QVariant::fromValue(QGeoCoordinate(lat,longit)));
                if (j == ResultadosEstrella.size()){

                    misListas[i]->setProperty("vectorCoords",buffer);
                }
                idNodoj++;
            }

            nodoEstamos++;
        }idNodoi++;
    }
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
