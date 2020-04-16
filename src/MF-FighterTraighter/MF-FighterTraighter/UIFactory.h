#pragma once
#include <tuple>
class Entity;
class Texture;
class App;
class GameState;
class Font;
#include "Vector2D.h"
#include <string>
#include "TextComponent.h"

using CallBackOnClick = void(App * app);//method with a reference to app
using SetValueOnClick = void(App * app, double value); //method with a reference to app and a value

class UIFactory
{
public:
	//creates a button with functionality
	static std::tuple<Entity*, Entity*> createButton(App* app, GameState* state, Texture* buttonTex, Font* font, Vector2D position = Vector2D(), Vector2D anchor = Vector2D(), Vector2D pivot = Vector2D(), double width = 0, double height = 0, double rotation = 0, CallBackOnClick* clickCallback = nullptr, CallBackOnClick* stopClickCallback = nullptr, std::string text = "", int fontSize = 20, TextComponent::TextAlignment alignment = TextComponent::TextAlignment::Left);

	// Creates a slider with two texts
	static std::tuple<Entity*, Entity*, Entity*, Entity*> createSlider
	(App* app, GameState* state, double min, double max, int steps,
		Texture* texture_, Texture* reg_texture, Font* font,
		Vector2D position, Vector2D anchor, Vector2D pivot, double width, double height,
		SetValueOnClick* valueOnClickCallback = nullptr,
		std::string text = "", int fontSize = 20,
		std::string valueText = "", int valueFontSize = 20);


	static Entity* createPanel(App* app, GameState* state, Texture* texture_, Vector2D position = Vector2D(), double width = 0, double height = 0, double rotation = 0);
	static Entity* createHab(App* app, GameState* state, Entity* e, Vector2D pos, double width, double height, Texture* texture_);
	
	static std::tuple<Entity*, Entity*, Entity*, Entity*, Entity*> createSubMenu(App* app, GameState* state, Texture* bg, Texture* bt, Entity* hab1_, Entity* hab2_, Entity* hab3_, Vector2D pos, double width, double height);
	static std::tuple<Entity*, Entity*, Entity*, Entity*, Entity*, Entity*, Entity*, Entity*, Entity*, Entity*, Entity*, Entity*>createSubHabMenu(App* app, GameState* state, Texture* bg, Entity* h1_, Entity* h2_, Entity* h3_, Entity* h4_, Entity* h5_, Entity* h6_, Entity* h7_, Entity* h8_, Entity* h9_, Entity* h10_, Vector2D pos, double width, double height);


protected:
	UIFactory() = delete;
	~UIFactory() {};
};

