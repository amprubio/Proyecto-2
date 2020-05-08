#pragma once
#include "DestroyOnHit.h"
#include "PlayerData.h"
#include "BulletGravity.h"
#include "AbilityFactory.h"

class FallOnHit : public DestroyOnHit
{
public:
	FallOnHit(int damage, int time, int hitstun, Vector2D knockback, bool guardbreaker, int id, Entity* e, HitboxData* spawnData,bool destroyInContact = false) :
		DestroyOnHit(damage, time, hitstun, knockback, guardbreaker, id, e, destroyInContact), spawnData_(spawnData) {}
	virtual void onHit(b2Fixture* other) {
		UserData* data = static_cast<UserData*>(other->GetUserData());
		if (data) {
			if (data->entity_->getComponent<PlayerData>(ecs::PlayerData)){//other is player
				BulletGravity* bullet = entity_->getComponent<BulletGravity>(ecs::Bullet);
				//phTr->setSpeed(Vector2D(0, phTr->getSpeed().getY()));
				bullet->changeSpeed(Vector2D(0,bullet->getSpeed().getY()));
				entity_->getComponent<PhysicsTransform>(ecs::Transform)->changeMask(entity_->getState()->BOUNDARY);

			}
			else {
				PhysicsTransform* pT = entity_->getComponent<PhysicsTransform>(ecs::Transform);
				entity_->getState()->getEntityManager().addEntity();
				uint16 mask;
				Entity* owner;
				if (spawnData_->id_ == 0) {
					mask = entity_->getState()->PLAYER_1;
				}
				else {
					mask = entity_->getState()->PLAYER_2;
				}
				AbilityFactory::instanceProyectile(spawnData_->entity_, 200, 200, pT->getPosition(), Vector2D(0, 0), mask, entity_->getState(),
					entity_->getApp(), entity_->getApp()->getAssetsManager()->getTexture(AssetsManager::Logo), pT->getOrientation(),
					spawnData_, false);
				DestroyOnHit::onHit(other);
				
				//estado->createHumo(x,y)
				//entity_->getComponent<PhysicsTransform>(ecs::Transform)->changeMask(entity_->getState()->NONE);
			}
		}
	}
	virtual ~FallOnHit() {}
private:
	HitboxData* spawnData_ = nullptr;
};
