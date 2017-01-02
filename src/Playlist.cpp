/*
 * Copyright 2016-2017 Raefaldhi Amartya Junior <raefaldhiamartya@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#include "Playlist.h"

#include <String.h>
#include <ColumnTypes.h>
#include <fs_attr.h>
#include <Node.h>
#include <Query.h>
#include <Volume.h>
#include <VolumeRoster.h>

class PlaylistView : public BListView {
public:
	PlaylistView();
	
	virtual void AttachedToWindow();
	virtual void MessageReceived(BMessage*);
};

class PlaylistContent : public BColumnListView {
public:
	PlaylistContent();
	
	virtual void MessageReceived(BMessage*);
};

BListView* Playlist::pl = NULL;
BColumnListView* Playlist::plc = NULL;

void Playlist::Initialize() {
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
	AddItem(new BStringItem("Library"), 0);
}

void PlaylistView::AttachedToWindow() {
	SetSelectionMessage(new BMessage(M_PLAYLIST_ON_SELECT));
	SetTarget(Playlist::GetPlaylistContent());
	
	Select(0);

	BListView::AttachedToWindow();
}

void PlaylistView::MessageReceived(BMessage* message) {
	switch (message->what) {
		case M_PLAYLIST_ON_SELECT: {
		}
		default: {
			BListView::MessageReceived(message);
		}break;
	}
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

void PlaylistContent::MessageReceived(BMessage* message) {
	switch (message->what) {
		case M_PLAYLIST_ON_SELECT: {
			Clear();
			BVolumeRoster volRoster;
			BVolume bootVolume;
			volRoster.GetBootVolume(&bootVolume);

			BQuery query;		
			query.SetVolume(&bootVolume);

			query.PushAttr("name");
			query.PushString("*");
			query.PushOp(B_CONTAINS);

			query.PushAttr("Media:Title");
			query.PushString("*");
			query.PushOp(B_CONTAINS);
			query.PushOp(B_OR);

			query.PushAttr("Audio:Artist");
			query.PushString("*");
			query.PushOp(B_CONTAINS);
			query.PushOp(B_OR);

			query.PushAttr("Audio:Album");
			query.PushString("*");
			query.PushOp(B_CONTAINS);
			query.PushOp(B_OR);

			query.PushAttr("BEOS:TYPE");
			query.PushString("audio/");
			query.PushOp(B_BEGINS_WITH);
			query.PushOp(B_AND);
	
			if (query.Fetch() == B_OK) {
				entry_ref ref;
				while (query.GetNextRef(&ref) == B_OK) {
					BRow* row = new BRow();
					AddRow(row);
					row->SetField(new BStringField(ref.name), 0);		
				}
			}
		}
		default: {
			BColumnListView::MessageReceived(message);
		}break;
	}	
}
