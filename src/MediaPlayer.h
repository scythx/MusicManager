#ifndef MediaPlayer_H
#define MediaPlayer_H

#include <Application.h>

#include "MediaPlayerWindow.h"

class MediaPlayer : public BApplication {
public:
	MediaPlayer();
	~MediaPlayer();
private:
	MediaPlayerWindow* mpWindow;
};

#endif // MediaPlayer_H
