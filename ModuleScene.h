#pragma once
#include "Module.h"
#include "Globals.h"


class ModuleScene : public Module
{
public:
	ModuleScene();
	~ModuleScene();

	bool Init();
	bool Start();
	bool CleanUp();


private:
	
};