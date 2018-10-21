import QtQuick 2.4
import "js/db.js" as DB

Item {
	property bool enableSound: true
	property bool configShowSpeed: false;
	property bool configShowFrameSkip: false;
	property int displayScale: 0; //0 for automatic
    
	Component.onCompleted: load();
    
	onEnableSoundChanged: {
		iwindow.config.mute = !enableSound
	}
	onDisplayScaleChanged: save();
    
	function load() {
		var settings = DB.getSettings();
		enableSound = settings.enablesound;
		configShowSpeed = settings.showspeed;
		configShowFrameSkip = settings.showframeskip;
		displayScale = settings.scale;
	}
	
	function save() {
		DB.storeSettings("enableSound", "configShowSpeed", "configShowFrameSkip", "displayScale");
	}
}
