#include "grafoaqt.h"
#include <QObject>
#include

class coordsQt : public QObject
{
    Q_OBJECT
public:
    coordsQt() {}
    virtual ~coordsQt() {}
public slots:
    int masNodos(int n);

signals:
    void sendCoords(std::string latitud , std::string longitude);

};
int coordsQt::masNodos(int n){


}
