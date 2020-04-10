#include "MainMenu.h"
#include "Fight.h"
#include "OptionsMenu.h"
#include "Training.h"

#include "InputManager.h"

#include "Entity.h"

#include "RenderImage.h"
#include "Transform.h"
#include "Button.h"
#include "TextComponent.h"
#include "NavigationController.h"

#include "Font.h"

#include "App.h"
#include "consts.h"
#include "UIFactory.h"

MainMenu::MainMenu(App* app) : GameState(app)
{

	cout << "Menu principal" << endl;
	init();
}

MainMenu::~MainMenu()
{

}

void MainMenu::init()
{

	cout << "init" << endl;

	/*Entity* bg = entManager_.addEntity();
	Transform* t = bg->addComponent<Transform>();
	t->setPosition(0, 0);
	t->setWidthHeight(800, 600);
	RenderImage* img = bg->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(7));*/

	Entity* ent = entManager_.addEntity();
	Transform* transform = ent->addComponent<Transform>();
	transform->setWidthHeight(WIDTH_LOGO, HEIGHT_LOGO);
	transform->setPosition(POS_X_BUTTONS, POS_Y_LOGO);
	RenderImage* img = ent->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(2));


	tuple < Entity*, Entity *> arcade=	UIFactory::createButton(app_, this, app_->getAssetsManager()->getTexture(1), app_->getAssetsManager()->getFont(0), Vector2D(POS_X_BUTTONS, POS_Y_ARCADE), WIDTH_BUTTON + 40, HEIGHT_BUTTON,0, nullptr,GoArcade,"Arcade",150);
	tuple < Entity*, Entity *> pvp=	UIFactory::createButton(app_, this, app_->getAssetsManager()->getTexture(1), app_->getAssetsManager()->getFont(0), Vector2D(POS_X_BUTTONS, POS_Y_PVP), WIDTH_BUTTON - 60, HEIGHT_BUTTON,0, nullptr,Go1v1,"1vs1",150);

	tuple < Entity*, Entity *> options = UIFactory::createButton(app_, this, app_->getAssetsManager()->getTexture(1), app_->getAssetsManager()->getFont(0), Vector2D(POS_X_BUTTONS, POS_Y_OPTIONS), WIDTH_BUTTON + 90, HEIGHT_BUTTON,0, nullptr,GoOptions,"Options",150);
	tuple < Entity*, Entity *> exit = UIFactory::createButton(app_, this, app_->getAssetsManager()->getTexture(1), app_->getAssetsManager()->getFont(0), Vector2D(POS_X_BUTTONS, POS_Y_EXIT), WIDTH_BUTTON - 40, HEIGHT_BUTTON,0, nullptr,Leave,"Quit",150);

	Entity* navEnt = entManager_.addEntity();
	NavigationController* nav = navEnt->addComponent<NavigationController>(1, 4);
	nav->SetElementInPos(std::get<0>(arcade), 0, 0);
	nav->SetElementInPos(std::get<0>(pvp), 0, 1);
	nav->SetElementInPos(std::get<0>(options), 0, 2);
	nav->SetElementInPos(std::get<0>(exit), 0, 3);

	app_->getAssetsManager()->playMusic(0);
	
}

void MainMenu::handleInput()
{
	if (app_->getInputManager()->pressedStart()) {
		app_->Exit();
	}
	GameState::handleInput();
}

void MainMenu::GoArcade(App* app)
{
	app->getStateMachine()->pushState(new Fight(app));
}

void MainMenu::Go1v1(App* app)
{
	// TEMPORARY, TESTING
	app->getStateMachine()->pushState(new Training(app));
}

void MainMenu::GoOptions(App* app)
{
	app->Options();
}

void MainMenu::Leave(App* app)
{
	app->Exit();
}
