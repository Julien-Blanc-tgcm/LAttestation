import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    property bool multipleMotives : true;
    property int motiveValue : 0
    property int certificateType: 0
    property bool national: true
    property bool local: true

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: Math.max(column.height + footer.height + 3 * column.spacing,
                                parent.height)

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

        Column {
            id: column
            anchors.left: parent.left
            anchors.right: parent.right
            spacing: Theme.paddingMedium
            PageHeader {
                title: qsTr("Content")
            }

            ComboBox {
                id: nationalMotive
                visible: !multipleMotives && national
                width: parent.width
                label: qsTr("Motive (national)")
                menu: ContextMenu {
                    MenuItem {
                        text: qsTr("None")
                        property string codeData: ""
                        property int value: 0
                    }

                    Repeater {
                        model: generator.nationalMotives
                        delegate: MenuItem {
                            text: label
                            property string codeData: model.codeData
                            property int value: model.identifier
                        }
                    }
                }
                onCurrentIndexChanged: {
                    if(currentIndex !== 0)
                        localMotive.currentIndex = 0
                }
            }

            ComboBox {
                id: localMotive
                visible: !multipleMotives && local
                width: parent.width
                label: qsTr("Motive (local)")
                menu: ContextMenu {
                    MenuItem {
                        text: qsTr("None")
                        property string codeData: ""
                        property int value: 0
                    }

                    Repeater {
                        model: generator.localMotives
                        delegate: MenuItem {
                            text: label
                            property string codeData: model.codeData
                            property int value: model.identifier
                        }
                    }
                }
                onCurrentIndexChanged: {
                    if(currentIndex !== 0)
                        nationalMotive.currentIndex = 0
                }
            }


            SectionHeader {
                text: qsTr("National motives")
                visible: multipleMotives && national
            }

            Repeater {
                model: generator.nationalMotives
                delegate: TextSwitch {
                    text: model.label
                    onCheckedChanged: {
                        if(checked)
                            motiveValue |= model.identifier;
                        else
                            motiveValue &= ~model.identifier;
                    }
                    visible: multipleMotives && national
                }
            }

            SectionHeader {
                text: qsTr("Local motives")
                visible: multipleMotives && local
            }

            Repeater {
                model: generator.localMotives
                delegate: TextSwitch {
                    text: model.label
                    onCheckedChanged: {
                        if(checked)
                            motiveValue |= model.identifier;
                        else
                            motiveValue &= ~model.identifier;
                    }
                    visible: multipleMotives  && local
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
        generator.setCertificateType(certificateType)
    }

    function generate()
    {
        var motiveItem = null;
        var motiveV = 0;
        if(nationalMotive.currentIndex !== 0)
            motiveItem = nationalMotive.currentItem;
        if(localMotive.currentIndex !== 0)
            motiveItem = localMotive.currentItem;
        if(motiveItem !== null)
            motiveV = motiveItem.value;
        console.log(motiveV);
        console.log(motiveItem);
        if(multipleMotives)
            motiveV = motiveValue
        generator.generate(certificateType,
                           appSettings.firstName,
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
