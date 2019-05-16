import QtQuick 2.11
import QtQuick.Window 2.11
import QtPositioning 5.11
import QtLocation 5.11


Item {
    //sus coordenadas
    property variant centerLong;
    property variant centerLat;
    //Los otros nodos si es el parent/la ruta al parent si es el child
    property list<variant> vectorCoords;
//    property variant vectorCoords;
//    function makeCoords(vectorCoords){
//        i = 0;
//        myCoords =[];
//        for (x in vectorCoords){




//        i++;
//        }





    }

    parent: myMap

}

