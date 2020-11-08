import QtQuick 2.6
import Sailfish.Silica 1.0

Page {
    property string mode_ : "qr"
    id: thePage
    DockedPanel {
        id: theDock
        dock: Dock.Top
        open: true
        modal: false
        onOpenChanged: open = true // prevent hiding
        height: Theme.itemSizeMedium
        Row {
            anchors.left: parent.left
            anchors.right: parent.right
            spacing: Theme.horizontalPageMargin
            leftPadding: Theme.itemSizeMedium
            rightPadding: Theme.itemSizeMedium
            IconButton {
                icon.source: "image://theme/icon-m-file-image"
                onClicked: {
                    mode_ = "qr"
                    mainImage.scale = 3
                }
            }
            IconButton {
                icon.source: "image://theme/icon-m-file-formatted-light"
                onClicked: {
                    mode_ = "text"
                    mainImage.scale = 0.45
                }
            }
            IconButton {
                icon.source: "image://theme/icon-m-file-pdf-light"
                onClicked: generator.savePdf()
            }
        }
    }
    Flickable
    {
        contentWidth: imageContainer.width;
        contentHeight: imageContainer.height
        anchors.fill: parent
        anchors.topMargin: theDock.height
        clip: true

        Rectangle {
            anchors.fill: parent
            color: "white"// ensure white background for this page, otherwise may have code reading issues
        }

        Item {
           id: imageContainer
           width: Math.max(mainImage.width * mainImage.scale, thePage.width)
           height: Math.max(mainImage.height * mainImage.scale, thePage.height - theDock.height)

            Image {
                id: mainImage
                source: mode_ === "qr" ? generator.image2d : generator.imagePdf
                fillMode: Image.PreserveAspectFit
                anchors.centerIn: parent
                scale: thePage.width > mainImage.width?Math.floor(thePage.width / mainImage.width):1
            }
        }
        PinchArea {
            anchors.fill: parent
            anchors.topMargin: theDock.height
            onPinchStarted: function(pinchArg) {
//                console.log("Started: " + pinchArg.scale)
            }
            onPinchUpdated: function(pinchArg) {
//                console.log("Updated: " + pinchArg.scale)
            }
            onPinchFinished: function(pinchArg) {
//                console.log("Finished: " + pinchArg.scale);
            }

            pinch.target: mainImage
            pinch.minimumScale: 0.25
            pinch.maximumScale: 5
            enabled: true
        }
    }

}
