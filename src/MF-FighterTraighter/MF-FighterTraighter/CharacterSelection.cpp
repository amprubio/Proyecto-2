#include "CharacterSelection.h"

#include "Entity.h"
#include "UIFactory.h"
#include "RenderImage.h"
#include "Transform.h"
#include "Button.h"
#include "TextComponent.h"
#include "NavigationController.h"
#include "Font.h"
#include "RenderAnimation.h"
#include "UITransform.h"
void CharacterSelection::init()
{
	// background

	Entity* background_ = entManager_.addEntity();	
	background_->addComponent<Transform>(Vector2D(), Vector2D(), app_->getWindowManager()->getCurResolution().w, app_->getWindowManager()->getCurResolution().h, 0);
	background_->addComponent<RenderAnimation>(app_->getAssetsManager()->getTexture(AssetsManager::BackgroundFight), 20);

	//panel

	Entity* centralP_ = UIFactory::createPanel(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::Background),
		Vector2D(ancho / 5, 50), Vector2D(ancho /5, 50), Vector2D(ancho / 5, 50), (ancho / 25)*15, (alto/15)*10, 0);

	Entity* leftP_ = UIFactory::createPanel(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::Banner),
		Vector2D((ancho / 25) *1, 100), Vector2D((ancho / 25) * 1, 100), Vector2D((ancho / 25) * 1, 100), (ancho / 25) *4.5, (alto/15)*10, 0);

	Entity* rightP_ = UIFactory::createPanel(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::Banner),
		Vector2D((ancho / 25) * 19.5, 100), Vector2D((ancho / 25) * 19.5, 100), Vector2D((ancho / 25) * 19.5, 100), (ancho / 25) * 4.5, (alto / 15) * 10, 0);

	// buttons
	tuple <Entity*, Entity*> boton1 = UIFactory::createButton(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::Button), app_->getAssetsManager()->getFont(AssetsManager::Roboto_Black),
		Vector2D((ancho / 25) * 1, (alto / 14) * 11.5), Vector2D((ancho / 25) * 1, (alto / 14) * 11.5), Vector2D((ancho / 25) * 1, (alto / 14) * 11.5), (ancho / 25) * 4, (alto / 25) * 4, 0, nullptr, nullptr, "Continue", letra / 2, TextComponent::TextAlignment::Center);
	std::get<1>(boton1)->getComponent<UITransform>(ecs::Transform)->Center;
	tuple <Entity*, Entity*> boton2 = UIFactory::createButton(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::Button), app_->getAssetsManager()->getFont(AssetsManager::Roboto_Black),
		Vector2D((ancho / 25) * 20, (alto / 14) * 11.5), Vector2D((ancho / 25) * 20, (alto / 14) * 11.5), Vector2D((ancho / 25) * 20, (alto / 14) * 11.5), (ancho / 25) * 4, (alto / 25) * 4, 0, nullptr, nullptr, "Continue", letra / 2, TextComponent::TextAlignment::Center);
	std::get<1>(boton1)->getComponent<UITransform>(ecs::Transform)->Center;
	
	//icons of the character
	tuple <Entity*, Entity*> flor_ = UIFactory::createButton(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::CharacterSelection), app_->getAssetsManager()->getFont(AssetsManager::Roboto_Black),
		Vector2D((ancho / 25) * 6, (alto / 14) * 2), Vector2D((ancho / 25) * 6, (alto / 14) * 2), Vector2D((ancho / 25) * 6, (alto / 14) * 2), (ancho / 25) * 3, (alto / 14) * 3 ,0,
		nullptr, nullptr, " ", letra, TextComponent::TextAlignment::Center);
	tuple <Entity*, Entity*> mkwhoop_ = UIFactory::createButton(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::CharacterSelection), app_->getAssetsManager()->getFont(AssetsManager::Roboto_Black),
		Vector2D((ancho / 25) * 9.5, (alto / 14) * 2), Vector2D((ancho / 25) * 9.5, (alto / 14) * 2), Vector2D((ancho / 25) * 9.5, (alto / 14) * 2), (ancho / 25) * 3, (alto / 14) * 3, 0,
		nullptr, nullptr, " ", letra, TextComponent::TextAlignment::Center);
	tuple <Entity*, Entity*> aisha_ = UIFactory::createButton(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::CharacterSelection), app_->getAssetsManager()->getFont(AssetsManager::Roboto_Black),
		Vector2D((ancho / 25) * 13, (alto / 14) * 2), Vector2D((ancho / 25) * 13, (alto / 14) * 2), Vector2D((ancho / 25) * 13, (alto / 14) * 2), (ancho / 25) * 3, (alto / 14) * 3, 0,
		nullptr, nullptr, " ", letra, TextComponent::TextAlignment::Center);
	tuple <Entity*, Entity*> mockinbird_ = UIFactory::createButton(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::CharacterSelection), app_->getAssetsManager()->getFont(AssetsManager::Roboto_Black),
		Vector2D((ancho / 25) * 16.5, (alto / 14) * 2), Vector2D((ancho / 25) * 16.5, (alto / 14) * 2), Vector2D((ancho / 25) * 16.5, (alto / 14) * 2), (ancho / 25) * 3, (alto / 14) * 3, 0,
		nullptr, nullptr, " ", letra, TextComponent::TextAlignment::Center);


	//artwork of the character

	Entity* j1_ = entManager_.addEntity();
	Entity* j2 = entManager_.addEntity();
	Entity* text_j1 = UIFactory::createText(app_, this, Vector2D((ancho / 25) * 5, (alto / 14) * 7), Vector2D((ancho / 25) * 5, (alto / 14) * 7),
		Vector2D((ancho / 25) * 5, (alto / 14) * 7), app_->getAssetsManager()->getFont(AssetsManager::Roboto_Black), "description_ j1", 30, (ancho / 25) * 5, (alto / 14) * 2);
	Entity* text_j2 = UIFactory::createText(app_, this, Vector2D((ancho / 25) * 15, (alto / 14) * 8), Vector2D((ancho / 25) * 15, (alto / 14) * 8),
		Vector2D((ancho / 25) * 15, (alto / 14) * 8), app_->getAssetsManager()->getFont(AssetsManager::Roboto_Black), "description_ j2", 30, (ancho / 25) * 5, (alto / 14) * 2);

	//Entitys


	Entity* navEnt = entManager_.addEntity();
	NavigationController* nav = navEnt->addComponent<NavigationController>(2, 3);
	nav->SetElementInPos(std::get<0>(mockinbird_)->getComponent<UIElement>(ecs::UIElement), 0, 0);
	nav->SetElementInPos(std::get<0>(flor_)->getComponent<UIElement>(ecs::UIElement), 0, 1);
	nav->SetElementInPos(std::get<0>(mkwhoop_)->getComponent<UIElement>(ecs::UIElement), 1, 0);
	nav->SetElementInPos(std::get<0>(aisha_)->getComponent<UIElement>(ecs::UIElement), 1, 1);
	nav->SetElementInPos(std::get<0>(boton1)->getComponent<UIElement>(ecs::UIElement), 0, 2);
	nav->SetElementInPos(std::get<0>(boton2)->getComponent<UIElement>(ecs::UIElement), 1, 2);


	//logic of that for changing the artwork of each player 
}
