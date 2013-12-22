/* Author: Ben Lau (https://github.com/benlau) */
import QtQuick 2.0
import "android.js" as Android

Rectangle {
    width: 400
    height: 400

    Text {
        text: "Forumla: 1 dp = " + Android.dp + " pixel."
        anchors.centerIn: parent
        font.pixelSize : 18 * Android.dp
    }

    MouseArea {
        id: mouseArea1
        anchors.bottomMargin: 0
        anchors.top: actionBar.bottom
        anchors.right: parent.right
        anchors.bottom: navBar.top
        anchors.left: parent.left
        anchors.topMargin: 0
        onClicked: {
            Qt.quit();
        }
    }

    Rectangle {
        id: actionBar
        height: 48 * Android.dp
        color: "#3498db"
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0

        Text {
            id: text1
            x: 144
            y: 17
            color: "#ffffff"
            text: "Action Bar - 48DP"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pixelSize : 22 * Android.dp;
        }
    }

    Rectangle {
        id: navBar
        x: 0
        y: 360
        height: 48 * Android.dp
        color: "#3498db"
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
    }
}
