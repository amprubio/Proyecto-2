#pragma once
#include "GameState.h"
#include "Texture.h"

/// C A L L B A C K S ///

void GoBackCallback(App* app);
void MovementsCallback(App* app);
void MenuCallback(App* app);
void OptionsCallback(App* app);

//brightness
void moreBright(App* app);
void lessBright(App* app);

//SFXVolume
void moreSFXVolume(App* app);
void lessSFXVolume(App* app);

//fullscreen
void fullScreen(App* app);

void MenuCallback(App* app);


class OptionsMenu:public GameState
{
public:
	OptionsMenu(App* app);
	virtual ~OptionsMenu();

	void init() override;
	virtual void update() override;
	virtual void render() override;
	void handleInput();

private:
	float current_volume = 0;
	float current_bright = 0;


};

