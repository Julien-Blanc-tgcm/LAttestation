import QtQuick 2.6
import Sailfish.Silica 1.0
import harbour.eu.tgcm.lattestation 1.0

Page {
    AttestationManager {
        id: attestationmanager
    }

    SilicaListView {
        anchors.fill: parent
        header: PageHeader {
            title: qsTr("Generated certificates"); // Attestations générées
            id: header
        }
        model: attestationmanager.attestations
        delegate : ListItem {
            id: theItem
            property var att : attestationmanager
            function remove() {
                remorseItem.execute(theItem, qsTr("Deleting"), function() { att.deleteAttestation(modelData);});
            }
            RemorseItem {
                id: remorseItem
            }

            Label {
                text: modelData
                anchors.verticalCenter: parent.verticalCenter
                anchors.leftMargin: Theme.horizontalPageMargin
                anchors.left: parent.left
            }
            menu: ContextMenu {
                MenuItem {
                    text: qsTr("Delete") // Effacer
                    onClicked: remove()
                }
            }
            onClicked: attestationmanager.openAttestation(modelData);
        }
    }
}
