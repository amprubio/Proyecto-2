#pragma once
#include "Component.h"
#include "UITimer.h"
#include "Entity.h"
#include "PlayerAttacks.h"

class AbilitiesTimerFunction:public Component
{
public:
	AbilitiesTimerFunction(HID* hid, UITimer* timer1, UITimer* timer2, Entity* pl) : Component(ecs::AbilitiesTimerFunction) {
		timer1_ = timer1;
		timer2_ = timer2;
		pl_ = pl;
	};
	~AbilitiesTimerFunction() {};
	//void init() override;
	void update() override;
	void updateTimerAb(int index, int time);
	void setTimeAb(int ind, int cool);
private:
	UITimer* timer1_;
	UITimer* timer2_;
	Entity* pl_;
	/*int timeab0;
	int timeab1;*/
};

