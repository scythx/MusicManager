/*
 * Copyright 2017 Raefaldhi Amartya Junior <raefaldhiamartya@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#include "PlayButton.h"

#include <Bitmap.h>
#include <TranslationUtils.h>

#include "../Playlist.h"

PlayButton::PlayButton() : BButton("", new BMessage(M_PLAYBUTTON_ON_PRESSED)) {
	playing = false;
	
	SetExplicitMinSize(BSize(20, 20));
	SetExplicitMaxSize(BSize(20, 20));
		
	playback_start_enabled = BTranslationUtils::GetBitmap('VICN', "playback_start_enabled");
	playback_start_disabled = BTranslationUtils::GetBitmap('VICN', "playback_start_disabled");
}

PlayButton::~PlayButton() {
	if (soundplayer) {
		soundplayer->Stop();
		delete soundplayer;
		soundplayer = NULL;
		delete file;
	}
}

void PlayButton::ProcBuffer(void* cookie, void* buffer, size_t size, const media_raw_audio_format& format) {
	int64 frameCount;
	
	((BMediaTrack*)cookie)->ReadFrames(buffer, &frameCount);
}

void PlayButton::AttachedToWindow() {
	SetTarget(this);
}

void PlayButton::Draw(BRect rect) {
	if (playing) {
		SetViewBitmap(playback_start_enabled);
	}
	else {
		SetViewBitmap(playback_start_disabled);
	}
}

void PlayButton::MessageReceived(BMessage* message) {
	switch (message->what) {
		case M_PLAYBUTTON_ON_PRESSED: {
			if (playing) {
				if (soundplayer) {
					soundplayer->Stop();
					delete soundplayer;
					soundplayer = NULL;
					delete file;
				}
			}
			else {
				media_format format;
				file = new BMediaFile(&Playlist::CurrentContentSelection->ref);
				if (file->InitCheck() == B_OK) {
					for (int i = 0; i < file->CountTracks(); i++) {
						track = file->TrackAt(i);
						if ((track->DecodedFormat(&format) == B_OK) && (format.type == B_MEDIA_RAW_AUDIO)) {
							break;
						}
						if (track) {
							file->ReleaseTrack(track);
						}		
					}					
					soundplayer = new BSoundPlayer(&format.u.raw_audio, Playlist::CurrentContentSelection->ref.name, PlayButton::ProcBuffer, NULL, (void*)track);
					soundplayer->SetVolume(1.0f);
					soundplayer->SetHasData(true);
					soundplayer->Start();
				}
				else {
					return;
				}
			}
			playing = !playing;
		}
		default: {
			BButton::MessageReceived(message);
		}
	}
}
