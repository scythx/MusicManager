#ifndef MediaPlayerPlaylist_H
#define MediaPlayerPlaylist_H

#include <ColumnListView.h>

//class PlaylistContent;

class MediaPlayerPlaylist : public BColumnListView {
public:
	static void Initialize();
	static void Exit();
	static BColumnListView* GetPlaylistContent();

	static BColumnListView* view;
private:
	MediaPlayerPlaylist();
	~MediaPlayerPlaylist();
	
	virtual void MessageReceived(BMessage*);
};

#endif // MediaPlayerPlaylist_H
