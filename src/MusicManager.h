/*
 * Copyright 2016-2017 Raefaldhi Amartya Junior <raefaldhiamartya@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#ifndef MusicManager_H
#define MusicManager_H

#include <Application.h>

#include "MusicManagerWindow.h"

class MusicManager : public BApplication {
public:
	MusicManager();
	~MusicManager();
private:
	MusicManagerWindow* mpWindow;
};

#endif // MusicManager_H
