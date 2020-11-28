import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    property bool multipleMotives : false;
    property int motiveValue : 0

    ListModel {
        id: motivesModel
        ListElement {
            name: qsTr("Shopping")
            value: 0x1;
        }
        ListElement {
            name: qsTr("Sport / hobbies")  // Loisirs - Sport
            value: 0x2;
        }
        ListElement {
            name: qsTr("Professional") // Déplacement pro
            value: 0x4;
        }
        ListElement {
            name: qsTr("Medical consultation") // Consultation médicale
            value: 0x8
        }
        ListElement {
            name: qsTr("Help vulnerable people") // Assistance pers. vulnérable
            value: 0x10
        }
        ListElement {
            name: qsTr("Public interest") // Mission intérêt public
            value: 0x20
        }
        ListElement {
            name: qsTr("Children accompanying") // Accompagnement enfants
            value: 0x40
        }
        ListElement {
            name: qsTr("Convocation") // Convocation
            value: 0x80
        }
        ListElement {
            name: qsTr("Assistance to disabled") // Aide pers. handicapée
            value: 0x100
        }
    }

    SilicaFlickable {
        Timer {
            id: theTimer
            interval: 1000
            repeat: true
            onTriggered: refreshTimes()
        }

        PullDownMenu {
            MenuItem {
                text: qsTr("Use multiple motives")
                onClicked: {
                    multipleMotives = true;
                }
                visible: multipleMotives === false
            }
            MenuItem {
                text: qsTr("Use single motive")
                onClicked: {
                    multipleMotives = false;
                }
                visible: multipleMotives === true
            }
            MenuItem {
                text: qsTr("Increase time range")
                onClicked: {
                    doneTimeShift.maximumValue = doneTimeShift.maximumValue * 2
                    doneTimeShift.minimumValue = doneTimeShift.minimumValue * 2
                }
            }
        }



        anchors.fill: parent
        contentHeight: Math.max(column.height + footer.height + 3 * column.spacing,
                                parent.height)
        Column {
            id: column
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: Theme.horizontalPageMargin
            anchors.rightMargin: Theme.horizontalPageMargin
            spacing: Theme.paddingMedium
            PageHeader {
                title: qsTr("Content")
            }

            ComboBox {
                id: motive
                visible: multipleMotives === false
                width: parent.width
                label: qsTr("Motive")
                menu: ContextMenu {
                    Repeater {
                        model: motivesModel
                        delegate: MenuItem {
                            text: model.name
                        }
                    }
                }
            }

            Repeater {
                model: motivesModel
                delegate: TextSwitch {
                    text: model.name
                    onCheckedChanged: {
                        if(checked)
                            motiveValue |= model.value;
                        else
                            motiveValue &= ~model.value;
                    }
                    visible: multipleMotives === true
                }
            }

            TextField {
                id: doneAt
                width: parent.width
                label: qsTr("Done at") // Fait à
                placeholderText: qsTr("Done at") // Fait à
            }
            Slider {
                id: doneTimeShift
                label: qsTr("Out hour") // Heure de sortie
                width: parent.width
                minimumValue: -120
                maximumValue: 30
                stepSize: 1
                value: 0
                valueText: formatValue(value)
            }

            Button {
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("Generate") // Générer
                onClicked: generate()
            }
        }
        Row {
            id: footer
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
        var motiveV = 1 << motive.currentIndex;
        if(multipleMotives)
            motiveV = motiveValue
        generator.generate(appSettings.firstName,
                           appSettings.lastName,
                           appSettings.birthDate,
                           appSettings.birthPlace,
                           appSettings.address,
                           motiveV,
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
