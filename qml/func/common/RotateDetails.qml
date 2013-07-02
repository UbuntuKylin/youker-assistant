import QtQuick 1.1

 Flipable {
     id: container
//     property alias frontContainer: containerFront
     property string title: ""
     property string description: ""
     signal closed
     transform: Rotation {
         id: itemRotation
         origin.x: container.width / 2;
         axis.y: 1; axis.z: 0
     }

     //前面显示内容
     front: Item {
         id: containerFront; anchors.fill: container

         Rectangle {
             anchors.fill: parent
             color: "black"; opacity: 0.4
         }

         Column {
             spacing: 10
             anchors {
                 left: parent.left; leftMargin: 10
                 right: parent.right; rightMargin: 10
                 top: parent.top; topMargin: 120
             }
             Text { font.bold: true; color: "white"; elide: Text.ElideRight; text: container.title; width: parent.width }
             Text { color: "white"; elide: Text.ElideRight; text: container.description; width: parent.width }
         }
     }

     //后面显示内容
     back: Item {
         anchors.fill: container
         Rectangle { anchors.fill: parent; color: "black"; opacity: 0.4 }
         Column {
             spacing: 10
             anchors {
                 left: parent.left; leftMargin: 10
                 right: parent.right; rightMargin: 10
                 top: parent.top; topMargin: 120
             }
             Text { font.bold: true; color: "white"; elide: Text.ElideRight; text: "container.title"; width: parent.width }
             Text { color: "white"; elide: Text.ElideRight; text: "container.description"; width: parent.width }
         }
     }

     states: State {
         name: "Back"
         PropertyChanges { target: itemRotation; angle: 180 }
         PropertyChanges { target: toolBar; button2Visible: false }
         PropertyChanges { target: toolBar; button1Label: qsTr("返回正面") }
     }

     transitions: Transition {
         SequentialAnimation {
             NumberAnimation { easing.type: Easing.InOutQuad; properties: "angle"; duration: 500 }
         }
     }
 }
