/*
 * Copyright 2017 Raefaldhi Amartya Junior <raefaldhiamartya@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
 
#ifndef PlayButton_H
#define PlayButton_H

#include <Bitmap.h>
#include <Button.h>
#include <MediaFile.h>
#include <MediaTrack.h>
#include <Sound.h>
#include <SoundPlayer.h>

enum {
	M_PLAYBUTTON_ON_PRESSED = 'pbop'
};

class PlayButton : public BButton {
public:
	PlayButton();
	~PlayButton();

	static void ProcBuffer(void*, void*, size_t, const media_raw_audio_format&);

	virtual void AttachedToWindow();
	virtual void Draw(BRect);
	virtual void MessageReceived(BMessage*);
private:
	bool playing;

	BBitmap* playback_start_enabled;
	BBitmap* playback_start_disabled;

	BMediaFile* file;
	BMediaTrack* track;
	BSoundPlayer* soundplayer;
};

#endif // PlayButton_H
