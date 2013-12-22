/* Author: Ben Lau (https://github.com/benlau) */
import QtQuick 2.0
import "android.js" as Android

Rectangle {
    id: splash
    width: 360
    height: 360
    color: "#000000"

    onWidthChanged: mainLoader.item.width = splash.width
    onHeightChanged: mainLoader.item.height = splash.height

    function init(context) {
        Android.init(context);
        mainLoader.source = "main.qml"
    }

    Loader { // this component performs deferred loading.
        id: mainLoader
        visible: status == Loader.Ready
        onLoaded: {
            mainLoader.item.width = splash.width
            mainLoader.item.height = splash.height
        }
    }
}
