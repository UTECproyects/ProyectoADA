#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QGeoRoute>
#include <QGeoCoordinate>
#include <QQmlComponent>
#include "Grafo/read.h"
#include "Grafo/graph.h"
#define nNodos 5

int main(int argc, char *argv[])
{
    
    vector <string> loquemevanadarlasfunciones;
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    QQmlComponent component(&engine,QUrl::fromLocalFile("qrc:/misListas.qml"));
    vector<QObject*> misListas;
    //TODO
    //acuerdate, a qt le vas a pasar SOLO COORDENADAS, i =2n, n siendo el numero del nodo

    for (int i =0;i < nNodos; i++) {
        misListas.push_back(component.create());
        //placeholders, esto es lima
        misListas[i]->setProperty("centerLong","-12.1348806");
        misListas[i]->setProperty("centerLat","-77.02212709999999");

        for (int j =0;j <= loquemevanadarlasfunciones.size(); j++) {
            vector<string> toSetCoords;
            toSetCoords.push_back(loquemevanadarlasfunciones[j]);

            if (j == loquemevanadarlasfunciones.size()){
                QVariant buffer;
                buffer.setValue(toSetCoords);
                misListas[i]->setProperty("vectorCoords",buffer);
            }
        }

    }
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
