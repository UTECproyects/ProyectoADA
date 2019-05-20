#include "circulo.h"
void circulo::setCenter(QGeoCoordinate a ){
    centro = a;
    gen = true;
    emit cambioCent(centro);
}
