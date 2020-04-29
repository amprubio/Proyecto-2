#include "Component.h"
#include "RenderImage.h"
#include "UIElement.h"

using CallBackOnClick = void(App* app);

class Button : public UIElement {

public:
	//constructor
	Button(CallBackOnClick* startClickCallback = nullptr, CallBackOnClick* stopClickCallback = nullptr) : UIElement(), clickCallback_(startClickCallback), stopClickCallback_(stopClickCallback) {};

	virtual void Press()
	{
		Buttonstate_ = Pressed;
		entity_->getComponent<RenderImage>(ecs::RenderImage)->setFrame(2, 0);
		if (clickCallback_) clickCallback_(app_);
	};
	virtual void Select() 
	{
		if (Buttonstate_ != Selected) {
			Buttonstate_ = Selected;
			entity_->getComponent<RenderImage>(ecs::RenderImage)->setFrame(1, 0);
		}
	};
	virtual void Disable() 
	{
		Buttonstate_ = Disabled;
	};
	virtual void Deselect()
	{
		Buttonstate_ = Normal;
		entity_->getComponent<RenderImage>(ecs::RenderImage)->setFrame(0, 0);
	};

	//destructor
	virtual ~Button() {};
	
	//callbacks
	inline void setClickCallback(CallBackOnClick* callback) { clickCallback_ = callback; }
	inline void setStopClickCallback(CallBackOnClick* callback) { stopClickCallback_ = callback; }

	//methods overrided of Component
	void init() override;
	//handle the input of the mouse by the moment
	void handleInput() override;
	void render() override;

private:
	CallBackOnClick* clickCallback_ = nullptr;
	CallBackOnClick* stopClickCallback_ = nullptr;
};
