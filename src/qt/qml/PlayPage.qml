import QtQuick 2.4
import QVBA 0.1
import Ubuntu.Components 1.3
import Ubuntu.Components.ListItems 1.3 as ListItems
import Ubuntu.Components.Popups 1.3
Page {
    property string slotAction
    property bool showPad: {
        var screenheight = Math.min(width / 240, height / 160) * 160
        if (height - screenheight > buttonBackground.height) {
            return true;
        } else {
            return false;
        }
    }
    Rectangle {
        id: screenContainer
        anchors {
            top: tools.bottom
            bottom: showPad ? buttonBackground.top : parent.bottom
        }
        width: parent.width
        color: "black"
        ScreenArea {
            anchors.centerIn: parent
            property int scale : settings.displayScale == 0 ? Math.min(parent.width / 240, parent.height / 160): settings.displayScale
            width: 241 * scale
            height: 160 * scale
            id: sa
            Connections {
                target: iwindow
                onSDrawScreen: {
                    sa.update()
                }
            }
        }
        Label {
            id: speedLabel
            anchors {
                right: parent.right
                top: parent.top
            }
            visible: settings.configShowSpeed
            text: "Speed: " + iwindow.speed + "%"
        }
        Label {
            anchors {
                right: parent.right
                top: speedLabel.bottom
            }
            visible: settings.configShowFrameSkip
            text: "Frame Skip: " + iwindow.frameSkip
        }
    }
    Rectangle {
        id: buttonBackground
        width: parent.width
        height: units.gu(28)
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        color: showPad ? "white" : "transparent"
        opacity: showPad ? 1.0 : 0.5
        property var buttonsPositions: [
            ["L", 2.25, 21.25, 11, 5, "left", Qt.Key_A, "./img/LButton.png"],
            ["R", 2.25, 21.25, 11, 5, "right", Qt.Key_S, "./img/RButton.png"],
            ["A", 2.5, 5.5, 6.5, 6.5, "right", Qt.Key_Z, "./img/AButton.png"],
            ["B", 9, 3, 6.5, 6.5, "right", Qt.Key_X, "./img/BButton.png"],
            ["Start", 19, 3, 3.5, 3.5, "right", Qt.Key_Return, "./img/circleButton.png"],
            ["Select", 24.5, 3, 3.5, 3.5, "right", Qt.Key_Backspace, "./img/circleButton.png"],
            ["Direct", 3.5, 5, 12, 12, "left", 0, "./img/directionButtons.png"]
        ]
        property var directRatio: 0.31;
        property var lastKeyStatus: [false, false, false, false, false, false, false, false, false, false]
       	property var buttonKeys: [Qt.Key_A, Qt.Key_S, Qt.Key_Z, Qt.Key_X, Qt.Key_Return, Qt.Key_Backspace, Qt.Key_Up, Qt.Key_Left, Qt.Key_Down, Qt.Key_Right]

        MultiPointTouchArea {
            anchors.fill: parent
            onTouchUpdated: {
                for (var i in buttonBackground.lastKeyStatus) {
                    var pressed = false;
                    var buttonKey = buttonBackground.buttonKeys[i];
                    for (var j in touchPoints) {
                        if (i < 6) {
                            if (buttonBackground.buttonsPositions[i][5] == "left") {
                                if (touchPoints[j].x > units.gu(buttonBackground.buttonsPositions[i][1])
                                        && touchPoints[j].x < units.gu(buttonBackground.buttonsPositions[i][1]) + units.gu(buttonBackground.buttonsPositions[i][3])
                                        && touchPoints[j].y > height - units.gu(buttonBackground.buttonsPositions[i][2]) - units.gu(buttonBackground.buttonsPositions[i][4])
                                        && touchPoints[j].y < height - units.gu(buttonBackground.buttonsPositions[i][2])) {
                                    pressed = true
                                }
                            } else {
                                //should be right
                                if (touchPoints[j].x > width - units.gu(buttonBackground.buttonsPositions[i][1]) - units.gu(buttonBackground.buttonsPositions[i][3])
                                        && touchPoints[j].x < width - units.gu(buttonBackground.buttonsPositions[i][1])
                                        && touchPoints[j].y > height - units.gu(buttonBackground.buttonsPositions[i][2]) - units.gu(buttonBackground.buttonsPositions[i][4])
                                        && touchPoints[j].y < height - units.gu(buttonBackground.buttonsPositions[i][2])) {
                                    pressed = true;
                                }
                            }
                       } else {
                            //Direction Button
                            var directButtonWidth = units.gu(buttonBackground.buttonsPositions[6][3]);
                            var directButtonHeight = units.gu(buttonBackground.buttonsPositions[6][4]);
                            var directButtonX = units.gu(buttonBackground.buttonsPositions[6][1]);
                            var directButtonY = height - units.gu(buttonBackground.buttonsPositions[6][1]) - directButtonHeight;
                            var directButtonPosition = [
                                        [directButtonX + buttonBackground.directRatio * directButtonWidth,
                                         directButtonX + (1 - buttonBackground.directRatio) * directButtonWidth,
                                         directButtonY,
                                         directButtonY + buttonBackground.directRatio * directButtonHeight,
                                         Qt.Key_Up],
                                        [directButtonX,
                                         directButtonX + buttonBackground.directRatio * directButtonWidth,
                                         directButtonY + buttonBackground.directRatio * directButtonHeight,
                                         directButtonY + (1 - buttonBackground.directRatio) * directButtonHeight,
                                         Qt.Key_Left],
                                        [directButtonX + buttonBackground.directRatio * directButtonWidth,
                                         directButtonX + (1 - buttonBackground.directRatio) * directButtonWidth,
                                         directButtonY + (1 - buttonBackground.directRatio) * directButtonHeight,
                                         directButtonY + directButtonHeight,
                                         Qt.Key_Down],
                                        [directButtonX + (1 - buttonBackground.directRatio) * directButtonWidth,
                                         directButtonX + directButtonWidth,
                                         directButtonY + buttonBackground.directRatio * directButtonHeight,
                                         directButtonY + (1 - buttonBackground.directRatio) * directButtonHeight,
                                         Qt.Key_Right]
                                    ]
                            if (touchPoints[j].x > directButtonPosition[i - 6][0]
                                    && touchPoints[j].x < directButtonPosition[i - 6][1]
                                    && touchPoints[j].y > directButtonPosition[i - 6][2]
                                    && touchPoints[j].y < directButtonPosition[i - 6][3]) {
                                pressed = true;
                            }
                        }
                    }
                    if (pressed != buttonBackground.lastKeyStatus[i]) {
                       if (pressed) {
                           iwindow.on_key_press_event(buttonKey);
                       } else {
                           iwindow.on_key_release_event(buttonKey);
                       }
                       buttonBackground.lastKeyStatus[i] = pressed;
                    }
                }
            }

            //        MouseArea {
            //            anchors.fill: parent
            //            onClicked: {
            //                console.log(mouse.x / units.gu(1) + " " + (width - mouse.x) / units.gu(1) + " " + (height - mouse.y) / units.gu(1))
            //             }
            //      }
        }

        Repeater {
            model: buttonBackground.buttonsPositions
            delegate: Image {
                source: model.modelData[7]
                anchors {
                    bottom: parent.bottom
                    bottomMargin:  units.gu(model.modelData[2])
                    left: model.modelData[5] == "left" ? parent.left : undefined
                    right: model.modelData[5] == "right" ? parent.right : undefined
                    leftMargin: model.modelData[5] == "left" ? units.gu(model.modelData[1]) : undefined
                    rightMargin: model.modelData[5] == "right" ? units.gu(model.modelData[1]) : undefined
                }
                width: units.gu(model.modelData[3])
                height: units.gu(model.modelData[4])
            }
        }
    }
    
    header: PageHeader {
        id: tools
        
        leadingActionBar.actions: [
            Action {
                text: "Quit"
                iconName: "close"
                onTriggered: {
                    iwindow.vOnFileClose();
                    pageStack.pop();
                }
            }
        ]

        trailingActionBar.actions: [
            Action {
                text: "Settings"
                iconName: "settings"
                onTriggered: {
                    pageStack.push(Qt.resolvedUrl("SettingPage.qml"));
                }
            },
            Action {
                text: "Load Slot"
                iconName: "keyboard-caps-disabled"
                onTriggered: {
                    slotAction = "load";
                    PopupUtils.open(slotSheet)
                }
            },
            Action {
                text: "Save Slot"
                iconName: "save"
                onTriggered: {
                   slotAction = "save";
                   PopupUtils.open(slotSheet)
                }
            }
        ]
    }
    Component {
        id: slotSheet
        DefaultSheet {
            id: sheet
            title: slotAction
            doneButton: false
            ListView {
                anchors.fill: parent
                model: iwindow.gameSlot
                clip: true
                delegate: ListItems.Standard {
                    text: model.isEmpty ? model.time : "<font color='purple'>" + model.time + "</font>"
                    onClicked: {
                        if (slotAction === "save") {
                            iwindow.vOnSaveGame(model.index + 1);
                        } else if (slotAction === "load") {
                            iwindow.vOnLoadGame(model.index + 1);
                        }
                        PopupUtils.close(sheet);
                        tools.close();
                    }
                }
            }
        }
    }
}
