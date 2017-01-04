/*
 * Copyright 2016-2017 Raefaldhi Amartya Junior <raefaldhiamartya@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#include "MusicManager.h"

#include "Control.h"
#include "Playlist.h"
#include "Query.h"

int main(int argc, char *argv[]) {
	MusicManager mp;
	mp.Run();
	
	return 0;
}

MusicManager::MusicManager() : BApplication("application/x-vnd.Haiku-MusicManager") {
	Playlist::Init();
	Query::Init();

	mpWindow = new MusicManagerWindow();
	mpWindow->Show();
}

MusicManager::~MusicManager() {
	delete mpWindow;
}
