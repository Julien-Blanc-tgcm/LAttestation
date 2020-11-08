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
            title: qsTr("Attestations en cours");
            id: header
        }
        model: attestationmanager.attestations
        delegate : ListItem {
            function remove() {
                remorseAction("Suppression", function() { attestationmanager.deleteAttestation(modelData);});
            }

            Label {
                text: modelData
                anchors.verticalCenter: parent.verticalCenter
                anchors.leftMargin: Theme.horizontalPageMargin
                anchors.left: parent.left
            }
            menu: ContextMenu {
                MenuItem {
                    text: qsTr("Effacer")
                    onClicked: remove()
                }
            }
            onClicked: attestationmanager.openAttestation(modelData);
        }
    }
}
