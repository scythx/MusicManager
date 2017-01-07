/*
 * Copyright 2017 Raefaldhi Amartya Junior <raefaldhiamartya@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#ifndef LibraryRow_H
#define LibraryRow_H

#include <String.h>

#include <Bitmap.h>
#include <ColumnTypes.h>
#include <ColumnListView.h>
#include <Entry.h>

class PlaylistContentRow : public BRow {
public:
	PlaylistContentRow(entry_ref);

	entry_ref ref;
	BString release_id;
	BBitmap* Artwork;
private:
};

#endif // LibraryRow_H
