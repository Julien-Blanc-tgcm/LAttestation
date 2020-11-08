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
            title: qsTr("Attestation de sortie")
        }

        PullDownMenu{
            MenuItem {
                text: qsTr("Paramètres")
                onClicked: pageStack.push(Qt.resolvedUrl("SettingsPage.qml"))
            }
        }

        model: ListModel {
            ListElement {
                text: qsTr("Générer une attestation")
                page: "Generate.qml"
            }
            ListElement {
                text: qsTr("Accéder à une attestation")
                page: "Access.qml"
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
        }
    }
}
