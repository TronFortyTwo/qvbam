import QtQuick 2.4
import U1db 1.0 as U1db
Item {
    property bool enableSound: true
    property bool configShowSpeed: true;
    property bool configShowFrameSkip: true;
    property int displayScale: 0; //0 for automatic
    Component.onCompleted: load();
    onEnableSoundChanged: {
        iwindow.config.mute = !enableSound
    }
    onDisplayScaleChanged: save();
    U1db.Database {
        id: aDatabase
        path: "aU1DbDatabase"
    }

    U1db.Document {
        id: aDocument
        database: aDatabase
        docId: 'settings'
        create: true
        defaults: {
            enableSound: true
            configShowSpeed: true
            configShowFrameSkip: true
        }
    }
    function load() {
        var settings = aDocument.contents;
        if (settings.enableSound !== undefined) {
            enableSound = settings.enableSound;
            configShowSpeed = settings.configShowSpeed;
            configShowFrameSkip = settings.configShowFrameSkip;
            displayScale = settings.displayScale;
        }
    }
    function save() {
        var settings = aDocument.contents;
        settings.enableSound = enableSound;
        settings.configShowSpeed = configShowSpeed;
        settings.configShowFrameSkip = configShowFrameSkip;
        settings.displayScale = displayScale;
        aDocument.contents = settings;
    }
}
