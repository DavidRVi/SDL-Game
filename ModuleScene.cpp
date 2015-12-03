#pragma once
#include "ModuleScene.h"
#include "ModuleRender.h"
#include "moduleTextures.h"
#include "Application.h"
#include <string>

using namespace std;

ModuleScene::ModuleScene() {

}

ModuleScene::~ModuleScene() {
	//for (list<string*>::iterator it = texturePaths.begin(); it != texturePaths.end(); ++it)
	//	delete *it;

	//texturePaths.clear();
	//textures.clear();
}

bool ModuleScene::Init() {
	texturePaths.push_back(new std::string("sprites.png"));
	return true;
}

bool ModuleScene::Start() {
	bool ret = true;
	for (list<string*>::iterator it = texturePaths.begin(); it != texturePaths.end() && ret; ++it)
	{
		SDL_Texture* texture = App->textures->Load((*it)->c_str());
		if (texture)
		{
			textures.push_back(texture);
		}
		else ret = false;
		delete *it;	// free memory from texturePaths list, the texture is already loaded and we don't need its path anymore.
	}

	texturePaths.clear();	// Destroy texturePaths list because we won't need it anymore.

	return ret;
}

update_status ModuleScene::PreUpdate() {
	return UPDATE_CONTINUE;
}

update_status ModuleScene::Update() {
	update_status status = UPDATE_CONTINUE;

	if (DrawTextures() == false)
	{
		status = UPDATE_ERROR;
		LOG("Error Drawing Textures");
	}
	
	return status;
}

update_status ModuleScene::PostUpdate() {
	return UPDATE_CONTINUE;
}

bool ModuleScene::CleanUp() {
	textures.clear();
	return true;
}

bool ModuleScene::DrawTextures() const {
	bool ret = true;
	for (std::list<SDL_Texture*>::const_iterator it = textures.begin(); it != textures.end() && ret; ++it)
	{
		if (!App->renderer->Blit(*(it), 0, 0, NULL))
			ret = false;
	}

	return ret;
}