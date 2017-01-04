/*
 * Copyright 2016-2017 Raefaldhi Amartya Junior <raefaldhiamartya@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#include "Playlist.h"

#include <cstdlib>

#include <String.h>

#include "internal/PlaylistContentRow.h"

class PlaylistView : public BListView {
public:
	PlaylistView();
	
	virtual void AttachedToWindow();
};

class PlaylistContent : public BColumnListView {
public:
	PlaylistContent();
	~PlaylistContent();
	
	virtual void AttachedToWindow();
	virtual void MessageReceived(BMessage*);
};

BListView* Playlist::pl = NULL;
BColumnListView* Playlist::plc = NULL;
std::vector<entry_ref> Playlist::library;

void Playlist::Init() {
	pl = new PlaylistView();
	plc = new PlaylistContent();
}

BListView* Playlist::GetPlaylist() {
	return pl;
}

BColumnListView* Playlist::GetPlaylistContent() {
	return plc;
}

PlaylistView::PlaylistView()
		 : BListView("Playlist") {
//	Library contains music from your computer
//	Another index would become playlist
	AddItem(new BStringItem("Library"), 0);
}

void PlaylistView::AttachedToWindow() {
	SetSelectionMessage(new BMessage(M_PLAYLIST_ON_SELECT));
	SetTarget(Playlist::GetPlaylistContent());
	
	Select(0);

	BListView::AttachedToWindow();
}

PlaylistContent::PlaylistContent()
		 : BColumnListView("PlaylistContent", B_FANCY_BORDER) {
	AddColumn(new BStringColumn("Title", 50, 50, 300,B_TRUNCATE_END), 0);
	AddColumn(new BStringColumn("Artist", 50, 50, 300,B_TRUNCATE_END), 1);
	AddColumn(new BStringColumn("Album", 50, 50, 300,B_TRUNCATE_END), 2);
	AddColumn(new BStringColumn("Genre", 50, 50, 300,B_TRUNCATE_END), 3);
	AddColumn(new BStringColumn("Years", 50, 50, 300,B_TRUNCATE_END), 4);
	AddColumn(new BStringColumn("Rating", 50, 50, 300,B_TRUNCATE_END), 5);
}

PlaylistContent::~PlaylistContent() {

}

void PlaylistContent::AttachedToWindow() {

}

void PlaylistContent::MessageReceived(BMessage* message) {
	switch (message->what) {
		case M_PLAYLIST_ON_SELECT: {
			Clear();
			switch (Playlist::GetPlaylist()->CurrentSelection()) {
				case 0: {
					for (std::vector<entry_ref>::iterator it = Playlist::library.begin(); it != Playlist::library.end(); it++) {
						BRow* row = new PlaylistContentRow(*it);
						AddRow(row);
					}
				}break;
				default: {
					// Playlist TODO
				}break;
			}
			
		}
		default: {
			BColumnListView::MessageReceived(message);
		}break;
	}	
}
