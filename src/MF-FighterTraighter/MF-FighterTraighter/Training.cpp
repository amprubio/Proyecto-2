﻿#include "Training.h"
#include "Entity.h"
#include "PlayerController.h"
#include "RenderImage.h"
#include "Jump.h"
#include "PauseMenu.h"
#include "Crouch.h"
#include "SacoTimer.h"
#include "FactoryMk.h"
#include "PunchingBagOnHit.h"
#include "FloorOnHit.h"
#include "UITransform.h"
#include "UITimer.h"
#include "UIHealthbar.h"
Training::Training(App* app) : GameState(app)
{
	init();
}

void Training::init()
{
	FactoryMk::addMkToGame(app_, this, 1, { SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT, SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_Q, SDL_SCANCODE_E, SDL_SCANCODE_Z, SDL_SCANCODE_X,
		SDL_SCANCODE_SPACE, SDL_SCANCODE_R, SDL_SCANCODE_1, SDL_SCANCODE_2 }, PLAYER_1, PLAYER_2 | BOUNDARY | P_BAG, true, 0);
	FactoryMk::addMkToGame(app_, this, -1, { SDL_SCANCODE_J, SDL_SCANCODE_L, SDL_SCANCODE_I, SDL_SCANCODE_K, SDL_SCANCODE_U, SDL_SCANCODE_O, SDL_SCANCODE_N, SDL_SCANCODE_M,
		SDL_SCANCODE_0, SDL_SCANCODE_H, SDL_SCANCODE_8, SDL_SCANCODE_9 }, PLAYER_2, PLAYER_1 | WALLS | BOUNDARY, true, 1);

	Entity* saco = entManager_.addEntity();
	PhysicsTransform* pBpT = saco->addComponent<PhysicsTransform>(Vector2D(app_->getWindowManager()->getCurResolution().w / 2, app_->getWindowManager()->getCurResolution().h - 455), Vector2D(10, 10), 150, 500, 0, P_BAG, PLAYER_1 | PLAYER_2, false);
	addHurtbox(pBpT->getMainFixture());
	saco->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(AssetsManager::Player));
	saco->addComponent<PunchingBagOnHit>();
	Health* sacoHealth = saco->addComponent<Health>(200);
	//saco->addComponent<SacoTimer>(5000);

	Entity* timer = entManager_.addEntity();
	timer->addComponent<UITransform>(Vector2D(0, 120), Vector2D(app_->getWindowManager()->getCurResolution().w / 2, 0), Vector2D(200, 50), Vector2D(400, 100));
	timer->addComponent<TextComponent>("0000", app_->getAssetsManager()->getFont(AssetsManager::Roboto_Black), 45, TextComponent::Center);
	timer->addComponent<UITimer>(UITimer::Minutes);

	Entity* healthbarBack = entManager_.addEntity();
	healthbarBack->addComponent<UITransform>(Vector2D(0, 40), Vector2D(app_->getWindowManager()->getCurResolution().w / 2, 0), Vector2D(850, 20), Vector2D(1700, 40));
	healthbarBack->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(AssetsManager::HealthbarBack));

	Entity* healthbarL = entManager_.addEntity();
	healthbarL->addComponent<UITransform>(Vector2D(0, 40), Vector2D(app_->getWindowManager()->getCurResolution().w / 2, 0), Vector2D(0, 20), Vector2D(850, 40));
	healthbarL->addComponent<UIHealthbar>(sacoHealth, app_->getAssetsManager()->getTexture(AssetsManager::HealthbarSaco));
	Entity* healthbarR = entManager_.addEntity();
	healthbarR->addComponent<UITransform>(Vector2D(0, 40), Vector2D(app_->getWindowManager()->getCurResolution().w / 2, 0), Vector2D(850, 20), Vector2D(850, 40));
	healthbarR->addComponent<UIHealthbar>(sacoHealth, app_->getAssetsManager()->getTexture(AssetsManager::HealthbarSaco), true);

	Entity* character1 = entManager_.addEntity();
	character1->addComponent<UITransform>(Vector2D(100, 70), Vector2D(), Vector2D(70, 70), Vector2D(140, 140));
	character1->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(AssetsManager::CharacterSelection))->setFrame(2, 0);
	Entity* character2 = entManager_.addEntity();
	character2->addComponent<UITransform>(Vector2D(-100, 70), Vector2D(app_->getWindowManager()->getCurResolution().w, 0), Vector2D(70, 70), Vector2D(140, 140));
	character2->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(AssetsManager::CharacterSelection))->setFrame(2, 0);

	Entity* floor = entManager_.addEntity();
	PhysicsTransform* FpT = floor->addComponent<PhysicsTransform>(Vector2D(960, 1100), Vector2D(0, 0), 1920, 450, 0, BOUNDARY, EVERYTHING, false);
	floor->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(AssetsManager::Player));
	//floor->addComponent<FloorOnHit>();

	//Walls
	Entity* wall1 = entManager_.addEntity();
	PhysicsTransform* W1pT = wall1->addComponent<PhysicsTransform>(Vector2D(-50, 540), Vector2D(0, 0), 100, 1080, 0, WALLS, EVERYTHING, false);

	Entity* wall2 = entManager_.addEntity();
	PhysicsTransform* W2pT = wall2->addComponent<PhysicsTransform>(Vector2D(1970, 540), Vector2D(0, 0), 100, 1080, 0, WALLS, EVERYTHING, false);
}

void Training::handleInput()
{
	if (app_->getInputManager()->pressedStart()) {
		app_->getGameManager()->pressedStart();
	}
	GameState::handleInput();
}

Training::~Training()
{
}