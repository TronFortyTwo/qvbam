import QtQuick 2.4
import Ubuntu.Components 1.3
import Ubuntu.Components.ListItems 1.3 as ListItem
import Ubuntu.Components.Popups 1.3
Tabs {
    id: tabs
    Tab {
        id: romTab
        title: "Load Roms"
        page: Page {
            head.actions: [
                Action {
                    iconName: "add"
                    text: i18n.tr("Import")
                    onTriggered: PopupUtils.open(contentPickerDialog)
                }
            ]
            ListView {
                anchors.fill: parent
                model: romsModel.files
                delegate: ListItem.Standard {
                    text: model.modelData
                    removable: true;
                    confirmRemoval: true;
                    onClicked: {
                        iwindow.bLoadRomInQML(model.modelData)
                        pageStack.push(Qt.resolvedUrl("PlayPage.qml"))
                    }
                    onItemRemoved: {
                        romsModel.removeFile(model.modelData)
                    }
                }
            }
        }
    }

    Tab {
        id: settingTab
        title: "Settings"
        page: SettingPage {

        }
    }

    ContentPickerDialog {
        id: contentPickerDialog
    }
}
