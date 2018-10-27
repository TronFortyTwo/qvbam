import QtQuick 2.4
import Qt.labs.settings 1.0

Item {
	id: settingsItem

	property int displayScale: settings.displayScale;
	property bool enableSound: settings.enableSound;
	property bool configShowSpeed: settings.configShowSpeed;
	property bool configShowFrameSkip: settings.configShowFrameSkip;

	onEnableSoundChanged: {
		iwindow.config.mute = !enableSound;
	}
	onDisplayScaleChanged: save();
	
	function save() {
		settings.enableSound = settingsItem.enableSound;
		settings.configShowSpeed = settingsItem.configShowSpeed;
		settings.configShowFrameSkip = settingsItem.configShowFrameSkip;
		settings.displayScale = settingsItem.displayScale;
	}

	Settings {
		id: settings
		property bool enableSound: true;
	        property bool configShowSpeed: false;
	        property bool configShowFrameSkip: false;
	        property int displayScale: 0;
	}
}
