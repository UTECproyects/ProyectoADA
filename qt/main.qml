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
         objectName: "myLine"
         line.width: 4
            path: [QtPositioning.coordinate( -12.1348806 , -77.02212709999999),QtPositioning.coordinate( -12 , -77)]
     }



       
    }
    
    }

