import QtQuick 2.0
import Sailfish.Silica 1.0

Dialog {
    id: page

    // The effective value will be restricted by ApplicationWindow.allowedOrientations
    allowedOrientations: Orientation.All

    SilicaFlickable {
        id: list
        anchors.fill: parent
        contentHeight: column.height
        Column {
            id: column
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: parent.leftMargin
            anchors.rightMargin: parent.rightMargin
            DialogHeader{
                title: qsTr("Parameters") // Paramètres
            }
            TextField {
                id: firstName
                width: parent.width
                label: qsTr("First name") // Prénom
                placeholderText: "Camille"
                EnterKey.enabled: text.length > 0
                EnterKey.iconSource: "image://theme/icon-m-enter-next"
                EnterKey.onClicked: lastName.focus = true
            }
            TextField {
                id: lastName
                width: parent.width
                label: qsTr("Surname") // Nom
                placeholderText: "Dupont"
                EnterKey.enabled: text.length > 0
                EnterKey.iconSource: "image://theme/icon-m-enter-next"
                EnterKey.onClicked: birthDate.focus = true
            }
            TextField {
                id: birthDate
                width: parent.width
                label: qsTr("Birth date") // Date de naissance
                placeholderText: "01/01/1970"
                EnterKey.enabled: text.length > 0
                EnterKey.iconSource: "image://theme/icon-m-enter-next"
                EnterKey.onClicked: birthPlace.focus = true
            }
            TextField {
                id: birthPlace
                width: parent.width
                label: qsTr("Birth place") // Lieu de naissance
                placeholderText: "Paris"
                EnterKey.enabled: text.length > 0
                EnterKey.iconSource: "image://theme/icon-m-enter-next"
                EnterKey.onClicked: address.focus = true
            }
            TextField {
                id: address
                width: parent.width
                label: qsTr("Address") // Adresse
                placeholderText: "55 rue du faubourg Saint-Honoré, 75008 Paris"
                EnterKey.enabled: text.length > 0
                EnterKey.iconSource: "image://theme/icon-m-enter-next"
                EnterKey.onClicked: defaultPlace.focus = true
            }
            TextField {
                id: defaultPlace
                width: parent.width
                label: qsTr("Default 'Done at' value") // Valeur par défaut pour le « fait à »
                placeholderText: "Paris"
                EnterKey.enabled: text.length > 0
                EnterKey.iconSource: "image://theme/icon-m-enter-accept"
                EnterKey.onClicked: accept()
            }
            TextSwitch {
                id: enableOoops
                width: parent.width
                text: qsTr("Activate 'ooops' mode") // Activer le mode « oups »
            }
        }
    }
    onAccepted: {
        appSettings.firstName = firstName.text;
        appSettings.lastName = lastName.text;
        appSettings.birthDate = birthDate.text;
        appSettings.birthPlace = birthPlace.text;
        appSettings.address = address.text;
        appSettings.defaultPlace = defaultPlace.text;
        appSettings.ooopsEnabled = enableOoops.checked
        appSettings.save();
    }
    Component.onCompleted: {
        firstName.text = appSettings.firstName
        lastName.text = appSettings.lastName
        birthDate.text = appSettings.birthDate
        birthPlace.text = appSettings.birthPlace
        address.text = appSettings.address
        defaultPlace.text = appSettings.defaultPlace
        enableOoops.checked = appSettings.ooopsEnabled
    }
}
