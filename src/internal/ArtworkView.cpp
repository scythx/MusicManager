/*
 * Copyright 2017 Raefaldhi Amartya Junior <raefaldhiamartya@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#include "ArtworkView.h"

#include <AffineTransform.h>

#include "../Playlist.h"

ArtworkView::ArtworkView() : BView("ArtworkView", B_WILL_DRAW) {
	SetExplicitMinSize(BSize(60, 60));
	SetExplicitMaxSize(BSize(60, 60));

	SetViewColor(255, 255, 255, 0);
}

void ArtworkView::AttachedToWindow() {
}

void ArtworkView::Draw(BRect rect) {
}

void ArtworkView::MessageReceived(BMessage* message) {
	switch (message->what) {
		case 'jkla': {
			if ((Playlist::CurrentContentSelection != NULL) && (Playlist::CurrentContentSelection->Artwork != NULL)) {
				SetViewBitmap(Playlist::CurrentContentSelection->Artwork);
				BAffineTransform transform;
				transform.ScaleBy(BPoint(0, 0), 0.1, 0.1);
				SetTransform(transform);
			}
			else {
				SetViewBitmap(NULL);
			}
		}break;
		default: {
			ArtworkView::MessageReceived(message);
		}break;
	}
}
