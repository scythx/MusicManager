/*
 * Copyright 2017 Raefaldhi Amartya Junior <raefaldhiamartya@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
 
#ifndef Control_H
#define Control_H

#include <Button.h>
#include <View.h>

class Control {
public:
	static void Init();
	static BView* GetControlBox();
	static BView* _ArtworkView;
	static BView* _ControlBox;
	static BButton* _PictureButton;
	
	static void SetArtWork();
private:
	Control();
};

#endif // Control_H
