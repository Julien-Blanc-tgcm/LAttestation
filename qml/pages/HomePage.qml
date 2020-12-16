import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: page

    // The effective value will be restricted by ApplicationWindow.allowedOrientations
    allowedOrientations: Orientation.All

    // To enable PullDownMenu, place our content in a SilicaFlickable
    SilicaListView
    {
        anchors.fill: parent
        id: list
        header: PageHeader {
            title: qsTr("Certificate of discharge") // "Attestation de sortie"
        }

        PullDownMenu{
            MenuItem {
                text: qsTr("Parameters") // "Paramètres"
                onClicked: pageStack.push(Qt.resolvedUrl("SettingsPage.qml"))
            }
        }

        model: ListModel {
            ListElement {
                text: qsTr("Generate a certificate") // Générer une attestation
                page: "Generate.qml"
                ooops: false
            }
            ListElement {
                text: qsTr("Previous certificates") // Précédentes attestations
                page: "Access.qml"
                ooops: false
            }
            ListElement {
                text: qsTr("Ooops - Animals") // Oups - Sport & Loisirs
                page: "QuickLoisirs.qml"
                ooops: true
            }
        }
        delegate : ListItem {
            height: Theme.itemSizeMedium
            Label {
                id: lbl
                text: model.text
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.leftMargin: Theme.horizontalPageMargin
                anchors.rightMargin: Theme.horizontalPageMargin
                anchors.verticalCenter: parent.verticalCenter
            }
            onClicked: pageStack.push(Qt.resolvedUrl(model.page))
            visible: !model.ooops || appSettings.ooopsEnabled
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
