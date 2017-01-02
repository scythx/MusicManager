/*
 * Copyright 2016-2017 Raefaldhi Amartya Junior <raefaldhiamartya@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

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
				  	B_DOCUMENT_WINDOW, B_QUIT_ON_WINDOW_CLOSE |
				  	B_AUTO_UPDATE_SIZE_LIMITS) {
	MediaPlayerPlaylist::Initialize();

	BView* mpView = new BView("mpView", B_WILL_DRAW);	

	BButton* refresh = new BButton("refresh", "Refresh", new BMessage(M_PLAYLIST_ON_SELECT));
	BLayoutBuilder::Group<>(mpView, B_HORIZONTAL)
		.SetInsets(10)
		.Add(MediaPlayerPlaylist::GetPlaylist())
		.AddGroup(B_VERTICAL, B_USE_DEFAULT_SPACING, 2)
			.Add(MediaPlayerPlaylist::GetPlaylistContent())
			.AddGrid()
				.AddGlue(0, 0)
				.Add(refresh, 1, 0)
			.End()
		.End()
	.End();
	BLayoutBuilder::Group<>(this, B_VERTICAL, 0.0f)
		.SetInsets(0)
		.Add(mpView)
	.End();
	refresh->SetTarget(MediaPlayerPlaylist::GetPlaylistContent());
}
