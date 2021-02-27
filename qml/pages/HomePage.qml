import QtQuick 2.0
import Sailfish.Silica 1.0
import "../components"

Page {
    id: page

    // The effective value will be restricted by ApplicationWindow.allowedOrientations
    allowedOrientations: Orientation.All

    // To enable PullDownMenu, place our content in a SilicaFlickable
    SilicaFlickable
    {
        PullDownMenu{
            MenuItem {
                text: qsTr("Parameters") // "Paramètres"
                onClicked: pageStack.push(Qt.resolvedUrl("SettingsPage.qml"))
            }
        }
        anchors.fill: parent
        contentHeight: column.height
        Column
        {
            id: column
            width:parent.width
            PageHeader {
                title: qsTr("Certificate of discharge") // "Attestation de sortie"
            }
            SectionHeader {
                text: qsTr("Certificate « Couvre-feu »")
            }

            MainPageItem {
                label: qsTr("Multiple choice certificate")
                destination: Qt.resolvedUrl("Generate.qml")
                destinationArgs: {"certificateType": 0, "multipleMotives": true}
            }

            MainPageItem {
                label: qsTr("Single choice certificate")
                destination: Qt.resolvedUrl("Generate.qml")
                destinationArgs: {"certificateType": 0, "multipleMotives": false, "local": true, "national": true}
            }

            MainPageItem {
                label: qsTr("National certificate")
                destination: Qt.resolvedUrl("Generate.qml")
                destinationArgs: {"certificateType": 0, "multipleMotives": false, "local": false, "national": true}
            }

            MainPageItem {
                label: qsTr("Local certificate")
                destination: Qt.resolvedUrl("Generate.qml")
                destinationArgs: {"certificateType": 0, "multipleMotives": false, "local": true, "national": false}
            }

            SectionHeader {
                text: qsTr("Quick access")
                visible: appSettings.ooopsEnabled
            }
            MainPageItem {
                label: qsTr("Ooops - Animals")
                destination: Qt.resolvedUrl("QuickGenerate.qml")
                destinationArgs: { "motive":2}
                visible: appSettings.ooopsEnabled
            }
            MainPageItem {
                label: qsTr("Ooops - Shopping")
                destination: Qt.resolvedUrl("QuickGenerate.qml")
                destinationArgs: { "motive":1}
                visible: appSettings.ooopsEnabled
            }
            SectionHeader {
                text: qsTr("Previous certificates")
            }
            MainPageItem {
                label: qsTr("Previously generated certificates")
                destination: Qt.resolvedUrl("Access.qml")
            }

        }


    }
    Timer {
        id: timer
        interval: 1000
        repeat: false
        onTriggered: pageStack.push(Qt.resolvedUrl("SettingsPage.qml"))
    }

    Component.onCompleted: {
        if(appSettings.firstName.length === 0)
            timer.start();
    }
}
