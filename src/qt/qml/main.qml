import QtQuick 2.4
import QVBA 0.1
import Ubuntu.Components 1.3

MainView {
    id: mainView
    width: units.gu(48)
    height: units.gu(70)
    backgroundColor: UbuntuColors.porcelain
    automaticOrientation: true
    applicationName: "emanuelesorce.qvbam"
    PageStack {
        id: pageStack
        Component.onCompleted: {
            push(Qt.resolvedUrl("TopPage.qml"))
        }
    }

    Settings {
        id: settings
    }

    PlayPage {
        id: playPage
        visible: false
    }
    focus: true
    Keys.onPressed: {
        iwindow.on_key_press_event(event.key);
    }
    Keys.onReleased: {
        iwindow.on_key_release_event(event.key);
    }
    Connections {
        target: Qt.application
        onActiveChanged: {
            if (Qt.application.active) {
                iwindow.paused = false;
            } else {
                iwindow.paused = true;
            }
        }
    }
}
