#include "Move.h"
#include "Fight.h"
#include "HitboxMng.h"
bool Move::update()
{ 
	
	if (activeFrame_ == endingFrame_) {
		/*
		//hitbox_=new hitbox(10,1,entity_->getComponent<PhysicsTransform>(ecs::Transform)->getBody());
		std::cout << "Puum" << endl;
		entity_->getComponent<PhysicsTransform>(ecs::Transform)->getBody();//{ 200,0 }, 50, 50, 10, 50, { 0,0 }
		entity_->getApp()->getHitboxMng()->addHitbox({ 200,0 }, 50, 50, 500, 50, entity_->getComponent<PhysicsTransform>(ecs::Transform)->getBody());
		//hitbox_->update();
		//static_cast<Fight*>(entity_->getApp()->getStateMachine()->getCurrentState())->destroyHitbox(entity_->getComponent<PhysicsTransform>(ecs::Transform)->getBody(),hitbox_);
		*/
		if (generateHitbox_ != nullptr && entity_ != nullptr) generateHitbox_(entity_);
		return true;
	}
	else {
		activeFrame_++;
		
		return false;
	}
	
}

void Move::render()
{
	//Renderizar seg�n activeFrame_, por lo que todas tendr�n que tener frames reptidos en lo que a dibujo se refiere
	//animaSheet_->render()
}
