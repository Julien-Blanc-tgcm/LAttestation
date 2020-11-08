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
            height: Theme.itemSizeSmall
            Label {
                text: modelData
            }
            menu: ContextMenu {
                MenuItem {
                    text: qsTr("Effacer")
                    onClicked: attestationmanager.deleteAttestation(modelData)
                }
            }
            onClicked: attestationmanager.openAttestation(modelData);
        }
    }
}
