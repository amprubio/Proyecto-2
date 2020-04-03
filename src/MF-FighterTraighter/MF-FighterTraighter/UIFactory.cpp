#include "UIFactory.h"
#include "GameState.h"
#include "EntityManager.h"
#include "Entity.h"

#include "Texture.h"

#include "Transform.h"
#include "Button.h"
#include "TextComponent.h"
#include "RenderImage.h"
#include "App.h"
#include "Slider.h"
#include "IndexSlider.h"

//create a button with their callbacks
std::tuple<Entity*, Entity*> UIFactory::createButton
	(App* app, GameState* state, Texture* buttonTex, 
	Font* font, Vector2D position, double width, double height, double rotation, 
	CallBackOnClick* clickCallback, CallBackOnClick* stopClickCallback, std::string text, int fontSize)
{
	Entity* button = state->getEntityManager().addEntity();
	button->addComponent<Transform>(position, Vector2D(), width, height, rotation);
	button->addComponent<RenderImage>(buttonTex);
	button->addComponent<Button>(clickCallback, stopClickCallback);

	Entity* textEnt = state->getEntityManager().addEntity();
	textEnt->addComponent<Transform>(position, Vector2D(), width, height, rotation);
	textEnt->addComponent<TextComponent>(text, font, fontSize);

	return std::make_tuple(button, textEnt);
}

// create the structure of  slider (bar, buttons and the index)
std::tuple<Entity*, Entity*, Entity*, Entity*> UIFactory::createSlider
	(App* app, GameState* state, double min, double max, int steps, 
	Texture* texture_, Texture* reg_texture, Font* font,
	Vector2D position, double width, double height,
	SetValueOnClick* valueOnClickCallback,
	std::string text, int fontSize,
	std::string valueText, int valueFontSize)
{
	Entity* slider = state->getEntityManager().addEntity();
	slider->addComponent<Transform>(position, Vector2D(), width, height, 0);
	slider->addComponent<RenderImage>(texture_);
	slider->addComponent<Slider>(min, max, steps, valueOnClickCallback);

	Entity* reg_ = state->getEntityManager().addEntity();
	reg_->addComponent<Transform>(position, Vector2D(), 25, height * 5, 0);
	reg_->addComponent<RenderImage>(reg_texture);
	reg_->addComponent<IndexSlider>(slider);
	
	Entity* text_ = state->getEntityManager().addEntity();
	text_->addComponent<Transform>(Vector2D(position.getX(), position.getY() - fontSize - 20), Vector2D(), width, fontSize, 0);
	text_->addComponent<TextComponent>(text, font, fontSize);
	
	Entity* ValueText_ = state->getEntityManager().addEntity();
	ValueText_->addComponent<Transform>(Vector2D(position.getX() + width + 10, position.getY() - fontSize / 2), Vector2D(), width, fontSize, 0);
	ValueText_->addComponent<TextComponent>(valueText, font, valueFontSize);

	return std::make_tuple(slider, reg_, text_, ValueText_);
}

Entity* UIFactory::createPanel(App* app, GameState* state, Texture* texture_, Vector2D position, double width, double height, double rotation)
{
	Entity* panel = state->getEntityManager().addEntity();
	panel->addComponent<Transform>(position, Vector2D(), width, height, rotation);
	panel->addComponent<RenderImage>(texture_);
	//a�adir tema de UIComponent para las resoluciones

	return panel;
}

 vector<Entity*> UIFactory::createHabSubMenu(App* app, GameState* state, Vector2D position, double width, double height, Texture* wallTexture_, vector<Entity*> habilidades) //este vector tiene 3 habilidades
{
	vector<Entity*> aux;
	Entity* panel = createPanel(app, state, wallTexture_, position, width, height);
	aux.push_back(panel);
	for (int i = 0; i < habilidades.size(); i++) {

		Entity* e = state->getEntityManager().addEntity();

		Transform* t = e->addComponent<Transform>(Vector2D(position.getX() + 60 * i, 300),
			Vector2D(),habilidades[i]->getComponent<Transform>(ecs::Transform)->getWidth(),
			habilidades[i]->getComponent<Transform>(ecs::Transform)->getHeight());
		
		//RenderImage* im = habilidades[i]->getComponent<RenderImage>(ecs::RenderImage);
		RenderImage* im = e->addComponent<RenderImage>(wallTexture_); //esto es auxiliar

		aux.push_back(e);
	}

	Entity* button = state->getEntityManager().addEntity();
	aux.push_back(button);

	return aux;
}

 vector<Entity*> UIFactory::createSelectionHabSubMenu(App* app, GameState* state, Vector2D position, double width, double height, Texture* wallTexture_, vector<Entity*> habilidades)
 {
	 vector<Entity*> menu;
	 Entity* panel = createPanel(app, state, wallTexture_, position, width, height);
	 menu.push_back(panel);

	 Entity* lButton=state->getEntityManager().addEntity();
	 lButton->addComponent<Transform>(Vector2D(position.getX() + (width / 2) - 100, position.getY()), Vector2D(), 50, 50, 0);
	 lButton->addComponent<RenderImage>(wallTexture_);
	 menu.push_back(lButton);

	 Entity* rButton=state->getEntityManager().addEntity();
	 rButton->addComponent<Transform>(Vector2D(position.getX() + (width / 2) + 100, position.getY()), Vector2D(), 50, 50, 0);
	 rButton->addComponent<RenderImage>(wallTexture_);
	 menu.push_back(rButton);

	 for (int i = 0; i < habilidades.size(); i++) {
		
		 Entity* e = state->getEntityManager().addEntity();

		 if (i <= 4) {
			 Transform* t = e->addComponent<Transform>(Vector2D(position.getX() + 60 * i, 300),
				 Vector2D(), habilidades[i]->getComponent<Transform>(ecs::Transform)->getWidth(),
				 habilidades[i]->getComponent<Transform>(ecs::Transform)->getHeight());
		 }
		 //ESTO LUEGO SE CAMBIA
		 else if(i<=9) {
			 Transform* t = e->addComponent<Transform>(Vector2D(position.getX() + 60 * i, 600),
				 Vector2D(), habilidades[i]->getComponent<Transform>(ecs::Transform)->getWidth(),
				 habilidades[i]->getComponent<Transform>(ecs::Transform)->getHeight());

		 }
		 //RenderImage* im = habilidades[i]->getComponent<RenderImage>(ecs::RenderImage);
		 RenderImage* im = e->addComponent<RenderImage>(wallTexture_); //esto es auxiliar

		 menu.push_back(e);
	 }
	 
	 return menu;
 }


//std::tuple<Entity*,std::list<Entity*>> 
//UIFactory::createSelectionHabMenu(GameState* state, double width, double height, Texture* wallTexture_, double x, double y, Entity* player)
//{
//	Entity* wall_ = state->getEntityManager().addEntity();
//	wall_->addComponent<Transform>(Vector2D(x, y), Vector2D(), width, height, 0);
//	wall_->addComponent<RenderImage>(wallTexture_);
//
//	std::list<Entity*>hab;
//	//hab = player->getHabilitiesList();
//	//pedir al player su lista de habilidades
//
//	for (int i = 0; i < hab.size(); i++) {
//		Entity* num_ = state->getEntityManager().addEntity();
//		num_->addComponent<Transform>(Vector2D(x, y), Vector2D(), width, height, 0);
//		num_->addComponent<RenderImage>(/*hab[i].getRender()*/);
//	}
//
//
//	return std::make_tuple(wall_, hab);
//}
//
//
