/*
 * Copyright 2016-2017 Raefaldhi Amartya Junior <raefaldhiamartya@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#include "MediaPlayer.h"

int main(int argc, char *argv[]) {
	MediaPlayer mp;
	mp.Run();
	
	return 0;
}

MediaPlayer::MediaPlayer() : BApplication("application/x-vnd.Haiku-MediaPlayer") {
	mpWindow = new MediaPlayerWindow();
	mpWindow->Show();
}

MediaPlayer::~MediaPlayer() {
	delete mpWindow;
}
