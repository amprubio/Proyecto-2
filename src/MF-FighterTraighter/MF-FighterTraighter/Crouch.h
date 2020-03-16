#pragma once
#include "Component.h"
#include "PhysicsTransform.h"

class Crouch :
	public Component
{
public:
	Crouch();
	void init() override;
	void handleInput() override; // separate into two?
	void update() override;
	void crouch();
	void uncrouch();
	//poder 
	//CanCrouch(){return  !cancrouched;};
	virtual ~Crouch();
private:
	//Transform* tr_;
	PhysicsTransform* tr_ = nullptr;

	bool canCrouch = false;
	Vector2D pos;
	double initialHeight;
	double crouchPercent; //el n�mero entre cu�nto queremos que se divida el hitbox
};

