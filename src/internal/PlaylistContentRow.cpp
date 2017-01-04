/*
 * Copyright 2017 Raefaldhi Amartya Junior <raefaldhiamartya@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#include "PlaylistContentRow.h"

#include <String.h>
#include <SimpleGameSound.h>
#include <fs_attr.h>
#include <Node.h>

PlaylistContentRow::PlaylistContentRow(entry_ref _ref)
		   : BRow() {
	ref = _ref;
	BNode node(&ref);

	BString attr;
	attr_info attrInfo;
	char* buffer;

	if (node.GetAttrInfo("Media:Title", &attrInfo) == B_OK) {
			buffer = attr.LockBuffer(attrInfo.size + 1);
			node.ReadAttr("Media:Title", attrInfo.type, 0, buffer, attrInfo.size);
			buffer[attrInfo.size] = '\0';
			attr.UnlockBuffer();

			SetField(new BStringField(attr), 0);
	}
	else {
		SetField(new BStringField(ref.name), 0);
	}

	if (node.GetAttrInfo("Audio:Artist", &attrInfo) == B_OK) {
		buffer = attr.LockBuffer(attrInfo.size + 1);
		node.ReadAttr("Audio:Artist", attrInfo.type, 0, buffer, attrInfo.size);
		buffer[attrInfo.size] = '\0';
		attr.UnlockBuffer();

		SetField(new BStringField(attr), 1);
	}

	if (node.GetAttrInfo("Audio:Album", &attrInfo) == B_OK) {
		buffer = attr.LockBuffer(attrInfo.size + 1);
		node.ReadAttr("Audio:Album", attrInfo.type, 0, buffer, attrInfo.size);
		buffer[attrInfo.size] = '\0';
		attr.UnlockBuffer();

		SetField(new BStringField(attr), 2);
	}

	if (node.GetAttrInfo("Media:Genre", &attrInfo) == B_OK) {
		buffer = attr.LockBuffer(attrInfo.size + 1);
		node.ReadAttr("Media:Genre", attrInfo.type, 0, buffer, attrInfo.size);
		buffer[attrInfo.size] = '\0';
		attr.UnlockBuffer();

		SetField(new BStringField(attr), 3);
	}

	if (node.GetAttrInfo("Media:Year", &attrInfo) == B_OK) {
		buffer = attr.LockBuffer(attrInfo.size + 1);
		node.ReadAttr("Media:Year", attrInfo.type, 0, buffer, attrInfo.size);
		buffer[attrInfo.size] = '\0';
		attr.UnlockBuffer();

		SetField(new BStringField(attr), 4);
	}
}
