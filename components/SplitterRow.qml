import QtQuick 1.1
import "custom" as Components

/*
*
* SplitterRow
*
* SplitterRow is a component that provides a way to layout items horisontally with
* a draggable splitter added in-between each item.
*
* Add items to the SplitterRow by inserting them as child items. The splitter handle
* is outsourced as a delegate (handleBackground). To enable the user to drag the handle,
* it will need to contain a mouse area that communicates with the SplitterRow by binding
* 'drag.target: handle'. The 'handle' property points to the handle item that embedds
* the delegate. To change handle positions, either change 'x' (or 'width') of 'handle', or
* change the width of the child items inside the SplitterRow. If you set the visibility
* of a child item to false, the corresponding handle will also be hidden, and the
* SplitterRow will perform a layout update to fill up available space.
*
* There will always be one (and only one) item in the SplitterRow that is 'expanding'.
* The expanding item is the child that will get all the remaining space in the SplitterRow
* (down to its own mimimumWidth/Height) when all other items have been layed out.
* This means that that 'width', 'percentageWidth' and 'maximumWidth' will be ignored for this item.
* By default, the last visible child item of the SplitterRow will be 'expanding'.
*
* A handle can belong to the item on the left side, or the right side, of the handle. Which one depends
* on the expaning item. If the expanding item is to the right of the handle, the
* handle will belong to the item on the left. If it is to the left, it will belong to the item on the
* right. This will again control which item that gets resized when the user drags a handle, and which
* handle that gets hidden when an item is told to hide.
*
* NB: Since SplitterRow might modify geometry properties like 'width' and 'x' of child items
* to e.g. ensure they stay within minimumWidth/maximumWidth, explicit expression bindings
* to such properties can easily be broken up by the SplitterRow, and is not recommended.
*
* The SplitterRow contains the following API:
*
* Component handleBackground - delegate that will be instanciated between each
*   child item. Inside the delegate, the following properties are available:
*   int handleIndex - specifies the index of the splitter handle. The handle
*       between the first and the second item will get index 0, the next handle index 1 etc.
*   Item handle - convenience property that points to the item where the handle background is
*       instanciated as a child. Identical to splitterRow.handles[handleIndex]. The handle
*       background iteself can be accessed through handle.item.
*       Modify 'handle[d.offset]' to move the handle (or change 'width' of SplitterRow child items).
*   Item splitterItem - convenience property that points to the child item that the handle controls.
*       Also refer to information about the expanding item above.
*   Item splitterRow - points to the SplitterRow that the handle is in.
* List<Item> items - contains the list of child items in the SplitterRow. Currently read-only.
* List<Item> handles - contains the list of splitter handles in the SplitterRow. Note that this list will
*   be populated after all child items has completed, so accessing it from Component.onCompleted
*   inside a SplitterRow child item will not work.  To get to the handle background, access the
*   'background' property of the handle, e.g. handles[0].background. Read-only.
* real preferredWidth/Height - contains the accumulated with of all child items and handles, except
*   the expanding item. If the expanding item has a minimum width, the minimum width will
*   be included.
*
* The following attached properties can optionally be used for each child item of SplitterRow:
*
* real Splitter.minimumSize - ensures that the item cannot be resized below the
*   given pixelvalue. A value of -1 will disable it.
* real Splitter.maximumSixe - ensures that the item cannot be resized above the
*   given value. A value of -1 will disable it.
* real Splitter.percentageSize - This value specifies a percentage (0 - 100) of the width of the
*   SplitterRow width. If the width of the SplitterRow change, the width of the item will
*   change as well. 'percentageWidth' have precedence over 'width', which means that
*   SplitterRow will ignore any assignments to 'width'. A value of -1 disables it.
* bool Splitter.expanding - See explanation of 'expanding' above. If set to true, the current item
*   will be the expanding item in the SplitterRow. If set to false, the SplitterRow will
*   autmatically choose the last visible child of the SplitterRow as expanding instead.
* int Splitter.itemIndex - will be assigned a read-only value with the item index. Can be used to e.g. look-up
*   the handles sourrounding the item (parent.handles[itemIndex])
*
* Example:
*
* To create a SplitterRow with three items, and let
* the center item be the one that should be expanding, one
* could do the following:
*
*    SplitterRow {
*        anchors.fill: parent
*
*        Rectangle {
*            Splitter.maximumWidth: 400
*            color: "gray"
*            width: 200
*        }
*        Rectangle {
*            Splitter.minimumWidth: 50
*            Splitter.expanding: true
*            color: "darkgray"
*        }
*        Rectangle {
*            color: "gray"
*            width: 200
*        }
*    }
*/


Components.Splitter {
    orientation: Qt.Horizontal
    handleBackground: StyleItem {
        id: styleitem
        elementType: "splitter"
        width: handleWidth !== -1 ?  handleWidth : pixelMetric("splitterwidth")
        property alias pressed: mouseArea.pressed
        property bool dragged: mouseArea.drag.active

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            anchors.leftMargin: (parent.width <= 1) ? -2 : 0
            anchors.rightMargin: (parent.width <= 1) ? -2 : 0
            drag.axis: Qt.YAxis
            drag.target: handle

            CursorArea {
                anchors.fill: parent
                cursor: CursorArea.SplitHCursor
            }
        }
    }
}
