import QtQuick 2.11
import QtQuick.Window 2.11
import QtPositioning 5.11
import QtLocation 5.11


Window {
    visible: true
    width: 1280
    height: 720
    title: qsTr("ADA-Proyect")
    Plugin{
        id:map
        name: "osm"
    }

    Map{
        objectName: "myMap"
        plugin:map
         anchors.fill: parent
         zoomLevel: 13
         id:myMap
         center : QtPositioning.coordinate( -12.1348806 , -77.02212709999999);




         MapPolyline{
             id:pl
         objectName: "myLine"
         line.width: 4
         line.color: "green"
     }

     Component.onCompleted: {
                 var lines = []
                 for(var i=0; i < geopath.size(); i++){
                     lines[i] = geopath.coordinateAt(i)
                 }
                 pl.path = lines
             }

//         { latitude: -27, longitude: 153.0 },
//         { latitude: -27, longitude: 154.1 },


       
    }
    
    }

