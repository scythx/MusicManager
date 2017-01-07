/*
 * Copyright 2017 Raefaldhi Amartya Junior <raefaldhiamartya@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#include "Control.h"

#include "internal/ArtworkView.h"
#include "internal/ControlBox.h"
#include "internal/PlayButton.h"

#include <Bitmap.h>
#include <LayoutBuilder.h>

BView* Control::_ArtworkView = NULL;
BView* Control::_ControlBox = NULL;
BButton* Control::_PictureButton = NULL;

Control::Control() {

}

void Control::Init() {
	_ArtworkView = new ArtworkView();
	_ControlBox = new ControlBox();
	_PictureButton = new PlayButton();

	BLayoutBuilder::Grid<>(_ControlBox)
		.SetInsets(0)
		.AddGlue(0, 0)
		.Add(_ArtworkView, 1, 0)
		.Add(_PictureButton, 2, 0)
		.AddGlue(3, 0)
	.End();
}

BView* Control::GetControlBox() {
	return _ControlBox;
}
