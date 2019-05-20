#ifndef CIRCULO_H
#define CIRCULO_H
#include<QObject>
#include <QGeoCoordinate>

class circulo : public QObject{
    Q_OBJECT
public:
    circulo(){gen =  false;}
    circulo(QGeoCoordinate a){
        centro = a;
        gen = true;
    }
public slots:
    void setCenter(QGeoCoordinate a);

signals:
    void cambioCent(QGeoCoordinate a);
private:
    QGeoCoordinate centro;
    bool gen;
};






#endif
