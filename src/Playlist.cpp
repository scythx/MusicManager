/*
 * Copyright 2016-2017 Raefaldhi Amartya Junior <raefaldhiamartya@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#include "Playlist.h"

#include <cstdlib>

#include <String.h>
#include <Messenger.h>

#include "Control.h"

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
PlaylistContentRow* Playlist::CurrentContentSelection = NULL;
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
	SetExplicitMinSize(BSize(120, B_SIZE_UNSET));
	SetExplicitMaxSize(BSize(120, B_SIZE_UNSET));

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
	AddColumn(new BIntegerColumn("Track", 100, 100, 300), 0);
	AddColumn(new BStringColumn("Title", 100, 100, 300,B_TRUNCATE_END), 1);
	AddColumn(new BStringColumn("Artist", 100, 100, 300,B_TRUNCATE_END), 2);
	AddColumn(new BStringColumn("Album", 100, 100, 300,B_TRUNCATE_END), 3);
	AddColumn(new BStringColumn("Genre", 100, 100, 300,B_TRUNCATE_END), 4);
	AddColumn(new BIntegerColumn("Year", 100, 100, 300), 5);
	AddColumn(new BStringColumn("Comment", 100, 100, 300,B_TRUNCATE_END), 6);
}

PlaylistContent::~PlaylistContent() {

}

void PlaylistContent::AttachedToWindow() {
	SetTarget(this);

	SetSelectionMessage(new BMessage(M_CONTENT_ON_SELECT));

	BColumnListView::AttachedToWindow();
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
		case M_CONTENT_ON_SELECT: {
			Playlist::CurrentContentSelection = (PlaylistContentRow*)CurrentSelection();
			BMessenger messenger(Control::_ArtworkView);
			messenger.SendMessage(new BMessage('jkla'));
		}break;
		default: {
			BColumnListView::MessageReceived(message);
		}break;
	}	
}
