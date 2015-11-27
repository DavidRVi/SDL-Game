#pragma once
#include "Module.h"
#include "Globals.h"
#include <list>
#include "SDL/include/SDL.h"

#include "SDL_image/include/SDL_image.h"
#pragma comment( lib, "SDL_image/libx86/SDL2_image.lib" )

class ModuleScene : public Module
{
public:
	ModuleScene();
	~ModuleScene();

	bool Init();
	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();


private:

	// Contains references to the loaded textures so we can easily access them and draw them later
	std::list<SDL_Texture*> textures;

	// Contains texture paths that we're going to use in the scene
	std::list<std::string*> texturePaths;

	bool DrawTextures() const;
};