import QtQuick 1.1

//import QtDesktop 0.1
import "../common" as Common
Item {
     id: toolbar

     property bool showok: true
     signal cancelBtnClicked
     signal gobackBtnClicked
     signal continueBtnClicked

     BorderImage {
 //        source: "../../img/icons/tab.png"
         width: parent.width; height: parent.height + 14; y: -7
     }

     Rectangle{id: splitbar; x:2; width:parent.width - 4 ; height:1; color:"#b9c5cc"}

     Row {
         spacing: 30
         height: 32
         anchors {
             right: parent.right
             rightMargin: 5
             top: splitbar.bottom
             topMargin: 10
         }

//         anchors.right: parent.right; anchors.rightMargin: 5; y: 3; height: 32; spacing: 30
         Common.Button {
             id: cancelBtn
             visible: toolbar.showok
             //hoverimage: "list_item_active.png"
             text: "取消"
             width: 94; height: 29
             onClicked:
             {
                 toolbar.cancelBtnClicked()
             }
         }

         Common.Button {
            id: gobackBtn
            visible: toolbar.showok
           // hoverimage: "list_item_active.png"
            text: "上一步"
            width: 94; height: 29
            onClicked: toolbar.gobackBtnClicked()
         }
         Common.Button {
             id: continueBtn
           //  hoverimage: "list_item_active.png"
             text: "下一步"
             width: 94; height: 29
             onClicked: toolbar.continueBtnClicked()
         }
     }
}
