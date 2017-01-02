#include "MediaPlayerWindow.h"

#include <Button.h>
#include <MenuBar.h>
#include <SplitView.h>
#include <StringView.h>
#include <View.h>
#include <LayoutBuilder.h>
#include <GroupLayout.h>
#include <SpaceLayoutItem.h>

#include "MediaPlayerPlaylist.h"

MediaPlayerWindow::MediaPlayerWindow()
				  : BWindow(BRect(100, 100, 400, 400), "Media Player",
				  	B_DOCUMENT_WINDOW, B_QUIT_ON_WINDOW_CLOSE) {
	MediaPlayerPlaylist::Initialize();

	BView* mpView = new BView("mpView", B_WILL_DRAW);	

	BButton* refresh = new BButton("refresh", "Refresh", new BMessage('aaaa'));
	BLayoutBuilder::Group<>(mpView, B_VERTICAL)
		.SetInsets(0)
		.Add(MediaPlayerPlaylist::GetPlaylistContent())
		.Add(refresh)
	.End();
	BLayoutBuilder::Group<>(this, B_VERTICAL, 0.0f)
		.SetInsets(0)
		.Add(mpView)
	.End();
	refresh->SetTarget(MediaPlayerPlaylist::GetPlaylistContent());
}

MediaPlayerWindow::~MediaPlayerWindow() {
	MediaPlayerPlaylist::Exit();		
}
