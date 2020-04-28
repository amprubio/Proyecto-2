#include "Fight.h"
#include "FloorOnHit.h"
#include "UITimer.h"
#include "UITransform.h"
#include "UIFactory.h"
#include "Health.h"
#include "UIHealthbar.h"
#include "UIRoundRenderer.h"
#include "AbilityFactory.h"
#include "RenderAnimation.h"
#include "Bullet.h"

Fight::Fight(App* app) : GameState(app)
{
	init();
}

void Fight::init()
{
	GameState::init();
	doStep = true;
	Entity* bg = entManager_.addEntity();
	bg->addComponent<Transform>(Vector2D(), Vector2D(), app_->getWindowManager()->getCurResolution().w, app_->getWindowManager()->getCurResolution().h, 0);
	bg->addComponent<RenderAnimation>(app_->getAssetsManager()->getTexture(AssetsManager::BackgroundFight), 20);

	//Floor
	Entity* floor = entManager_.addEntity();
	PhysicsTransform* FpT = floor->addComponent<PhysicsTransform>(Vector2D(960, 1200), Vector2D(0, 0), 1920, 450, 0, world, BOUNDARY, EVERYTHING, 2);
	/*floor->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(AssetsManager::Player));*/
	//floor->addComponent<FloorOnHit>();

	//Walls
	Entity* wall1 = entManager_.addEntity();
	PhysicsTransform* W1pT = wall1->addComponent<PhysicsTransform>(Vector2D(-50, 540), Vector2D(0, 0), 100, 1080, 0, world, WALLS, EVERYTHING, 2);

	Entity* wall2 = entManager_.addEntity();
	PhysicsTransform* W2pT = wall2->addComponent<PhysicsTransform>(Vector2D(1970, 540), Vector2D(0, 0), 100, 1080, 0, world, WALLS, EVERYTHING, 2);
	/*Entity* bullet = entManager_.addEntity();// = entManager_.addEntity();
	//PhysicsTransform* pT = e->addComponent<PhysicsTransform>(Vector2D(-orientation * 100 + 960, 600), Vector2D(0, 0), 500, 500, 0, world, cBits, mBits, dyn);
	//bullet->setApp(app_);
	bullet->addComponent<PhysicsTransform>(Vector2D(100, 300), Vector2D(0, 0), 500, 500, 0, world, BULLET, PLAYER_2,1);
	bullet->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(AssetsManager::Player));
	//uint16 playerNumber,Vector2D speed, int damage, int hitstun, Vector2D knockBack, int time
	bullet->addComponent<Bullet>(this,0, Vector2D(5000, 0), 10,0,Vector2D(50,50),1000,false);*/
	//Player 1
	Entity* player1 = FactoryMk::addMkToGame(app_, this, 1, { SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT, SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_Q, SDL_SCANCODE_E, SDL_SCANCODE_Z, SDL_SCANCODE_X,
		SDL_SCANCODE_1, SDL_SCANCODE_2, SDL_SCANCODE_SPACE, SDL_SCANCODE_R }, world, false, PLAYER_1, PLAYER_2 | WALLS | BOUNDARY | BULLET, 0);
	//Entity* player1 = FactoryMk::addMkToGame(app_, this, 1, { SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT, SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_Q, SDL_SCANCODE_E, SDL_SCANCODE_Z, SDL_SCANCODE_X, 
	//	SDL_SCANCODE_1, SDL_SCANCODE_2, SDL_SCANCODE_SPACE, SDL_SCANCODE_R }, world, false, PLAYER_1, PLAYER_2 | WALLS | BOUNDARY | BULLET, 0);
	player1->getComponent<PlayerAttacks>(ecs::PlayerAttacks)->setAbility(AbilityFactory::GiveMegatonGrip(player1), 0);
	player1->getComponent<PlayerAttacks>(ecs::PlayerAttacks)->setAbility(AbilityFactory::SeismicShock(player1), 1);
	vector<std::string>abilitiesP1;
	abilitiesP1.push_back("MegatonGrip");
	abilitiesP1.push_back("SeismicShock");
	app_->getGameManager()->setPlayerInfo1(player1, "MKWHOOP", abilitiesP1, 0, 1);

	//player1->addComponent
	//Player 2
	Entity* player2 = FactoryMk::addMkToGame(app_, this, -1, { SDL_SCANCODE_J, SDL_SCANCODE_L, SDL_SCANCODE_I, SDL_SCANCODE_K, SDL_SCANCODE_U, SDL_SCANCODE_O, SDL_SCANCODE_N, SDL_SCANCODE_M,
		SDL_SCANCODE_0, SDL_SCANCODE_H, SDL_SCANCODE_8, SDL_SCANCODE_9 }, world, true, PLAYER_2, PLAYER_1 | WALLS | BOUNDARY | BULLET, 1);
	player2->getComponent<PlayerAttacks>(ecs::PlayerAttacks)->setAbility(AbilityFactory::GiveMegatonGrip(player2), 1);
	vector<std::string>abilitiesP2;
	//abilities.push_back("MegatonGrip");
	//abilities.push_back("SeismicShock");
	app_->getGameManager()->setPlayerInfo2(player2, "MKWHOOP", abilitiesP2, -1, -1);
	Entity* timer = entManager_.addEntity();
	timer->addComponent<UITransform>(Vector2D(0, 75), Vector2D(app_->getWindowManager()->getCurResolution().w / 2, 0), Vector2D(200, 50), Vector2D(400, 100));
	timer->addComponent<TextComponent>("0000", app_->getAssetsManager()->getFont(AssetsManager::Roboto_Black), 45, TextComponent::Center);
	timer->addComponent<UITimer>(UITimer::Minutes);

	Entity* healthbarBack1 = entManager_.addEntity();
	healthbarBack1->addComponent<UITransform>(Vector2D(460, 50), Vector2D(0, 0), Vector2D(365, 20), Vector2D(730, 40));
	healthbarBack1->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(AssetsManager::HealthbarBack));
	Entity* healthbar1 = entManager_.addEntity();
	healthbar1->addComponent<UITransform>(Vector2D(460, 50), Vector2D(0, 0), Vector2D(365, 20), Vector2D(730, 40));
	healthbar1->addComponent<UIHealthbar>(player1->getComponent<Health>(ecs::Health), app_->getAssetsManager()->getTexture(AssetsManager::Healthbar), true);
	Entity* character1 = entManager_.addEntity();
	character1->addComponent<UITransform>(Vector2D(70, 70), Vector2D(), Vector2D(70, 70), Vector2D(140, 140));
	character1->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(AssetsManager::CharacterSelection))->setFrame(2, 0);

	Entity* healthbarBack2 = entManager_.addEntity();
	healthbarBack2->addComponent<UITransform>(Vector2D(-460, 50), Vector2D(app_->getWindowManager()->getCurResolution().w, 0), Vector2D(365, 20), Vector2D(730, 40));
	healthbarBack2->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(AssetsManager::HealthbarBack));
	Entity* healthbar2 = entManager_.addEntity();
	healthbar2->addComponent<UITransform>(Vector2D(-460, 50), Vector2D(app_->getWindowManager()->getCurResolution().w, 0), Vector2D(365, 20), Vector2D(730, 40));
	healthbar2->addComponent<UIHealthbar>(player2->getComponent<Health>(ecs::Health), app_->getAssetsManager()->getTexture(AssetsManager::Healthbar));
	Entity* character2 = entManager_.addEntity();
	character2->addComponent<UITransform>(Vector2D(-70, 70), Vector2D(app_->getWindowManager()->getCurResolution().w, 0), Vector2D(70, 70), Vector2D(140, 140));
	character2->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(AssetsManager::CharacterSelection))->setFrame(2, 0);

	std::vector<Entity*> leftCounter;
	std::vector<Entity*> rightCounter;
	// Make a factory or something
	for (int i = 0; i < 3; ++i) {
		Entity* roundCounter1 = entManager_.addEntity();
		roundCounter1->addComponent<UITransform>(Vector2D(-173 - i * 40, 93), Vector2D(app_->getWindowManager()->getCurResolution().w / 2, 0), Vector2D(18, 18), Vector2D(36, 36));
		roundCounter1->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(AssetsManager::RoundCounter));
		leftCounter.push_back(roundCounter1);
		Entity* roundCounter2 = entManager_.addEntity();
		roundCounter2->addComponent<UITransform>(Vector2D(173 + i * 40, 93), Vector2D(app_->getWindowManager()->getCurResolution().w / 2, 0), Vector2D(18, 18), Vector2D(36, 36));
		roundCounter2->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(AssetsManager::RoundCounter));
		rightCounter.push_back(roundCounter2);
	}
	// Should be like a manager, or something
	Entity* gameController = entManager_.addEntity();
	gameController->addComponent<UIRoundRenderer>(leftCounter)->setRoundsWon(3);
	gameController->addComponent<UIRoundRenderer>(rightCounter);

	//app_->getGameManager().
}

void Fight::handleInput()
{
	if (app_->getInputManager()->pressedStart()) {
		app_->getGameManager()->pressedStart();
	}
	else
		GameState::handleInput();
}
Fight::~Fight()
{
}
