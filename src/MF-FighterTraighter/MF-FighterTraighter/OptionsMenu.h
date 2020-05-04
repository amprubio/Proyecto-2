#pragma once
#include "GameState.h"
#include "Texture.h"

class OptionsMenu:public GameState
{
public:
	//constructor
	OptionsMenu(App* app);
	//destructor
	virtual ~OptionsMenu();

	//method overrided from GameState where the objects are created from the different factories
	void init() override;
	void handleInput() override;


	//callbacks of the Entitys
	
	//go to the state that was before
	static void GoBackCallback(App* app);
	
	//go to the controls menu
	static void GoControlsCallback(App* app);

	//change the brightness
	static void SetBright(App* app, double value);
	

	//changes the volume
	static void SetVolume(App* app, double value);

	static void SetSfxVolume(App* app, double value);
	
	//fullscreen
	static void fullScreen(App* app);
	
	//changes the resolution
	static void setResolution(App* app, double value);	
	
	//saves the settings, and applies the resolution
	static void applySettings(App* app);
protected:
	static double curResolution_;
};