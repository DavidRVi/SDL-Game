#ifndef _MODULEAUDIO_H_
#define _MODULEAUDIO_H_
#include<list>
#include "Module.h"
#include "Globals.h"
#include "SDL/include/SDL_mixer.h"


class ModuleAudio : public Module
{
public:
	ModuleAudio();
	~ModuleAudio();

	bool Init();
	bool Start();
	update_status Update();
	bool CleanUp();
	bool PlaySoundEffect();
	bool PlayBackgroundMusic();

private:
	Mix_Music* background;
	Mix_Chunk* sound_effect;
	int channel;
};

#endif