import QtQuick 2.6
import Sailfish.Silica 1.0

Page {

    BusyIndicator {
        anchors.centerIn: parent
        running: true
        size: BusyIndicatorSize.Large
    }

    Timer {
        onTriggered: { generator.generate(appSettings.firstName,
                                          appSettings.lastName,
                                          appSettings.birthDate,
                                          appSettings.birthPlace,
                                          appSettings.address,
                                          0,
                                          appSettings.defaultPlace,
                                          timeshift_()) }
        interval: 500
        repeat: false
        id: timer
    }

    Timer {
        id: timer2
        interval: 1000
        repeat: false
        onTriggered: pageStack.pop()
    }

    Component.onCompleted: {
        generator.onImagePdfChanged.connect(view_)
        timer.start();
    }
    Component.onDestruction: {
        generator.onImagePdfChanged.disconnect(view_)
    }

    function view_()
    {
        generator.viewPdf();
        timer2.start()
    }

    function timeshift_()
    {
        return Math.floor(-30 + 10 * Math.random())
    }
}
