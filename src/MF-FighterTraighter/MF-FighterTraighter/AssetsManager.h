#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <vector>
#include "Texture.h"
#include "Font.h"
#include "jute.h"
class App;

class AssetsManager
{
public:
	AssetsManager(App* app);
	AssetsManager(AssetsManager&) = delete;
	AssetsManager& operator= (AssetsManager&) = delete;

	Texture* getTexture(size_t id);
	void loadTextures(); // Textures are hardcoded for now

	void loadFonts(); // Fonts are hardcoded for now
	Font* getFont(size_t id);

	/*void loadJsons(); // Fonts are hardcoded for now
	jute::jValue getJson(size_t id);*/

	virtual ~AssetsManager();
private:
	std::vector<Texture*> textures_;
	std::vector<Font*> fonts_;
	//std::vector<jute::jValue> jsons_;
	App* app_;
};

