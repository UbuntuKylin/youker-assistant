import QtQuick 2.0
import "./defaultstyle" as DefaultStyle

//Row {
//    spacing: 20
//    MyCheckBox {
//        id: radiobutton1
//        checkmark: defaultStyle1.checkmark
//        background: defaultStyle1.background
//        DefaultStyles.RadioButtonStyle { id: defaultStyle1}
//    }
//    MyCheckBox {
//        id: radiobutton2
//        checkmark: defaultStyle2.checkmark
//        background: defaultStyle2.background
//        DefaultStyles.RadioButtonStyle { id: defaultStyle2}
//    }
//}
MyCheckBox {
    id: radiobutton1
    checkmark: defaultStyle1.checkmark
    background: defaultStyle1.background
    DefaultStyle.RadioButtonStyle { id: defaultStyle1}
}
