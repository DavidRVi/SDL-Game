#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "Application.h"
#include "ModuleAudio.h"

#include "SDL/include/SDL.h"

using namespace std;
ModuleInput::ModuleInput()
{}

// Destructor
ModuleInput::~ModuleInput()
{}

// Called before render is available
bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool ModuleInput::Start()
{
	LOG("MODULO INPUT OK");
	return true;
}

// Called every draw update
update_status ModuleInput::Update()
{
	SDL_PumpEvents();

	keyboard = SDL_GetKeyboardState(NULL);

	// TODO 1: Make the application properly close when ESC is pressed (do not use exit())
	if (keyboard[SDL_SCANCODE_ESCAPE])
	{
		LOG("Closing game with ESC\n");
		return UPDATE_STOP;
	}
	if (keyboard[SDL_SCANCODE_E])
	{
		if (!App->audio->PlaySoundEffect())
			return UPDATE_STOP;
	}
	// Homework: Make the application close up when pressing �X� button of the window
	SDL_Event events;
	while (SDL_PollEvent(&events)) {
		if (events.type == SDL_QUIT)
			return UPDATE_STOP;
	}

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}