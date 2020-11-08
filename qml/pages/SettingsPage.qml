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
                title: qsTr("Paramètres")
            }
            TextField {
                id: firstName
                width: parent.width
                label: qsTr("Prénom")
                placeholderText: "Camille"
                EnterKey.enabled: text.length > 0
                EnterKey.iconSource: "image://theme/icon-m-enter-next"
                EnterKey.onClicked: lastName.focus = true
            }
            TextField {
                id: lastName
                width: parent.width
                label: qsTr("Nom")
                placeholderText: "Dupont"
                EnterKey.enabled: text.length > 0
                EnterKey.iconSource: "image://theme/icon-m-enter-next"
                EnterKey.onClicked: birthDate.focus = true
            }
            TextField {
                id: birthDate
                width: parent.width
                label: qsTr("Date de naissance")
                placeholderText: "01/01/1970"
                EnterKey.enabled: text.length > 0
                EnterKey.iconSource: "image://theme/icon-m-enter-next"
                EnterKey.onClicked: birthPlace.focus = true
            }
            TextField {
                id: birthPlace
                width: parent.width
                label: qsTr("Lieu de naissance")
                placeholderText: "Paris"
                EnterKey.enabled: text.length > 0
                EnterKey.iconSource: "image://theme/icon-m-enter-next"
                EnterKey.onClicked: address.focus = true
            }
            TextField {
                id: address
                width: parent.width
                label: qsTr("Adresse")
                placeholderText: "55 rue du faubourg Saint-Honoré, 75008 Paris"
                EnterKey.enabled: text.length > 0
                EnterKey.iconSource: "image://theme/icon-m-enter-next"
                EnterKey.onClicked: defaultPlace.focus = true
            }
            TextField {
                id: defaultPlace
                width: parent.width
                label: qsTr("Valeur par défaut pour le « fait à »")
                placeholderText: "55 rue du faubourg Saint-Honoré, 75008 Paris"
                EnterKey.enabled: text.length > 0
                EnterKey.iconSource: "image://theme/icon-m-enter-accept"
                EnterKey.onClicked: accept()
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
        appSettings.save();
    }
    Component.onCompleted: {
        firstName.text = appSettings.firstName
        lastName.text = appSettings.lastName
        birthDate.text = appSettings.birthDate
        birthPlace.text = appSettings.birthPlace
        address.text = appSettings.address
        defaultPlace.text = appSettings.defaultPlace
    }
}
