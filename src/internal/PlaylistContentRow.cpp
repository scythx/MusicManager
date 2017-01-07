/*
 * Copyright 2017 Raefaldhi Amartya Junior <raefaldhiamartya@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#include "PlaylistContentRow.h"

#include <String.h>
#include <Path.h>
#include <TranslationUtils.h>
#include <musicbrainz5/Metadata.h>
#include <musicbrainz5/Query.h>
#include <musicbrainz5/Release.h>
#include <taglib/tag.h>
#include <taglib/fileref.h>
#include <taglib/mpegfile.h>
#include <taglib/id3v2tag.h>
#include <taglib/id3v2frame.h>
#include <taglib/id3v2header.h>
#include <taglib/attachedpictureframe.h>


PlaylistContentRow::PlaylistContentRow(entry_ref _ref)
		   : BRow() {
	Artwork = NULL;
	ref = _ref;

	BPath path(&ref);
	TagLib::FileRef taglib_file(path.Path());

	BString query_string;
		
	if (taglib_file.tag()->track()) {
		SetField(new BIntegerField(taglib_file.tag()->track()), 0);
	}
	else {
		SetField(new BIntegerField(0), 0);
	}
	if (taglib_file.tag()->title().isNull()) {
		SetField(new BStringField(ref.name), 1);	
		query_string << "title:\"" << ref.name << "\" AND ";
	}
	else {
		SetField(new BStringField(taglib_file.tag()->title().toCString(true)), 1);
		query_string << "title:\"" << taglib_file.tag()->title().toCString(true) << "\" AND ";
	}
	if (taglib_file.tag()->artist().isNull()) {
		SetField(new BStringField(""), 2);
	}
	else {
		SetField(new BStringField(taglib_file.tag()->artist().toCString(true)), 2);
		query_string << "artist:\"" << taglib_file.tag()->artist().toCString(true) << "\" AND ";		
	}
	if (taglib_file.tag()->album().isNull()) {
		SetField(new BStringField(""), 3);
	}
	else {
		SetField(new BStringField(taglib_file.tag()->album().toCString(true)), 3);
		query_string << "album:\"" << taglib_file.tag()->artist().toCString(true) << "\" AND ";			
	}
	SetField(new BStringField((taglib_file.tag()->genre().isNull()) ? ("") : (taglib_file.tag()->genre().toCString(true))), 4);
	if (taglib_file.tag()->year()) {
		SetField(new BIntegerField(taglib_file.tag()->year()), 5);
	}
	else {
		SetField(new BIntegerField(0), 5);
	}
	SetField(new BStringField((taglib_file.tag()->comment().isNull()) ? ("") : (taglib_file.tag()->comment().toCString(true))), 6);

//  Get the coverart
	TagLib::MPEG::File MPEGfile(path.Path());
	TagLib::ID3v2::Tag* MPEGtags = MPEGfile.ID3v2Tag();
	TagLib::ID3v2::FrameList MPEGframes = MPEGtags->frameList("APIC");
	if (!MPEGframes.isEmpty()) {
		TagLib::ID3v2::AttachedPictureFrame* MPEGframe = static_cast<TagLib::ID3v2::AttachedPictureFrame*>(MPEGframes.front());
		if (!MPEGframe->picture().isEmpty()) {
			BMallocIO* mallocIO = new BMallocIO();
			mallocIO->WriteAt(0, MPEGframe->picture().data(), MPEGframe->picture().size());
			Artwork = BTranslationUtils::GetBitmap(mallocIO);
			delete mallocIO;
		}
	}

	MusicBrainz5::CQuery query("MusicManager for Haiku - github.com/raefaldhia/MusicManager");
	try {
		MusicBrainz5::CQuery::tParamMap params;

		query_string.Truncate(query_string.Length() - 5);
		params["query"] = query_string.String();
		params["limit"] = "1";

		MusicBrainz5::CMetadata metadata = query.Query("release", "", "", params);
		MusicBrainz5::CRelease* result = metadata.Release();
		if (result != NULL) {
			release_id = result->ID().c_str();
		}
		else {
			release_id = "";
		}
	}
	catch (...) {
		//TODO: Handle exception.
	}
}
