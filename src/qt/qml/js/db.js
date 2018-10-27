/*
 * uNav http://launchpad.net/unav
 * Copyright (C) 2015 JkB https://launchpad.net/~joergberroth
 * Copyright (C) 2015 Marcos Alvarez Costales https://launchpad.net/~costales
 *
 * uNav is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * uNav is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
// Thanks http://askubuntu.com/questions/352157/how-to-use-a-sqlite-database-from-qml


function openDB() {

    var db = LocalStorage.openDatabaseSync("qvbam_db", "0.1", "QVBAM settings", 1000);
    try {
        db.transaction(function(tx){
            tx.executeSql('CREATE TABLE IF NOT EXISTS settings( enablesound BOOL, showspeed BOOL, showframeskip BOOL, scale INT)');
        });
    } catch (err) {
        console.log("Error creating table in database: " + err)
    } return db
}

// Save Settings
function storeSettings(enablesound, showspeed, showframeskip, scale) {
    var db = openDB();
    db.transaction(function(tx){
        tx.executeSql('INSERT OR REPLACE INTO settings (enablesound, showspeed, showframeskip, scale) VALUES(?, ?, ?, ?)', [enablesound, showspeed, showframeskip, scale]); //null is the automatic id
    });
}

// get Settings
function getSettings() {

	var enablesound;
	var showspeed;
	var showframeskip;
	var scale;

	var db = openDB();

	db.transaction(function(tx) {
		var rs = tx.executeSql('SELECT * FROM settings');

		if(rs.rows.length > 0)
		{
			enablesound = rs.rows.item(0).enablesound;
			showspeed = rs.rows.item(0).showspeed;
			showframeskip = rs.rows.item(0).showframeskip;
			scale = rs.rows.item(0).scale;
		}
		else
		{
			console.log("loading default settings");
			// set defaults
			enablesound = true;
			showspeed = false;
			showframeskip = false;
			scale = 0; // 0 is auto
		}
	});

	return {
		enablesound: enablesound,
		showspeed: showspeed,
		showframeskip: showframeskip,
		scale: scale
	}
}

