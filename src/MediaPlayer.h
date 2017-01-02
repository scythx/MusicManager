/*
 * Copyright 2016-2017 Raefaldhi Amartya Junior <raefaldhiamartya@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#ifndef MediaPlayer_H
#define MediaPlayer_H

#include <Application.h>

#include "MediaPlayerWindow.h"

class MediaPlayer : public BApplication {
public:
	MediaPlayer();
	~MediaPlayer();
private:
	MediaPlayerWindow* mpWindow;
};

#endif // MediaPlayer_H
