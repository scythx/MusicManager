#include "MediaPlayerPlaylist.h"

#include <fs_attr.h>
#include <Node.h>
#include <String.h>
#include <ColumnTypes.h>
#include <ColumnListView.h>
#include <Query.h>
#include <Volume.h>
#include <VolumeRoster.h>

BColumnListView* MediaPlayerPlaylist::view = NULL;

MediaPlayerPlaylist::MediaPlayerPlaylist() 
					: BColumnListView("PlaylistView", B_FANCY_BORDER) {
	AddColumn(new BStringColumn("Title", 50, 50, 300,B_TRUNCATE_END), 0);
//	AddColumn(new BStringColumn("Ratings", 50, 50, 300,B_TRUNCATE_END), 1);
}

MediaPlayerPlaylist::~MediaPlayerPlaylist() {

}

void MediaPlayerPlaylist::Initialize() {
	if (view != NULL) {
		delete view;
	}
	view = new MediaPlayerPlaylist();
}

void MediaPlayerPlaylist::Exit() {
//	delete view;
//	view = NULL;
}

BColumnListView* MediaPlayerPlaylist::GetPlaylistContent() {
	return view;
}

void MediaPlayerPlaylist::MessageReceived(BMessage* msg) {
	switch (msg->what) {
		case 'aaaa': {
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
			BColumnListView::MessageReceived(msg);
		}break;
	}
}
