import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    SilicaFlickable {
        Timer {
            id: theTimer
            interval: 1000
            repeat: true
            onTriggered: refreshTimes()
        }

        PullDownMenu {
            MenuItem {
                text: qsTr("Agrandir la plage horaire")
                onClicked: {
                    doneTimeShift.maximumValue = doneTimeShift.maximumValue * 2
                    doneTimeShift.minimumValue = doneTimeShift.minimumValue * 2
                }
            }
        }


        anchors.fill: parent
        contentHeight: Math.max(column.height, parent.height)
        Column {
            id: column
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: Theme.horizontalPageMargin
            anchors.rightMargin: Theme.horizontalPageMargin
            spacing: Theme.paddingMedium
            PageHeader {
                title: qsTr("Contenu")
            }

            ComboBox {
                id: motive
                width: parent.width
                label: qsTr("Motif")
                menu: ContextMenu {
                    MenuItem { text: qsTr("Courses") }
                    MenuItem { text: qsTr("Loisir") }
                    MenuItem { text: qsTr("Déplacement pro") }
                    MenuItem { text: qsTr("Consultation médicale") }
                    MenuItem { text: qsTr("Assistance pers. vulnérable") }
                    MenuItem { text: qsTr("Mission intérêt public") }
                    MenuItem { text: qsTr("Accompagnement enfants") }
                    MenuItem { text: qsTr("Convocation") }
                    MenuItem { text: qsTr("Aide handicapé") }
                }
            }
            TextField {
                id: doneAt
                width: parent.width
                label: qsTr("Fait à")
                placeholderText: qsTr("Fait à")
            }
            Slider {
                id: doneTimeShift
                label: qsTr("Heure de sortie")
                width: parent.width
                minimumValue: -120
                maximumValue: 30
                stepSize: 1
                value: 0
                valueText: formatValue(value)
            }
            Button {
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("Générer")
                onClicked: generate()
            }
        }
        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: Theme.paddingLarge
            spacing: Theme.paddingMedium
            Icon {
                color: Theme.highlightColor
                source: "image://theme/icon-m-clock"
                anchors.verticalCenter: parent.verticalCenter
            }
            Label {
                id: currentTime
                text: ""
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: Theme.fontSizeHuge
                color: Theme.highlightColor
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }

    function formatValue(sliderValue)
    {
        var n = Date.now();
        var msCount = n + sliderValue * 60000;
        var nDate = new Date(msCount);
        return nDate.toTimeString().substring(0, 5);
    }

    Component.onCompleted: {
        doneAt.text = appSettings.defaultPlace;
        refreshTimes();
        theTimer.start();
    }

    function generate()
    {
        generator.generate(appSettings.firstName,
                           appSettings.lastName,
                           appSettings.birthDate,
                           appSettings.birthPlace,
                           appSettings.address,
                           motive.currentIndex,
                           doneAt.text,
                           doneTimeShift.value);
        pageStack.push(Qt.resolvedUrl("Preview.qml"));
    }

    function refreshTimes()
    {
        var val = doneTimeShift.value;
        var n = new Date();
        currentTime.text = n.toTimeString().substring(0, 5);
        doneTimeShift.value = -1;
        doneTimeShift.value = val;
    }
}
