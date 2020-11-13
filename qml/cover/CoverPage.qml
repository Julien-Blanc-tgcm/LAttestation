import QtQuick 2.0
import Sailfish.Silica 1.0

CoverBackground {
    Label {
        id: label
        anchors.centerIn: parent
        text: qsTr("Certificate of discharge")
        wrapMode: Text.Wrap
        width: parent.width - Theme.horizontalPageMargin
        horizontalAlignment: Text.AlignHCenter
    }

}
