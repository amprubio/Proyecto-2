﻿#include "Training.h"
#include "Entity.h"
#include "PlayerController.h"
#include "RenderImage.h"
#include "Jump.h"
#include "SacoTimer.h"

Training::Training(App* app) : GameState(app)
{
	init();
}

void Training::init()
{
	world = new b2World(b2Vec2(0.0, 9.81));//inicializamos el mundo para las f�sicas de b2D
	//---------Debuggear hitbox-------------------------------------------
	debugInstance = new SDLDebugDraw(app_->getRenderer());
	world->SetDebugDraw(debugInstance);
	debugInstance->SetFlags(b2Draw::e_aabbBit);
	//---------------------------------------------------------------
	string filePath = "../../../../assets/Assets/personaje.png";
	Texture* tex = new Texture(app_->getRenderer(), filePath.c_str(), 1, 1);

	Entity* e = new Entity(); // Until we have factories
	e->setApp(app_);
	e->addComponent<PhysicsTransform>(Vector2D(10, 10), Vector2D(10, 10), 50, 50, 0, world);
	e->addComponent<PlayerController>();
	e->addComponent<RenderImage>(tex);
	e->addComponent<Jump>(-1000);
	scene.push_back(e);

	Entity* saco = new Entity();
	saco->addComponent<PhysicsTransform>(Vector2D(250, 10), Vector2D(10, 10), 35, 100, 0, world);
	saco->addComponent<RenderImage>(tex);
	saco->addComponent<SacoTimer>(5000);
	scene.push_back(saco);

	Entity* floor = new Entity();
	floor->addComponent<PhysicsTransform>(Vector2D(100, 600), Vector2D(0, 0), 1000, 100, 0, world, false);
	floor->addComponent<RenderImage>(tex);
	scene.push_back(floor);

}

void Training::update()
{
	GameState::update();

	world->Step(1.0 / 30, 8, 3);//update box2d

}

void Training::render() {
	SDL_RenderClear(app_->getRenderer());
	GameState::render();
	world->DrawDebugData();
	SDL_RenderPresent(app_->getRenderer());
}

Training::~Training()
{
	delete world;
	delete debugInstance;
}