import QtQuick 1.1
import "custom" as Components

/*
*
* SplitterColumn
*
* SplitterColumn is a component that provides a way to layout items horisontally with
* a draggable splitter added in-between each item.
*
* Add items to the SplitterColumn by inserting them as child items. The splitter handle
* is outsourced as a delegate (handleBackground). To enable the user to drag the handle,
* it will need to contain a mouse area that communicates with the SplitterColumn by binding
* 'drag.target: handle'. The 'handle' property points to the handle item that embedds
* the delegate. To change handle positions, either change 'y; (or 'height') of 'handle', or
* change the height of the child items inside the SplitterColumn. If you set the visibility
* of a child item to false, the corresponding handle will also be hidden, and the
* SplitterColumn will perform a layout update to fill up available space.
*
* There will always be one (and only one) item in the SplitterColumn that is 'expanding'.
* The expanding item is the child that will get all the remaining space in the SplitterColumn
* (down to its own mimimumHeight/Height) when all other items have been layed out.
* This means that that 'height', 'percentageHeight' and 'maximumHeight' will be ignored for this item.
* By default, the last visible child item of the SplitterColumn will be 'expanding'.
*
* A handle can belong to the item on the left side, or the right side, of the handle. Which one depends
* on the expaning item. If the expanding item is to the right of the handle, the
* handle will belong to the item on the left. If it is to the left, it will belong to the item on the
* right. This will again control which item that gets resized when the user drags a handle, and which
* handle that gets hidden when an item is told to hide.
*
* NB: Since SplitterColumn might modify geometry properties like 'height' and 'y; of child items
* to e.g. ensure they stay within minimumHeight/maximumHeight, explicit expression bindings
* to such properties can easily be broken up by the SplitterColumn, and is not recommended.
*
* The SplitterColumn contains the following API:
*
* Component handleBackground - delegate that will be instanciated between each
*   child item. Inside the delegate, the following properties are available:
*   int handleIndex - specifies the index of the splitter handle. The handle
*       between the first and the second item will get index 0, the next handle index 1 etc.
*   Item handle - convenience property that points to the item where the handle background is
*       instanciated as a child. Identical to splitterColumn.handles[handleIndex]. The handle
*       background iteself can be accessed through handle.item.
*       Modify 'handle[d.offset]' to move the handle (or change 'height' of SplitterColumn child items).
*   Item splitterItem - convenience property that points to the child item that the handle controls.
*       Also refer to information about the expanding item above.
*   Item splitterColumn - points to the SplitterColumn that the handle is in.
* List<Item> items - contains the list of child items in the SplitterColumn. Currently read-only.
* List<Item> handles - contains the list of splitter handles in the SplitterColumn. Note that this list will
*   be populated after all child items has completed, so accessing it from Component.onCompleted
*   inside a SplitterColumn child item will not work.  To get to the handle background, access the
*   'background' property of the handle, e.g. handles[0].background. Read-only.
* real preferredHeight/Height - contains the accumulated with of all child items and handles, except
*   the expanding item. If the expanding item has a minimum height, the minimum height will
*   be included.
*
* The following attached properties can be used for each child item of SplitterColumn:
*
* real Splitter.minimumSize - ensures that the item cannot be resized below the
*   given pixelvalue. A value of -1 will disable it.
* real Splitter.maximumSize - ensures that the item cannot be resized above the
*   given pixelvalue. A value of -1 will disable it.
* real percentageHeight - This value specifies a percentage (0 - 100) of the height of the
*   SplitterColumn height. If the height of the SplitterColumn change, the height of the item will
*   change as well. 'percentageHeight' have precedence over 'height', which means that
*   SplitterColumn will ignore any assignments to 'height'. A value of -1 disables it.
* bool Splitter.expanding - See explanation of 'expanding' above. If set to true, the current item
*   will be the expanding item in the SplitterColumn. If set to false, the SplitterColumn will
*   autmatically choose the last visible child of the SplitterColumn as expanding instead.
* int Splitter.itemIndex - will be assigned a read-only value with the item index. Can be used to e.g. look-up
*   the handles sourrounding the item (parent.handles[itemIndex])
*
* Example:
*
* To create a SplitterColumn with three items, and let
* the center item be the one that should be expanding, one
* could do the following:
*
*    SplitterColumn {
*        anchors.fill: parent
*
*        Rectangle {
*            Splitter.maximumSize: 400
*            color: "gray"
*            height: 200
*        }
*        Rectangle {
*            Splitter.minimumSize: 50
*            Splitter.expanding: true
*            color: "darkgray"
*        }
*        Rectangle {
*            color: "gray"
*            height: 200
*        }
*    }
*/

Components.Splitter {
    orientation: Qt.Vertical
    handleBackground: StyleItem {
        id: styleitem
        elementType: "splitter"
        height: handleWidth !== -1 ?  handleWidth : pixelMetric("splitterwidth")
        horizontal: false
        property alias pressed: mouseArea.pressed
        property bool dragged: mouseArea.drag.active

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            anchors.topMargin: (parent.height <= 1) ? -2 : 0
            anchors.bottomMargin: (parent.height <= 1) ? -2 : 0
            drag.axis: Drag.XandYAxis // Why doesn't X-axis work?
            drag.target: handle
            CursorArea {
                anchors.fill: parent
                cursor: CursorArea.SplitVCursor
            }
        }
    }
}
