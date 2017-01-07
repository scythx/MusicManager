/*
 * Copyright 2017 Raefaldhi Amartya Junior <raefaldhiamartya@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
 
#ifndef ArtworkView_H
#define ArtworkView_H

#include <View.h>

class ArtworkView : public BView {
public:
	ArtworkView();

	virtual void AttachedToWindow();
	virtual void Draw(BRect);
	virtual void MessageReceived(BMessage*);
};

#endif // ArtworkView_H
