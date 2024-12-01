pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Controls
import QtQuick.Controls.FluentWinUI3
import QtQuick.Layouts
import untitled

Item {
    MyCalendarModel{
        id:dataModel
        //https://www.mardy.it/blog/2016/11/qml-trick-force-re-evaluation-of.html
        property int updateCounter: 0
        onDataChanged: updateCounter++;
    }

    Rectangle {
        id: rectangle
        width: 1920
        height: 1080

        color: "#EAEAEA"

        Button {
            id: button
            width: 274
            height: 104
            text: qsTr("Mark Workout Completed")
            anchors.verticalCenter: parent.verticalCenter
            font.pointSize: 15
            anchors.verticalCenterOffset: 31
            anchors.horizontalCenterOffset: 707
            checkable: false
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: dataModel.addData()
        }

        Page {
            id: page
            x: 0
            y: 0
            width: 1920
            height: 83

            Text {
                id: _text
                x: 720
                y: 20
                text: qsTr("Workout Tracking App - Calendar")
                font.pixelSize: 33
                horizontalAlignment: Text.AlignHCenter
            }
        }

        Rectangle {
            id: rectangle1
            x: 1388
            y: 82
            width: 18
            height: 998
            color: "#ffffff"
        }



        SwipeView {
            id: swipeView
            x: 272
            y: 159
            width: 969
            height: 897
            clip: true

            ListView {
                id: listview
                x: -958
                y: -298

                width: 0; height: 0
                boundsMovement: Flickable.StopAtBounds
                boundsBehavior: Flickable.StopAtBounds
                synchronousDrag: false
                snapMode: ListView.SnapOneItem
                orientation: ListView.Vertical
                highlightRangeMode: ListView.StrictlyEnforceRange

                model: CalendarModel {
                    from: new Date(2024, 0, 1)
                    to: new Date(2024, 11, 31)
                }

                delegate: GridLayout {
                    required property var model
                    width: listview.width
                    height: listview.height
                    id:calendarLayout
                    columns: 1

                    Text{
                        text:"Month " + (model.month+1)
                        font.bold: true
                        font.pixelSize: 30
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                       // width:listview.width
                    }

                    DayOfWeekRow {
                        locale: grid.locale

                        Layout.column: 1
                        Layout.fillWidth: true
                    }

                    MonthGrid {
                        id: grid
                        month: model.month
                        year: model.year

                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        delegate: Rectangle{
                            required property var model
                            opacity: model.month === grid.month ? 1 : 0
                            radius:width / 2
                            color: dataModel.updateCounter,dataModel.exerciseOnDate(model.year,model.day,model.month) ? "green" : "white"
                            Text{
                                anchors.fill: parent
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                text: model.day
                                fontSizeMode: Text.fit
                                }
                        }
                    }
                }

                states:[
                    State {
                        name:"normal"
                    },
                    State{
                        name:"needReload"
                        when: button.pressed
                        StateChangeScript {
                            name : "script"
                            script:  dataModel.updateCounter++;//listview.forceLayout();
                        }
                    }

                ]

                ScrollIndicator.horizontal: ScrollIndicator { }
            }
        }





        states: [
            State {
                name: "clicked"
                when: button.checked
            }
        ]
    }

}

