import QtQuick 2.0
import Sailfish.Silica 1.0

Rectangle {
    property string label: ""
    property string destination: ""
    property var destinationArgs: null

    height: Theme.itemSizeMedium
    anchors.left: parent.left
    anchors.right: parent.right
    color: "transparent"
    Label {
        text: label // Générer une attestation
        anchors.leftMargin: Theme.horizontalPageMargin
        anchors.rightMargin: Theme.horizontalPageMargin
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
    }
    MouseArea {
        anchors.fill: parent
        onClicked: pageStack.push(destination, destinationArgs)
        onPressedChanged: {
            if(pressed) {
                parent.color = Theme.rgba(Theme.highlightBackgroundColor, Theme.highlightBackgroundOpacity)
            }
            else
                parent.color = "transparent"
        }
        //onDragChanged: parent.color = "transparent"
        onReleased: parent.color = "transparent"
    }
}
