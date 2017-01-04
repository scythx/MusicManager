/*
 * Copyright 2017 Raefaldhi Amartya Junior <raefaldhiamartya@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#ifndef LibraryRow_H
#define LibraryRow_H

#include <ColumnTypes.h>
#include <ColumnListView.h>
#include <Entry.h>

class PlaylistContentRow : public BRow {
public:
	PlaylistContentRow(entry_ref);
private:
	entry_ref ref;
};

#endif // LibraryRow_H
