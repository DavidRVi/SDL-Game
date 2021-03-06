#include "ModuleAudio.h"
#include "SDL/include/SDL.h"

#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

ModuleAudio::ModuleAudio() {
	sound_effect = NULL;
	background = NULL;
	channel = -1;
}

ModuleAudio::~ModuleAudio() {
	Mix_Quit();
}

bool ModuleAudio::Init() {
	LOG("Init SDL audio & mixer");
	bool ret = true;

	if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		LOG("SDL_AUDIO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	int audio_rate = 22050;
	Uint16 audio_format = AUDIO_S16SYS;
	int audio_channels = 2;
	int audio_buffers = 4096;

	int flags = MIX_INIT_OGG;
	if (Mix_Init(flags)&flags != flags)
	{
		LOG("MIX_INIT fail.", Mix_GetError());
		ret = false;
	}
		

	if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) {
		LOG("Unable to initialize audio Mixer: %s\n", Mix_GetError());
		ret = false;
	}

	return ret;
}

bool ModuleAudio::Start() {
	LOG("Loading OGG file for background music")
	bool ret = true;

	background = Mix_LoadMUS(BACKGROUND_MUSIC);
	if (background == NULL)
	{
		LOG("ERROR LOADING OGG MUSIC: %s\n", Mix_GetError());
		ret = false;
	}

	sound_effect = Mix_LoadWAV(SOUND_EFFECT);
	if (sound_effect == NULL)
	{
		LOG("ERROR LOADING WAV MUSIC: %s\n", Mix_GetError());
		ret = false;
	}

	ret = PlayBackgroundMusic();

	return ret;
}

update_status ModuleAudio::Update() {
	return UPDATE_CONTINUE;
}

bool ModuleAudio::CleanUp() {
	Mix_HaltMusic();
	Mix_CloseAudio();
	if (sound_effect != NULL)
		Mix_FreeChunk(sound_effect);
	if (background != NULL)
		Mix_FreeMusic(background);

	SDL_QuitSubSystem(SDL_INIT_AUDIO);

	return true;
}

bool ModuleAudio::PlaySoundEffect() {
	bool ret = true;
	if (!Mix_Playing(channel))
		channel = Mix_PlayChannel(-1, sound_effect, 0);

	if (channel == -1) {
		fprintf(stderr, "Unable to play WAV file: %s\n", Mix_GetError());
		ret = false;
	}

	return ret;
}

bool ModuleAudio::PlayBackgroundMusic() {
	bool ret = true;
	if (Mix_PlayMusic(background, -1) == -1)		// second argument -1 : InfiniteLoop
	{
		LOG("Unable to play Ogg file: %s\n", Mix_GetError());
		ret = false;
	}

	return ret;

}