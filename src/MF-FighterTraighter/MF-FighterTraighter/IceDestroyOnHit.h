#pragma once
#include "DestroyOnHit.h"
#include "PlayerState.h"
#include "PlayerParticleSystem.h"
class IceDestroyOnHit : public DestroyOnHit
{
public:
	IceDestroyOnHit(int damage, int time, int hitstun, Vector2D knockback, bool guardbreaker, int id, Entity* e, bool mHit = false) :
		DestroyOnHit(damage, time, hitstun, knockback, guardbreaker, id, e, mHit) {}

	virtual void onHit(b2Fixture* other) {
		UserData* data = static_cast<UserData*>(other->GetUserData());
		if (data && data->entity_->getComponent<PlayerState>(ecs::PlayerState)->isGuardingStun()) {	//When the ice has hit (SPECIAL CASE)
			hitstun_ /= 10;
			data->entity_->getComponent<PlayerState>(ecs::PlayerState)->goGuardingStun(hitstun_);
		}
		else {
			PhysicsTransform* phTr = data->entity_->getComponent<PhysicsTransform>(ecs::Transform);
			int orientation_ = phTr->getOrientation();
			int width = 260;
			int projX = (phTr->getWidth() / 4);
			if (orientation_ == -1) projX = (phTr->getWidth() / 4);
			Vector2D pos = Vector2D(projX, -30);

			data->entity_->getComponent<PlayerParticleSystem>(ecs::PlayerParticleSystem)->addNewParticle(AssetsManager::Hb2, pos, Vector2D(width, 530), hitstun_, true);
		}
		DestroyOnHit::onHit(other);
	}
	virtual ~IceDestroyOnHit() {}
};