import QtQuick 2.4
import Ubuntu.Components 1.3
import Ubuntu.Components.ListItems 1.3 as ListItem
Page {
    title: "Settings"
    
    Flickable {
        id: flickable2
        anchors.fill: parent
        contentHeight: column.height
        Column {
            id: column
            width: parent.width
            ListItem.Standard {
                text: "Enable Sound"
                control: Switch {
                    id: enableSoundSwitch
                    checked: settings.enableSound
                    onCheckedChanged: {
                        settings.enableSound = checked;
                        settings.save();
                    }
                }
            }
            ListItem.Standard {
                text: "Show speed"
                control: Switch {
                    checked: settings.configShowSpeed
                    onCheckedChanged: {
                        settings.configShowSpeed = checked;
                        settings.save();
                    }
                }
            }
            ListItem.Standard {
                text: "Show frame skip"
                control: Switch {
                    checked: settings.configShowFrameSkip
                    onCheckedChanged: {
                        settings.configShowFrameSkip = checked;
                        settings.save();
                    }
                }
            }
            ListItem.ItemSelector {
                text: i18n.tr("Scale")
                model: ["auto", "x1", "x2", "x3", "x4", "x5", "x6"]
                selectedIndex: settings.displayScale;
                onSelectedIndexChanged: settings.displayScale = selectedIndex;
            }
        }
    }
    flickable: flickable2
}
