/*
 * Copyright 2016-2017 Raefaldhi Amartya Junior <raefaldhiamartya@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#ifndef Playlist_H
#define Playlist_H

#include <Entry.h>
#include <ListView.h>
#include <ColumnTypes.h>
#include <ColumnListView.h>

#include <vector>

#include "internal/PlaylistContentRow.h"

enum {
	M_PLAYLIST_ON_SELECT = 'ploa',
	M_CONTENT_ON_SELECT = 'pcoa'
};

class Playlist {
public:
	static void Init();
	static BListView* GetPlaylist();
	static BColumnListView* GetPlaylistContent();

	static BListView* pl;
	static BColumnListView* plc;

	static PlaylistContentRow* CurrentContentSelection;

	static std::vector<entry_ref> library;
private:
	Playlist();
	~Playlist();
};

#endif // Playlist_H
